#ifndef _MEM
#define _MEM

typedef struct _mem mem_t;

#include <mips-memory.h>
#include <execute.h>

struct _mem
{
    memory_t *memory;
    execute_t *ex;


    uint8_t MemtoReg;
    bool RegWrite;

    uint8_t write_addr;

    uint32_t next_pc;
    uint32_t result;
    uint32_t read_data;
};

void init_mem(mem_t *mem, execute_t *ex, memory_t *memory);
void mem_clock(mem_t *mem);

#endif
