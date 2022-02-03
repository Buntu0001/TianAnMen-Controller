//
// Created by LUNAFE on 2022-01-29.
//

#ifndef TIANANMEN_CLIENT_H
#define TIANANMEN_CLIENT_H

#include <winsock2.h>

class client {
public:
    SOCKET getSocket();
    time_t getStartTime();
    client(SOCKET socket_, time_t time);
private:
    struct tm {
        int tm_sec;
        int tm_min;
        int tm_hour;
        int tm_mday;
        int tm_mon;
        int tm_year;
        int tm_wday;
        int tm_yday;
        int tm_isdst;
    };

    SOCKET socket;
    time_t startTime;

};


#endif //TIANANMEN_CLIENT_H
