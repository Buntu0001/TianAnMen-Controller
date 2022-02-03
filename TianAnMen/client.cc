//
// Created by LUNAFE on 2022-01-29.
//

#include "client.h"

SOCKET client::getSocket() {
    return socket;
}

time_t client::getStartTime() {
    return startTime;
}

client::client(SOCKET socket_, time_t time) {
    socket = socket_;
    startTime = time;
}
