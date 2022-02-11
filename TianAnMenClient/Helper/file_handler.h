//
// Created by LUNAFE on 2022-02-10.
//

#ifndef TIANANMENCLIENT_FILE_HANDLER_H
#define TIANANMENCLIENT_FILE_HANDLER_H

#include <string.h>

class file_handler {
private:
    wchar_t *file_data = new wchar_t;
    char task_id[16];
    int current_index = 0;
    int final_index = 0;
public:
    file_handler(char task_id_[16], wchar_t file_data_[512], int final_index_);
};


#endif //TIANANMENCLIENT_FILE_HANDLER_H
