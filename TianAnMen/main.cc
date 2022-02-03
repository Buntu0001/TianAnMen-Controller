#include "main.h"
#include "packet.h"

bool main::recvData(SOCKET socket, char *msg) {
    int length = recv(socket, (char *) msg, PACKET_SIZE, 0);
    if (length > 0) {
        msg[length] = '\0';
        return true;
    } else {
        return false;
    }
}

void main::listen() {

}

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET serverSock;
    serverSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSock == -1) {
        printf("Socket Error!\n");
        system("pause");
        return 0;
    }

    SOCKADDR_IN serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSock, (sockaddr *) &serverAddr, sizeof(serverAddr)) == -1) {
        printf("Bind Error!\n");
        system("pause");
        return 0;
    }

    if (listen(serverSock, SOMAXCONN) == -1) {
        printf("Listen Error!\n");
        system("pause");
        return 0;
    }

    SOCKADDR_IN clientAddr = {};
    int addrSize = sizeof(clientAddr);
    SOCKET clientSock = accept(serverSock, (SOCKADDR *) &serverAddr, &addrSize);

    char buffer[PACKET_SIZE];
    if (recv(clientSock, (char *) buffer, PACKET_SIZE, 0)) {
        PACKET *testPacket = (PACKET *) buffer;
        printf("%s\n", testPacket->taskID);
    } else {
        printf("Error Data Receive!\n");
    }


    WSACleanup();
}
