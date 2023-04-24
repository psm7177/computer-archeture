#ifndef _PARSER
#define _PARSER
#include <stddef.h>

unsigned int str_hex2int(char *str_hex);
void slice_str(char* dst, char* src, size_t start, size_t end);

#endif