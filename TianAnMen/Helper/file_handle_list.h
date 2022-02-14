//
// Created by LUNAFE on 2022-02-13.
//

#ifndef TIANANMEN_FILE_HANDLE_LIST_H
#define TIANANMEN_FILE_HANDLE_LIST_H

#include <map>
#include <iostream>

#include "file_handler.h"

typedef std::map<char *, class file_handler *> handle_list_t;
typedef std::pair<char *, class file_handler *> handle_pair_t;

class file_handle_list {
private:
    static handle_list_t file_map;

    static handle_list_t MakeMap();
public:
    static void Add(char *task_id, file_handler *handle);

    static file_handler *Get(char *task_id);

    static void Remove(char *task_id);

    static void Clear();
};


#endif //TIANANMEN_FILE_HANDLE_LIST_H
