#ifndef _EXECUTE
#define _EXECUTE

typedef struct _execute execute_t;

#include <dec.h>
#include <alu.h>


struct _execute
{
    ifetch_t *ifetch;
    dec_t *dec;
    alu_t *alu;

    mux2_t *mux2_ALUSrc;

    bool MemWrite;
    uint8_t MemtoReg;
    bool MemRead;
    bool Branch;
    bool Zero;
    bool RegWrite;
    bool MemByte;
    
    uint8_t write_addr;
    uint32_t next_pc;

    uint32_t branch_addr;
    uint32_t result;
    uint32_t write_data;
};

void init_execute(execute_t *ex, dec_t *dec, alu_t *alu, mux2_t *mux2_ALUSrc);
void execute_clock(execute_t *ex);

uint8_t convert_ALUcontrol(uint8_t ALUOp, uint8_t funct);


#endif