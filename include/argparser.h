#ifndef _ARGPARSER
#define _ARGPARSER

#include <stdbool.h>

typedef struct _argparser argparser_t;

struct _argparser{
    bool option_m;
    bool option_d;
    bool option_n;
    unsigned int addr1;
    unsigned int addr2;
    int num_instruction;
    char* filename;
};

argparser_t parse_argument(int argc, char *argv[]);

int parse_option_m(argparser_t *arg, char *str);
int parse_option_n(argparser_t *arg, char *str);
int parse_filename(argparser_t *arg, char *str);

#endif