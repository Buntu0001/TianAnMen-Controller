//
// Created by LUNAFE on 2022-02-09.
//

#ifndef TIANANMENCLIENT_HANDLING_H
#define TIANANMENCLIENT_HANDLING_H

#include <iostream>
#include <winsock2.h>

#include "../Helper/event_handler.h"
#include "../Misc/util.h"
#include "packet.h"
#include "../Misc/structure.h"
#include "../main.h"

class handling {
public:
    static bool Connected();
    static void Handler();
    static void WaitConnected();
};


#endif //TIANANMENCLIENT_HANDLING_H
