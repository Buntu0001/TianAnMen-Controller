//
// Created by LUNAFE on 2022-02-10.
//

#ifndef TIANANMENCLIENT_FILE_HANDLE_LIST_H
#define TIANANMENCLIENT_FILE_HANDLE_LIST_H

#include <map>
#include <iostream>
#include "file_handler.h"

typedef std::map<char[16], file_handler> handle_list_t;
typedef std::map<char[16], file_handler>::iterator iterator_t;

class file_handle_list {
private:
    static handle_list_t file_map;
    static handle_list_t MakeMap();
public:
    static void Add(char task_id_[16], file_handler handle);
    static void Get(char task_id[16]);
    static void Remove(char task_id[16]);
    static void Clear();
};


#endif //TIANANMENCLIENT_FILE_HANDLE_LIST_H
