//
// Created by LUNAFE on 2022-02-04.
//

#ifndef TIANANMENCLIENT_UTIL_H
#define TIANANMENCLIENT_UTIL_H

#include <windows.h>
#include <ctime>
#include <random>

#include "eventhandler.h"
#include "structure.h"

class util {
public:
    static void genID(char* buf, int len);
    static void trim(wchar_t *src, int index, wchar_t *dst);
    static void initRetrieveInfo(struct INFO *info);
};


#endif //TIANANMENCLIENT_UTIL_H
