#include <string.h>

#include <iostream>

#include "lib_common.h"

#ifdef __cplusplus
extern "C" {
#endif

void get_name(char buf[MAX_NAME_LEN]) {
    const char* s = "world";
    memcpy(buf, s, strlen(s) + 1);
}

void action() { std::cout << "world\n"; }

#ifdef __cplusplus
}
#endif