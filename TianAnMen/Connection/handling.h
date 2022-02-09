//
// Created by LUNAFE on 2022-02-09.
//

#ifndef TIANANMEN_HANDLING_H
#define TIANANMEN_HANDLING_H

#define PORT 1234
#define PACKET_SIZE 1500

#include <iostream>
#include <windows.h>
#include <locale>
#include <thread>
#include <time.h>

#include "packet.h"
#include "client.h"
#include "client_list.h"
#include "../Misc/structure.h"

class handling {
public:
    static void Handler(SOCKET socket);
    static void Listening();
};


#endif //TIANANMEN_HANDLING_H
