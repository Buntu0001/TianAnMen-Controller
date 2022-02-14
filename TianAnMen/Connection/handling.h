//
// Created by LUNAFE on 2022-02-09.
//

#ifndef TIANANMEN_HANDLING_H
#define TIANANMEN_HANDLING_H

#include <iostream>
#include <windows.h>
#include <thread>
#include <ctime>

#include "packet.h"
#include "client.h"
#include "client_list.h"
#include "../Misc/structure.h"
#include "../main.h"
#include "../Helper/file_handler.h"

class handling {
public:
    static void Handler(SOCKET socket);

    static void Listening();
};


#endif //TIANANMEN_HANDLING_H
