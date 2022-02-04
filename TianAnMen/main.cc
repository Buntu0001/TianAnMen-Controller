#include "main.h"


bool main::recvData(SOCKET socket, char *msg) {
    int length = recv(socket, (char *) msg, PACKET_SIZE, 0);
    if (length > 0) {
        msg[length] = '\0';
        return true;
    } else {
        return false;
    }
}

void main::listening() {
    printf("[DEBUG]LISTENING\n");
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET serverSock;
    serverSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSock == -1) {
        printf("Socket Error!\n");
        system("pause");
        return;
    }

    SOCKADDR_IN serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSock, (sockaddr *) &serverAddr, sizeof(serverAddr)) == -1) {
        printf("Bind Error!\n");
        system("pause");
        return;
    }

    if (listen(serverSock, SOMAXCONN) == -1) {
        printf("Listen Error!\n");
        system("pause");
        return;
    }

    SOCKADDR_IN clientAddr = {};
    int addrSize = sizeof(clientAddr);
    while (true) {
        SOCKET clientSock = INVALID_SOCKET;
        clientSock = accept(serverSock, (SOCKADDR *) &serverAddr, &addrSize);
        if (clientSock != INVALID_SOCKET) {
            printf("[DEBUG]accepted\n");
        } else if (clientSock == INVALID_SOCKET) {
            continue;
        } else {
            continue;
        }
    }
}

int main() {
    _wsetlocale(LC_ALL, L"korean");

    std::thread t1(main::listening);
    t1.join();
    /*char buffer[PACKET_SIZE];
    if (recv(clientSock, (char *) buffer, PACKET_SIZE, 0)) {

        struct PACKET *testPacket = (struct PACKET *) &buffer;
        printf("packet size: %d\n", sizeof(buffer));
        struct INFO *testInfo = (struct INFO *) testPacket->data;


        printf("[DEBUG]PACKET Struct\n");
        wprintf(L"type: %d\ntaskID: %s\ndata: Reserved\ncurrentIndex: %d\nfinalIndex: %d\n",
                testPacket->type, testPacket->taskID, testPacket->currentIndex, testPacket->finalIndex);


        printf("[DEBUG]INFO Struct\n");
        wprintf(L"ipAddress: %S\n", testInfo->ipAddress);
        wprintf(L"computerName: %S\n", testInfo->computerName);
        wprintf(L"osVersion: %S\n", testInfo->osVersion);
        wprintf(L"windowTitle: %S\n", testInfo->windowTitle);
        wprintf(L"geoID: %S\n", testInfo->geoID);

    } else {
        printf("Error Data Receive!\n");
    }


    */
}
