#include <string.h>

#include <iostream>

#include "lib_common.h"

void get_name(char buf[MAX_NAME_LEN]) {
  const char* s = "hello";
  memcpy(buf, s, strlen(s) + 1);
}

void action() { std::cout << "hello\n"; }
