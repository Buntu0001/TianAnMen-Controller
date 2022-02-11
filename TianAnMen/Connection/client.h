//
// Created by LUNAFE on 2022-01-29.
//

#ifndef TIANANMEN_CLIENT_H
#define TIANANMEN_CLIENT_H

#include <winsock2.h>

#include "../Misc/structure.h"

class client {
private:
    SOCKET socket;
    time_t install_time;
    struct INFO info;
public:
    SOCKET GetSocket();

    time_t GetInstallTime();

    struct INFO GetInfo();

    client(SOCKET socket_, time_t time, struct INFO *info_);
};


#endif //TIANANMEN_CLIENT_H
