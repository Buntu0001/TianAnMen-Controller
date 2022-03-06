//
// Created by LUNAFE on 2022-02-13.
//

#include "file_handle_list.h"

handle_list_t FileHandlerList::file_map = MakeMap();

handle_list_t FileHandlerList::MakeMap() {
    return handle_list_t();
}

void FileHandlerList::Add(char *task_id_, FileHandler *handle) {
    file_map.insert(handle_pair_t(task_id_, handle));
}

FileHandler *FileHandlerList::Get(char *task_id) {
    if (file_map.find(task_id) != file_map.end()) {
        return file_map[task_id];
    } else {
        return nullptr;
    }
}

void FileHandlerList::Remove(char *task_id) {
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

void FileHandlerList::Clear() {
    file_map.clear();
}