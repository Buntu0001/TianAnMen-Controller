//
// Created by LUNAFE on 2022-02-04.
//

#ifndef TIANANMENCLIENT_MAIN_H
#define TIANANMENCLIENT_MAIN_H

#define PACKET_SIZE 1500
#define PORT 1234
#define SERVER_IP "127.0.0.1"

#include <iostream>
#include <winsock2.h>
#include <locale>

#include "Connection/handling.h"

class main {
public:
    static SOCKET sock;
};

#endif //TIANANMENCLIENT_MAIN_H
