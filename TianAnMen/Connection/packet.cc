//
// Created by LUNAFE on 2022-02-04.
//

#include "packet.h"

int packet::Send(SOCKET socket) {
    PACKET send_packet;
    send_packet.type = packet::type;

    memmove(send_packet.task_id, packet::task_id, sizeof(send_packet.task_id));

    memmove(send_packet.data, packet::data, sizeof(send_packet.data));

    send_packet.current_index = packet::current_index;
    send_packet.final_index = packet::final_index;

    if (send(socket, (char *) &send_packet, PACKET_SIZE, 0) == -1) {
        return -1;
    } else {
        return 0;
    }
}

int packet::Receive(SOCKET socket) {
    char buf[PACKET_SIZE];

    if (recv(socket, (char *) buf, PACKET_SIZE, 0) == -1) {
        return -1;
    } else {
        PACKET *packet_ = (PACKET *) &buf;
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

void packet::set_data(wchar_t *data_) {
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

wchar_t *packet::get_data() {
    return data;
}

int *packet::get_current_index() {
    return &(current_index);
}

int *packet::get_final_index() {
    return &(final_index);
}
