//
// Created by LUNAFE on 2022-02-10.
//

#include "file_handler.h"

file_handler::file_handler(char *task_id_, wchar_t *file_data_, int final_index_) {
    memmove(task_id, task_id, sizeof(task_id));
    memmove(file_data, file_data_, sizeof(file_data));
    current_index = 0;
    final_index = final_index_;
}
