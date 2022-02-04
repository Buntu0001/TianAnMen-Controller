//
// Created by LUNAFE on 2022-02-04.
//

#ifndef TIANANMENCLIENT_PACKET_H
#define TIANANMENCLIENT_PACKET_H

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
};


#endif //TIANANMENCLIENT_PACKET_H
