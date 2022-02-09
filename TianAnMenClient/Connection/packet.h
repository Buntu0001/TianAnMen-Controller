//
// Created by LUNAFE on 2022-02-04.
//

#ifndef TIANANMENCLIENT_PACKET_H
#define TIANANMENCLIENT_PACKET_H

#include "../main.h"
#include "../Misc/structure.h"


class packet {
public:
    static int ParsePacket(struct PACKET *packet);

    static void MakePong(struct PACKET *packet_);

    static void SendInfo();

    static void Init(struct PACKET *packet);
};


#endif //TIANANMENCLIENT_PACKET_H
