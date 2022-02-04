//
// Created by LUNAFE on 2022-02-04.
//

#ifndef TIANANMEN_PACKET_H
#define TIANANMEN_PACKET_H

#include "structure.h"

enum PACKET_TYPE {
    PING,
    INFO,
    FILE_DOWNLOAD
};

struct PACKET {
    enum PACKET_TYPE type;
    char taskID[16];
    wchar_t data[512];
    int currentIndex;
    int finalIndex;
};

class packet {
public:
    static struct INFO getInfo(struct PACKET *packet);
};


#endif //TIANANMEN_PACKET_H
