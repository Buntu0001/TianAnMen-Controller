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
    //testcode
    final_index = 1;
}

void file_handler::ReadData() {
    HANDLE open_handle = CreateFileW(file_path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (open_handle != INVALID_HANDLE_VALUE) {
        DWORD read_count;
        char test[2048];
        ReadFile(open_handle, test, 1024, &read_count, NULL);
        printf("[TEST111] %s\n", test);
        MultiByteToWideChar(CP_UTF8, 0, test, 1024, file_data, 512);
        CloseHandle(open_handle);
        return;
    } else {
#ifdef DEBUG
        wprintf(L"[DEBUG-TRANSFER] READDATA_ERROR\n");
#endif
        return;
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
        Sleep(1000);
    }
}

