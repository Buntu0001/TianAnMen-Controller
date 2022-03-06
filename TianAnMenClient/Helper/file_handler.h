//
// Created by LUNAFE on 2022-02-10.
//

#ifndef TIANANMENCLIENT_FILE_HANDLER_H
#define TIANANMENCLIENT_FILE_HANDLER_H

#include <string.h>
#include <thread>

#include "file_handle_list.h"
#include "../Connection/packet.h"


class FileHandler {
private:
    char file_buffer[1024];
    char task_id[16];
    int current_index;
    int final_index;
    LARGE_INTEGER stack;

    static void NewFileTransfer();
    int AddData(char *file_data_, int index);
    void IssueFile();

    static SOCKET *Connected();
    static void MakeInitTransfer(class Packet *packet_);

public:
    FileHandler(char *task_id_, int final_index_);

    static void ReceiveFileThread();
};


#endif //TIANANMENCLIENT_FILE_HANDLER_H
