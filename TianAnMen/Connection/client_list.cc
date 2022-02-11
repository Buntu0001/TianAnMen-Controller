//
// Created by LUNAFE on 2022-02-09.
//

#include "client_list.h"

list_t client_list::list = MakeVector();

void client_list::Add(client *client_) {
    list.push_back(client_);
}

void client_list::Remove(int index) {
    list.erase(list.begin() + index);
}

void client_list::Remove(SOCKET socket) {
    for (auto iter = client_list::Begin(); iter != client_list::End();) {
        if ((SOCKET) ((client *) (*iter)->GetSocket()) == socket) {
            iter = list.erase(iter);
#ifdef DEBUG
            wprintf(L"[DEBUG] CLIENT_REMOVED\n");
#endif
        } else {
            iter++;
        }
    }
}

int client_list::GetSize() {
    return list.size();
}

iterator_t client_list::Begin() {
    return list.begin();
}

iterator_t client_list::End() {
    return list.end();
}

list_t client_list::MakeVector() {
    list_t v;
    return v;
}

