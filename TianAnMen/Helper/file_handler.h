//
// Created by LUNAFE on 2022-02-12.
//

#ifndef TIANANMEN_FILE_HANDLER_H
#define TIANANMEN_FILE_HANDLER_H

#include <windows.h>
#include <winsock2.h>

#include "../Connection/packet.h"

class file_handler {
private:
    wchar_t file_data[512];
    wchar_t file_path[MAX_PATH];
    char task_id[16];
    int current_index;
    int final_index;
public:
    file_handler(wchar_t *file_path_);
    void InitHandle();
    void ReadData();

    static void SendFileThread(SOCKET socket, wchar_t *file_path_);
};


#endif //TIANANMEN_FILE_HANDLER_H
