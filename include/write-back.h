#ifndef _WRITE_BACK
#define _WRITE_BACK

typedef struct _write_back write_back_t;

#include <register.h>
#include <mem.h>
#include <mux.h>

struct _write_back
{
    reg_file_t * reg;
    mem_t* mem;

    mux3_t * mux3_MemtoReg;
};

void init_write_back(write_back_t *wr_back, mem_t *mem, reg_file_t *reg, mux3_t * mux3_MemtoReg);
void write_back_clock(write_back_t *wr_back);
#endif