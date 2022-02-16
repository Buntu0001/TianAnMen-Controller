//
// Created by LUNAFE on 2022-02-10.
//

#ifndef TIANANMENCLIENT_FILE_HANDLER_H
#define TIANANMENCLIENT_FILE_HANDLER_H

#include <string.h>
#include <thread>

#include "file_handle_list.h"
#include "../Connection/packet.h"


class file_handler {
private:
    char file_buffer[1024];
    char task_id[16];
    int current_index;
    int final_index;
    DWORD stack = 0;

    static void NewFileTransfer();
    int AddData(char *file_data_, int index);
    void IssueFile();

public:
    file_handler(char *task_id_, int final_index_);

    static void ReceiveFileThread();
};


#endif //TIANANMENCLIENT_FILE_HANDLER_H
