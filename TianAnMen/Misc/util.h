//
// Created by LUNAFE on 2022-02-04.
//

#ifndef TIANANMEN_UTIL_H
#define TIANANMEN_UTIL_H

#include <ctime>
#include <random>

#include "../Connection/packet.h"

class Util {
public:
    static void GenId(char *buf, int len);

    static void MakePing(class Packet *packet_);

    static void CharToWchar(wchar_t *dest, char *src);

    static void WcharToChar(char *dest, wchar_t *src);
};


#endif //TIANANMEN_UTIL_H
