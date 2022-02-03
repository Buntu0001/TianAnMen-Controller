//
// Created by LUNAFE on 2022-02-04.
//

#include "eventhandler.h"

void eventhandler::getComputerName(wchar_t *buf) {
    unsigned long len = 100;
    GetComputerNameW(buf, &len);
}
