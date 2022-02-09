//
// Created by LUNAFE on 2022-01-29.
//

#include "client.h"

SOCKET client::GetSocket() {
    return socket;
}

time_t client::GetInstallTime() {
    return install_time;
}

struct INFO client::GetInfo() {
    return info;
}

client::client(SOCKET socket_, time_t time, struct INFO *info_) {
    socket = socket_;
    install_time = time;
    memmove(&info, info_, sizeof(*info_));
}
