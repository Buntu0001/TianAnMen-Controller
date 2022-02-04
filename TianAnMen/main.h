//
// Created by LUNAFE on 2022-01-29.
//

#ifndef TIANANMEN_MAIN_H
#define TIANANMEN_MAIN_H

#define PORT 1234
#define PACKET_SIZE 1500

#include <stdio.h>
#include <windows.h>
#include <locale>
#include <thread>

#include "packet.h"
#include "client.h"
#include "structure.h"

class main {
public:
    static bool recvData(SOCKET socket, char *msg);
    static void listening();
};


#endif //TIANANMEN_MAIN_H
