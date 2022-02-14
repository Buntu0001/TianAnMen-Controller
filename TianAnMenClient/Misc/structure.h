//
// Created by LUNAFE on 2022-02-04.
//

#ifndef TIANANMENCLIENT_STRUCTURE_H
#define TIANANMENCLIENT_STRUCTURE_H

struct INFO {
    wchar_t ip_address[16];
    wchar_t computer_name[32];
    wchar_t os_version[16];
    wchar_t window_title[128];
    wchar_t geo_id[8];
};

enum PACKET_TYPE {
    PING,
    INFO,
    FILE_SERVER_TO_CLIENT,
    FILE_DATA
};

struct PACKET {
    enum PACKET_TYPE type;
    char task_id[16];
    wchar_t data[512];
    int current_index;
    int final_index;
};

#endif //TIANANMENCLIENT_STRUCTURE_H
