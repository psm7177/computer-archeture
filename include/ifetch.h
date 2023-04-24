#ifndef _IFETCH
#define _IFETCH

#include <mips-memory.h>
#include <stdbool.h>

typedef struct _ifetch ifetch_t;

struct _ifetch{
    unsigned int pc;
    memory_t *mem;
    unsigned int Instr;
    unsigned int next_pc;
    int count_exe_instr;
    int max_instr;
};

void  init_iftech(ifetch_t * ifetch, memory_t* mem, int max_instr);
bool iftech_clock(ifetch_t * ifetch);

#endif