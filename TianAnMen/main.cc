//
// Created by LUNAFE on 2022-01-29.
//

#include "main.h"

void count() {
    while (true) {
#ifdef DEBUG
        wprintf(L"[DEBUG] COUNT: %d\n", client_list::GetSize());
        Sleep(1000);
#endif
    }
}

int main() {
    _wsetlocale(LC_ALL, L"korean");

    std::thread handle_thread(handling::Listening);
    handle_thread.detach();

    std::thread count_thread(count);
    count_thread.detach();

    while (true) {
        std::string command_buffer;
        wprintf(L"Controller> ");
        std::getline(std::cin, command_buffer);
    }
}
