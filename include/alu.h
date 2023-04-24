#ifndef _ALU
#define _ALU

typedef struct _alu alu_t;
#include <stddef.h>
#include <stdint.h>

struct _alu
{
    uint8_t ALUcontrol;
};

int32_t alu(uint8_t ALUcontrol, int32_t left, int32_t right);

#endif