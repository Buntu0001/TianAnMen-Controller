//
// Created by LUNAFE on 2022-02-04.
//

#ifndef TIANANMEN_PACKET_H
#define TIANANMEN_PACKET_H

#include "../Misc/structure.h"
#include "../Misc/util.h"

class packet {
public:
    static struct INFO GetInfo(struct PACKET *packet);
    static void MakePing(struct PACKET *packet_);
};


#endif //TIANANMEN_PACKET_H
