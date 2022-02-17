//
// Created by LUNAFE on 2022-02-04.
//

#include "packet.h"

uint8_t packet::key[] = {0x15, 0x3e, 0x1f, 0xa5, 0x1a, 0xaf, 0xbd, 0x6a, 0xbb, 0xe1, 0x0e, 0xc8, 0xfe, 0x1c, 0x1d, 0x3e};
uint8_t packet::iv[] = {0x4a, 0x3f, 0xcc, 0x1d, 0xda, 0x52, 0x35, 0x18, 0xc9, 0xb0, 0x0a, 0x4d, 0x7e, 0xf2, 0x1c, 0xdc};

int packet::Send(SOCKET socket) {
    PACKET send_packet;
    send_packet.type = type;

    memmove(send_packet.task_id, task_id, sizeof(send_packet.task_id));

    memmove(send_packet.data, data, sizeof(send_packet.data));

    send_packet.current_index = current_index;
    send_packet.final_index = final_index;

    uint8_t *encrypt = (uint8_t *) &send_packet;

    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);

    AES_CBC_encrypt_buffer(&ctx, encrypt, sizeof(PACKET));

    if (send(socket, (char *) encrypt, PACKET_SIZE, 0) == -1) {
        return -1;
    } else {
        return 0;
    }
}

int packet::Receive(SOCKET socket) {
    char buf[PACKET_SIZE];

    if (recv(socket, (char *) buf, PACKET_SIZE, 0) == -1) {
        printf("[ERROR] %d\n", WSAGetLastError());
        return -1;
    } else {
        uint8_t *decrypt = (uint8_t *) buf;

        struct AES_ctx ctx;
        AES_init_ctx_iv(&ctx, key, iv);

        AES_CBC_decrypt_buffer(&ctx, decrypt, sizeof(PACKET));

        PACKET *packet_ = (PACKET *) decrypt;

        if (packet_->type == PACKET_TYPE::PING) {
            set_type(packet_->type);
            set_task_id(packet_->task_id);
            set_data(packet_->data);
            set_current_index(packet_->current_index);
            set_final_index(packet_->final_index);
            return 0;
        } else if (packet_->type == PACKET_TYPE::INFO) {
            set_type(packet_->type);
            set_task_id(packet_->task_id);
            set_data(packet_->data);
            set_current_index(packet_->current_index);
            set_final_index(packet_->final_index);
            return 1;
        } else if (packet_->type == PACKET_TYPE::FILE_SERVER_TO_CLIENT) {
            set_type(packet_->type);
            set_task_id(packet_->task_id);
            set_data(packet_->data);
            set_current_index(packet_->current_index);
            set_final_index(packet_->final_index);
            return 2;
        }
    }
}

void packet::set_type(PACKET_TYPE type_) {
    packet::type = type_;
}

void packet::set_task_id(char *task_id_) {
    memmove(packet::task_id, task_id_, sizeof(packet::task_id));
}

void packet::set_data(char *data_) {
    memmove(packet::data, data_, sizeof(packet::data));
}

void packet::set_current_index(int current_index_) {
    packet::current_index = current_index_;
}

void packet::set_final_index(int final_index_) {
    packet::final_index = final_index_;
}

PACKET_TYPE *packet::get_type() {
    return &(type);
}

char *packet::get_task_id() {
    return task_id;
}

char *packet::get_data() {
    return data;
}

int *packet::get_current_index() {
    return &(current_index);
}

int *packet::get_final_index() {
    return &(final_index);
}
