//
// Created by LUNAFE on 2022-02-04.
//

#include "main.h"

bool main::connected() {
    printf("[DEBUG]connect\n");
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    main::sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (main::sock == -1) {
        wprintf(L"Socket Error!\n");
        system("pause");
        return 0;
    }

    SOCKADDR_IN in = {};
    in.sin_family = AF_INET;
    in.sin_port = htons(PORT);
    in.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(main::sock, (SOCKADDR *) &in, sizeof(in)) == SOCKET_ERROR) {
        return false;
    } else {
        return true;
    }
}

void main::init(struct PACKET *packet) {
    printf("[DEBUG]init\n");

    struct INFO initInfo;
    util::initRetrieveInfo(&initInfo);

    struct PACKET initPacket;

    initPacket.type = PACKET_TYPE::INFO;

    util::genID(initPacket.taskID, 16);

    memmove(&(initPacket.data[0]), (wchar_t *) &initInfo.ipAddress[0], sizeof(initInfo));

    initPacket.currentIndex = 1;
    initPacket.finalIndex = 1;

    memmove(packet, &initPacket, sizeof(initPacket));
}

SOCKET main::sock = 0;
int main() {
    _wsetlocale(LC_ALL, L"korean");

    while (!main::connected()) {
        printf("[DEBUG]Connecting...\n");
        Sleep(5000);
    }
    printf("[DEBUG]Connected!\n");

    //printf("sent: %d\n", send(sock, (char *) &initPacket, PACKET_SIZE, 0));
}
