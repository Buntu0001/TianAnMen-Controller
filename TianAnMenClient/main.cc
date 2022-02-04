
#include "main.h"

int main() {
    _wsetlocale(LC_ALL, L"korean");

    struct INFO initInfo;

    util::initRetrieveInfo(&initInfo);

    /*printf("INFO size: %d\n", sizeof(initInfo));

    struct PACKET initPacket;

    initPacket.type = PACKET_TYPE::INFO;

    char id[16];
    util::genID(id, 16);
    printf("TaskID Genned!: %s\n", id);
    strcpy(initPacket.taskID, id);

    char *test;
    struct INFO *testInfo;
    test = (char *) &initInfo;
    testInfo = (struct INFO *) test;
    printf("info1: %S\n", testInfo->computerName);*/


    /*wprintf(L"data: %S\nsize: %d\n", initPacket.data, sizeof(initPacket.data));

    struct INFO testInfo;
    wcscpy((wchar_t *) &testInfo, initPacket.data);
    wprintf(L"test struct computerName: %S\n", testInfo.ipAddress);*/

    //initPacket.currentIndex = 0;
    //initPacket.finalIndex = 0;



    //system("pause");

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



    send(sock, (char *)&initInfo, sizeof(initInfo), 0);
}
