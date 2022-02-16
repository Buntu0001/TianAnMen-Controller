//
// Created by LUNAFE on 2022-02-04.
//

#ifndef TIANANMENCLIENT_UTIL_H
#define TIANANMENCLIENT_UTIL_H

#include <windows.h>
#include <ctime>
#include <random>

#include "../Helper/event_handler.h"
#include "../Connection/packet.h"
#include "../Helper/file_handler.h"
#include "structure.h"

class util {
public:
    static void GenId(char *buf, int len);

    static void Trim(wchar_t *src, int index, wchar_t *dst);

    static void InitRetrieveInfo(struct INFO *info);

    static void MakePong(class packet *packet_);

    static void MakeInfo(class packet *packet_);

    static void CharToWchar(wchar_t *dest, char *src);

    static void WcharToChar(char *dest, wchar_t *src);
};


#endif //TIANANMENCLIENT_UTIL_H
