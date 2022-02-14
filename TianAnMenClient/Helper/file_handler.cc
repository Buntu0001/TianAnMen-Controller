//
// Created by LUNAFE on 2022-02-10.
//

#include "file_handler.h"

file_handler::file_handler(char *task_id_, int final_index_) {
    memmove(task_id, task_id_, sizeof(task_id));
    final_index = final_index_;
}

int file_handler::AddData(wchar_t *file_data_, int index) {
#ifdef DEBUG
    wprintf(L"[DEBUG_TRANSFER] FILE_TASK_ID: %s\n[DEBUG_TRANSFER] INDEX: %d/%d\n", task_id, index, final_index);
#endif
    if (index == final_index) {
        memset(file_buffer, 0, sizeof(file_buffer));
        memmove(file_buffer, file_data_, sizeof(file_buffer));
        wcscat(file_data, file_buffer);
        IssueFile();
        return 0;
    } else {
        memset(file_buffer, 0, sizeof(file_buffer));
        memmove(file_buffer, file_data_, sizeof(file_buffer));
        wcscat(file_data, file_buffer);
        return 1;
    }
}

void file_handler::IssueFile() {
    wprintf(L"[DEBUG_TRANSFER] FILE_ISSUE\n");
    wprintf(L"[DEBUG_TRANSFER] %S\n", file_data);
}

void util::MakeInfo(packet *packet_) {
    struct INFO init_info;
    util::InitRetrieveInfo(&init_info);

    packet_->set_type(PACKET_TYPE::INFO);

    char id[16];
    util::GenId(id, 16);
    packet_->set_task_id(id);

    packet_->set_data((wchar_t *) &init_info);

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
                    if (*receive_packet.get_current_index() == 1) {
                         handle = new file_handler(receive_packet.get_task_id(),
                                                                *receive_packet.get_final_index());

                        file_handle_list::Add(receive_packet.get_task_id(), handle);

                        if (handle->AddData(receive_packet.get_data(), *receive_packet.get_current_index()) == 0) {
#ifdef DEBUG
                            wprintf(L"[DEBUG_TRANSFER] END!\n");
#endif
                            return;
                        }
#ifdef DEBUG
                        wprintf(L"[DEBUG_TRANSFER] FIRST_RECEIVED\n");
#endif
                    } else {
                        file_handler *handle = file_handle_list::Get(receive_packet.get_task_id());
                        if (handle->AddData(receive_packet.get_data(), *receive_packet.get_current_index()) == 0) {
#ifdef DEBUG
                            wprintf(L"[DEBUG_TRANSFER] END!\n");
#endif
                            return;
                        }
                    }
                } else {
#ifdef DEBUG
                    wprintf(L"[DEBUG_TRANSFER] WRONG_PACKET_TYPE\n");
#endif
                }
                Sleep(1000);
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
