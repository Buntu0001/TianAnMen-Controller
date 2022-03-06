//
// Created by LUNAFE on 2022-01-29.
//

#include "client.h"

SOCKET Client::GetSocket() {
    return socket;
}

time_t Client::GetInstallTime() {
    return install_time;
}

struct INFO Client::GetInfo() {
    return info;
}

Client::Client(SOCKET socket_, time_t time, struct INFO *info_) {
    socket = socket_;
    install_time = time;
    memmove(&info, info_, sizeof(info));
    cmd.type = COMMAND_TYPE::NONE;
}

void Client::SetCommand(struct COMMAND *cmd_) {
    memmove(&cmd, cmd_, sizeof(cmd));
}

struct COMMAND *Client::GetCommand() {
    return &cmd;
}
