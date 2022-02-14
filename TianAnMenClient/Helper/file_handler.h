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
    wchar_t *file_data = new wchar_t;
    wchar_t file_buffer[512];
    char task_id[16];
    int final_index;

    static void NewFileTransfer();
    int AddData(wchar_t *file_data_, int index);
    void IssueFile();

public:
    file_handler(char *task_id_, int final_index_);

    static void ReceiveFileThread();
};


#endif //TIANANMENCLIENT_FILE_HANDLER_H
