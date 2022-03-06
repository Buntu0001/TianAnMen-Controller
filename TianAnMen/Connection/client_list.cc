//
// Created by LUNAFE on 2022-02-09.
//

#include "client_list.h"

list_t ClientList::list = MakeVector();

void ClientList::Add(Client *client_) {
    list.push_back(client_);
}

void ClientList::Remove(int index) {
    list.erase(list.begin() + index);
}

void ClientList::Remove(SOCKET socket) {
    for (auto iter = ClientList::Begin(); iter != ClientList::End();) {
        if ((SOCKET)((Client * )(*iter)->GetSocket()) == socket) {
            iter = list.erase(iter);
#ifdef DEBUG
            wprintf(L"[DEBUG] CLIENT_REMOVED\n");
#endif
        } else {
            iter++;
        }
    }
}

int ClientList::GetSize() {
    return list.size();
}

iterator_t ClientList::Begin() {
    return list.begin();
}

iterator_t ClientList::End() {
    return list.end();
}

list_t ClientList::MakeVector() {
    list_t v;
    return v;
}

