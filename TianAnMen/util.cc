//
// Created by LUNAFE on 2022-02-04.
//

#include "util.h"

void util::genID(char *buf, int len) {
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    srand((unsigned) time(NULL));
    for (int i = 0; i < len; ++i) {
        buf[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    buf[len] = 0;
}