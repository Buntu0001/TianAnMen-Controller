//
// Created by LUNAFE on 2022-02-04.
//

#include "packet.h"

void packet::MakePing(struct PACKET *packet_) {
    struct PACKET packet;
    packet.type = PACKET_TYPE::PING;
    util::GenId(packet.task_id, 16);
    for (int i = 0; i < 4; i++) {
        packet.data[i] = i + 1;
    }
    packet.current_index = 0;
    packet.final_index = 0;

    memmove(packet_, &packet, sizeof(packet));
}
