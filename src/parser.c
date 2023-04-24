#include <parser.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

unsigned int str_hex2int(char *str_hex){
    str_hex += 2;
    return strtol(str_hex, NULL,16);
}

void slice_str(char* dst, char* src, size_t start, size_t end)
{
    strncpy(dst, src + start, end - start);
    dst[end - start] = '\0';
}
