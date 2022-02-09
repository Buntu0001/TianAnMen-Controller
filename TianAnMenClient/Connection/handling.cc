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
    packet::SendInfo();

    while (true) {
        struct PACKET *packet;
        char buf[PACKET_SIZE];
        if (recv(main::sock, (char *) buf, PACKET_SIZE, 0) == -1) {
            WaitConnected();
            packet::SendInfo();
        } else {
            packet = (struct PACKET *) &buf;
            int result = packet::ParsePacket(packet);
            if (result == 1) {
                struct PACKET pong_packet;
                packet::MakePong(&pong_packet);
                if (send(main::sock, (char *) &pong_packet, PACKET_SIZE, 0) == -1) {
                    WaitConnected();
                } else {
#ifdef DEBUG
                    printf("[DEBUG] PONG_SENT\n");
#endif
                }
            } else if (result == 0) {
            } else if (result == -1) {
                WaitConnected();
                packet::SendInfo();
            }
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