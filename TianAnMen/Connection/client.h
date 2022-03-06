//
// Created by LUNAFE on 2022-01-29.
//

#ifndef TIANANMEN_CLIENT_H
#define TIANANMEN_CLIENT_H

#include <winsock2.h>

#include "../Misc/structure.h"

class Client {
private:
    SOCKET socket;
    time_t install_time;
    struct INFO info;
    struct COMMAND cmd;
public:
    SOCKET GetSocket();

    time_t GetInstallTime();

    struct INFO GetInfo();

    void SetCommand(struct COMMAND *cmd_);

    struct COMMAND *GetCommand();

    Client(SOCKET socket_, time_t time, struct INFO *info_);
};


#endif //TIANANMEN_CLIENT_H
