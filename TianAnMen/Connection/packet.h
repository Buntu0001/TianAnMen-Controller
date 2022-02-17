//
// Created by LUNAFE on 2022-02-04.
//

#ifndef TIANANMEN_PACKET_H
#define TIANANMEN_PACKET_H

#include <winsock2.h>

#include "../Misc/structure.h"
#include "../Misc/util.h"
#include "../Misc/aes.h"

class packet {
private:
    enum PACKET_TYPE type;
    char task_id[16];
    char data[1024];
    int current_index;
    int final_index;

    static uint8_t key[];
    static uint8_t iv[];

public:
    void set_type(PACKET_TYPE type_);

    void set_task_id(char *task_id_);

    void set_data(char *data_);

    void set_current_index(int current_index_);

    void set_final_index(int final_index_);

    PACKET_TYPE *get_type();

    char *get_task_id();

    char *get_data();

    int *get_current_index();

    int *get_final_index();

    int Send(SOCKET socket);

    int Receive(SOCKET socket);
};


#endif //TIANANMEN_PACKET_H
