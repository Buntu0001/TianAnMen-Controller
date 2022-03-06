//
// Created by LUNAFE on 2022-01-29.
//

#include "main.h"

bool main::isActive = false;

std::vector<std::wstring> main::SplitCommand(std::wstring command, wchar_t delimiter) {
    std::vector<std::wstring> split;
    std::wstringstream stream(command);
    std::wstring buffer;

    while (std::getline(stream, buffer, delimiter)) {
        split.push_back(buffer);
    }

    return split;
}

void count() {
    while (true) {
#ifdef DEBUG
        wprintf(L"[DEBUG] COUNT: %d\n", ClientList::GetSize());
        Sleep(1000);
#endif
    }
}

int main() {
    _wsetlocale(LC_ALL, L"korean");
    std::thread handle_thread(Handling::SocketInit);
    handle_thread.detach();

    //std::thread count_thread(count);
    //count_thread.detach();

    while (true) {
        try {
            std::wstring command_buffer;
            wprintf(L"Controller> ");
            std::getline(std::wcin, command_buffer);
            if (!command_buffer.empty()) {
                std::vector<std::wstring> split = main::SplitCommand(command_buffer, L' ');
                if (split[0] == L"test") {
                    wprintf(L"ACTIVE\n");
                    struct COMMAND cmd;
                    cmd.type = COMMAND_TYPE::FILE_UPLOAD;
                    const wchar_t *data = split[1].c_str();;
                    memmove(cmd.data, data, 512);
                    wprintf(L"%S\n", cmd.data);
                    for (auto iter = ClientList::Begin(); iter != ClientList::End(); iter++) {
                        printf("FOUND!\n");
                        ((Client *) *iter)->SetCommand(&cmd);
                        printf("FOUND!22\n");
                    }
                }
            }
        } catch (int ex) {
            wprintf(L"[ERROR] CODE: %d\n", ex);
            return -1;
        }
    }
}
