//
// Created by LUNAFE on 2022-02-04.
//

#include "packet.h"

int packet::Send() {
    PACKET send_packet;
    send_packet.type = type;

    memmove(send_packet.task_id, task_id, sizeof(send_packet.task_id));

    memmove(send_packet.data, data, sizeof(send_packet.data));

    send_packet.current_index = current_index;
    send_packet.final_index = final_index;

    if (send(main::sock, (char *) &send_packet, PACKET_SIZE, 0) == -1) {
        return -1;
    } else {
        return 0;
    }
}

int packet::Receive() {
    char buf[PACKET_SIZE];

    if (recv(main::sock, (char *) buf, PACKET_SIZE, 0) == -1) {
        return -1;
    } else {
        PACKET *packet_ = (PACKET *) &buf;

        if (packet_->type == PACKET_TYPE::PING && packet_->data[0] == 1 && packet_->data[1] == 2 &&
            packet_->data[2] == 3 &&
            packet_->data[3] == 4) {
            set_type(packet_->type);
            set_task_id(packet_->task_id);
            set_data(packet_->data);
            set_current_index(packet_->current_index);
            set_final_index(packet_->final_index);
            return 1;
        } else if (packet_->type == PACKET_TYPE::FILE_DATA) {
            set_type(packet_->type);
            set_task_id(packet_->task_id);
            set_data(packet_->data);
            set_current_index(packet_->current_index);
            set_final_index(packet_->final_index);
            return 0;
        }
    }
}

void packet::Execute() {

}

void packet::set_type(PACKET_TYPE type_) {
    type = type_;
}

void packet::set_task_id(char *task_id_) {
    memmove(task_id, task_id_, sizeof(task_id));
}

void packet::set_data(wchar_t *data_) {
    memmove(data, data_, sizeof(data));
}

void packet::set_current_index(int current_index_) {
    current_index = current_index_;
}

void packet::set_final_index(int final_index_) {
    final_index = final_index_;
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
    return &(current_index);
}



