//
// Created by LUNAFE on 2022-02-04.
//

#include "util.h"

void Util::GenId(char *buf, int len) {
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

void Util::MakePing(class Packet *packet_) {
    packet_->set_type(PACKET_TYPE::PING);

    char id[16];
    Util::GenId(id, 16);
    packet_->set_task_id(id);

    char data_[4] = {1, 2, 3, 4};
    packet_->set_data(data_);

    packet_->set_current_index(0);
    packet_->set_final_index(0);
}

void Util::CharToWchar(wchar_t *dest, char *src) {
    int w_size = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, NULL);
    MultiByteToWideChar(CP_UTF8, 0, src, strlen(src) + 1, dest, w_size);
}

void Util::WcharToChar(char *dest, wchar_t *src) {
    int c_size = WideCharToMultiByte(CP_UTF8, 0, src, -1, NULL, 0, NULL, NULL);
    WideCharToMultiByte(CP_UTF8, 0, src, -1, dest, c_size, NULL, NULL);
}
