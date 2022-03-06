//
// Created by LUNAFE on 2022-01-29.
//

#ifndef TIANANMEN_MAIN_H
#define TIANANMEN_MAIN_H

#include <iostream>
#include <windows.h>
#include <vector>
#include <sstream>

#include "Connection/handling.h"
#include "Connection/client_list.h"
#include "Connection/client.h"

class main {
public:
    static bool isActive;
    static std::vector<std::wstring> SplitCommand(std::wstring command, wchar_t delimiter);
    static class Client selected_client;
};


#endif //TIANANMEN_MAIN_H
