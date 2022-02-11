//
// Created by LUNAFE on 2022-02-04.
//

#ifndef TIANANMEN_UTIL_H
#define TIANANMEN_UTIL_H

#include <ctime>
#include <random>

#include "../Connection/packet.h"

class util {
public:
    static void GenId(char* buf, int len);

    static void MakePing(class packet *packet_);
};


#endif //TIANANMEN_UTIL_H
