#include <alu.h>
#include <control-unit.h>

int32_t alu(uint8_t ALUcontrol, int32_t left, int32_t right)
{
    switch (ALUcontrol)
    {
    case ALU_CTRL_ADD:
        return left + right;
    case ALU_CTRL_AND:
        return left & right;
    case ALU_CTRL_NOR:
        return ~(left | right);
    case ALU_CTRL_OR:
        return left | right;
    case ALU_CTRL_SLT:
        return left < right;
    case ALU_CTRL_SUB:
        return left - right;
    default:
        break;
    }
}

