//
// Created by LUNAFE on 2022-02-10.
//

#ifndef TIANANMENCLIENT_FILE_HANDLE_LIST_H
#define TIANANMENCLIENT_FILE_HANDLE_LIST_H

#include <map>
#include <iostream>

#include "file_handler.h"

typedef std::map<char *, class FileHandler *> handle_list_t;
typedef std::pair<char *, class FileHandler *> handle_pair_t;

class FileHandlerList {
private:
    static handle_list_t file_map;

    static handle_list_t MakeMap();

public:
    static void Add(char *task_id, FileHandler *handle);

    static FileHandler *Get(char *task_id);

    static void Remove(char *task_id);

    static void Clear();
};


#endif //TIANANMENCLIENT_FILE_HANDLE_LIST_H
