//
// Created by LUNAFE on 2022-02-09.
//

#ifndef TIANANMEN_CLIENT_LIST_H
#define TIANANMEN_CLIENT_LIST_H

#include <vector>
#include <iostream>

#include "client.h"

typedef std::vector<client *> list_t;
typedef std::vector<client *>::iterator iterator_t;

class client_list {
private:
    static list_t list;

    static list_t MakeVector();

public:
    static void Add(client *client_);

    static void Remove(int index);

    static void Remove(SOCKET socket);

    static int GetSize();

    static iterator_t Begin();

    static iterator_t End();
};

#endif //TIANANMEN_CLIENT_LIST_H
