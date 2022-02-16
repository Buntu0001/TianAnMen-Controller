//
// Created by LUNAFE on 2022-02-12.
//

#include "file_handler.h"

file_handler::file_handler(wchar_t *file_path_) {
    memmove(file_path, file_path_, sizeof(file_path));

    util::GenId(task_id, 16);

    current_index = 1;
}

void file_handler::InitHandle() {
    final_index = GetFileBlockSize();
}

int file_handler::GetFileBlockSize() {
    HANDLE handle = CreateFileW(file_path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD size = GetFileSize(handle, NULL);
    CloseHandle(handle);
    if (size % 511 == 0) {
#ifdef DEBUG
        wprintf(L"[DEBUG-TRANSFER] BLOCK_SIZE: %d\n", size / 511);
#endif
        return size / 511;
    } else {
#ifdef DEBUG
        wprintf(L"[DEBUG-TRANSFER] BLOCK_SIZE: %d\n", (size / 511) + 1);
#endif
        return (size / 511) + 1;
    }
}

void file_handler::ReadData() {
    HANDLE open_handle = CreateFileW(file_path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (open_handle != INVALID_HANDLE_VALUE) {
        DWORD readed;
        memset(file_data, 0, sizeof(file_data));

        SetFilePointer(open_handle, stack, nullptr, FILE_BEGIN);

        ReadFile(open_handle, file_data, sizeof(file_data), &readed, NULL);
#ifdef DEBUG
        wprintf(L"[DEBUG-TRANSFER] READED: %d\n", readed);
#endif
        stack += sizeof(file_data);
#ifdef DEBUG
        wprintf(L"[DEBUG-TRANSFER] STACK: %lu\n", stack);
#endif

        CloseHandle(open_handle);
    } else {
#ifdef DEBUG
        wprintf(L"[DEBUG-TRANSFER] READ_DATA_ERROR\n");
        wprintf(L"[ERROR] %d\n", GetLastError());
#endif
    }
}

void file_handler::SendFileThread(SOCKET socket, wchar_t *file_path_) {
#ifdef DEBUG
    wprintf(L"[DEBUG-TRANSFER] SENDFILE_THREAD\n");
#endif
    file_handler *handle = new file_handler(file_path_);
    handle->InitHandle();
    while (true) {

        packet send_packet;
        send_packet.set_type(PACKET_TYPE::FILE_DATA);

        char id[16];
        util::GenId(id, 16);
        send_packet.set_task_id(id);

        handle->ReadData();
        send_packet.set_data(handle->file_data);

        send_packet.set_current_index(handle->current_index);
        send_packet.set_final_index(handle->final_index);

        if (send_packet.Send(socket) == -1) {
#ifdef DEBUG
            wprintf(L"[DEBUG_TRANSFER] SOCKET_ERROR\n");
#endif
            return;
        } else {
#ifdef DEBUG
            wprintf(L"[DEBUG_TRANSFER] DATA_SENT\n");
#endif
            printf("[DEBUG_TRANSFER] INDEX: %d/%d\n", handle->current_index, handle->final_index);
            if (handle->current_index == handle->final_index) {
#ifdef DEBUG
                wprintf(L"[DEBUG_TRANSFER] FINAL_SENT\n");
#endif
                return;
            } else {
                handle->current_index++;
            }
        }
        //Sleep(1000);
    }
}

