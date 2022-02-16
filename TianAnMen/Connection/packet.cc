//
// Created by LUNAFE on 2022-02-04.
//

#include "packet.h"

uint8_t key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
uint8_t iv[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

/*
uint8_t *packet::key = InitKey();
uint8_t *packet::iv = InitIV();

uint8_t *packet::InitKey() {
    uint8_t key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    return key;
}

uint8_t *packet::InitIV() {
    uint8_t iv_[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    return iv_;
}
 */

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
