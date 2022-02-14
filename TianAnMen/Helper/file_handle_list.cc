//
// Created by LUNAFE on 2022-02-13.
//

#include "file_handle_list.h"

handle_list_t file_handle_list::file_map = MakeMap();

handle_list_t file_handle_list::MakeMap() {
    return handle_list_t();
}

void file_handle_list::Add(char *task_id_, file_handler *handle) {
    file_map.insert(handle_pair_t(task_id_, handle));
}

file_handler *file_handle_list::Get(char *task_id) {
    if (file_map.find(task_id) != file_map.end()) {
        return file_map[task_id];
    } else {
        return nullptr;
    }
}

void file_handle_list::Remove(char *task_id) {
    for (auto iter = file_map.begin(); iter != file_map.end();) {
        if (strcmp(task_id, &(*iter->first)) == 0) {
            iter = file_map.erase(iter);
#ifdef DEBUG
            wprintf(L"[DEBUG] HANDLE_REMOVE\n");
#endif
        } else {
            iter++;
        }
    }
}

void file_handle_list::Clear() {
    file_map.clear();
}