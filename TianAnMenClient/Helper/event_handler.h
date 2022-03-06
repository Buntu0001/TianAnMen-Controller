//
// Created by LUNAFE on 2022-02-04.
//

#ifndef TIANANMENCLIENT_EVENT_HANDLER_H
#define TIANANMENCLIENT_EVENT_HANDLER_H

#include <windows.h>
#include <winnt.h>
#include <wininet.h>
#include <winnls.h>
#include "../Misc/util.h"

class EventHandler {
public:
    static void GetComputerName(wchar_t *buf);

    static void GetOsVersion(wchar_t *buf);

    static void GetIp(wchar_t *buf_);

    static void GetActiveWindow(wchar_t *buf);

    static void GetGeoId(wchar_t *buf);
};


#endif //TIANANMENCLIENT_EVENT_HANDLER_H
