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

void util::MakePing(class packet *packet_) {
    packet_->set_type(PACKET_TYPE::PING);

    char id[16];
    util::GenId(id, 16);
    packet_->set_task_id(id);

    wchar_t data_[4] = {1, 2, 3, 4};
    packet_->set_data(data_);

    packet_->set_current_index(0);
    packet_->set_final_index(0);
}
