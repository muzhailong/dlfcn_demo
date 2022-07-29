#ifndef LIB_COMMON_H
#define LIB_COMMON_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
const static int MAX_NAME_LEN = 20;

void get_name(char buf[MAX_NAME_LEN]);
void action();

#ifdef __cplusplus
}
#endif

#endif