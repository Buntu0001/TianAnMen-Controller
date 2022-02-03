
#include "main.h"
#include "packet.h"

int main() {
    wchar_t test[100];
    eventhandler::testEvent(test);

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET sock;
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1) {
        printf("Socket Error!\n");
        system("pause");
        return 0;
    }

    SOCKADDR_IN in = {};
    in.sin_family = AF_INET;
    in.sin_port = htons(PORT);
    in.sin_addr.s_addr = inet_addr(SERVER_IP);

    connect(sock, (SOCKADDR *) &in, sizeof(in));

    //wchar_t msg[] = L"Client Send";

    char id[16];
    util::genID(id, 16);
    struct PACKET testPacket;
    strcpy(testPacket.taskID, id);
    wcscpy(testPacket.data, test);
    testPacket.currentIndex = 0;
    testPacket.finalIndex = 0;

    printf("%s\n", testPacket.taskID);
    printf("%S\n", testPacket.data);
    printf("%d\n%d\n", testPacket.currentIndex, testPacket.finalIndex);

    printf("%d\n", sizeof(testPacket));

    send(sock, (char *)&testPacket, sizeof(testPacket), 0);
}
