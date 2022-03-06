//
// Created by LUNAFE on 2022-02-09.
//

#ifndef TIANANMENCLIENT_HANDLING_H
#define TIANANMENCLIENT_HANDLING_H

#include <iostream>
#include <thread>

#include "../Helper/event_handler.h"
#include "../Misc/util.h"
#include "packet.h"
#include "../Misc/structure.h"
#include "../main.h"

class Handling {
public:
    static bool Connected();

    static void Disconnected();

    static void PrintInfo(struct INFO *test);

    static void Handler();

    static void WaitConnected();
};


#endif //TIANANMENCLIENT_HANDLING_H
