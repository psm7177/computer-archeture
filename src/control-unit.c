#include <control-unit.h>
#include <stdint.h>
#include <dec.h>

void init_control_unit(control_unit_t *ctrl_unit, reg_file_t *reg_file, dec_t *dec)
{
    ctrl_unit->reg_file = reg_file;
    ctrl_unit->dec = dec;
};

void set_control_flag(control_unit_t *ctrl_unit, uint8_t opcode, uint8_t funct)
{
    uint8_t ALUOp = convert_ALUOp(opcode); // TODO: set any way
    ctrl_unit->dec->ALUOp = ALUOp;
    ctrl_unit->dec->mux2_RegDst->signal = convert_RegDst(opcode);
    ctrl_unit->dec->ALUSrc = convert_ALUSrc(opcode);
    ctrl_unit->dec->Branch = convert_Branch(opcode);
    ctrl_unit->dec->RegWrite = convert_RegWrite(opcode, funct);
    ctrl_unit->dec->MemWrite = convert_MemWrite(opcode);
    ctrl_unit->dec->MemtoReg = convert_MemToReg(opcode);
    ctrl_unit->dec->MemRead = convert_MemRead(opcode);
    ctrl_unit->dec->BranchNot = convert_BranchNot(opcode);
    ctrl_unit->dec->MemByte = convert_MemByte(opcode);
}

uint8_t convert_ALUOp(uint8_t opcode)
{
    switch (opcode)
    {
    case R:
        return ALUOP_R;
    case ADDIU:
        return ALUOP_ADD;
    case ANDI:
        return ALUOP_AND;
    case BEQ:
    case BNE:
        return ALUOP_BEQ;
    case J:
    case JAL:
        return ALUOP_J;
    case LW:
    case LB:
        return ALUOP_LW;
    case LUI: // TODO: make module
    case ORI:
        return ALUOP_OR;
    case SLTIU:
        return ALUOP_SLT;
    case SW:
    case SB:
        return ALUOP_SW;
    }
}

bool convert_RegDst(uint8_t opcode) // 1-> rd 0 -> rt
{
    switch (opcode)
    {
    case R:
    case BEQ:
    case BNE:
    case SW:
    case SB:
    case J:
    case JAL:
        return 1;
    case ADDIU:
    case ANDI:
    case SLTIU:
    case LUI: // TODO: make module
    case LW:
    case LB:
    case ORI:
        return 0;
    }
}

bool convert_ALUSrc(uint8_t opcode) // 1-> rd 0 -> rt
{
    switch (opcode)
    {
    case R:
    case BEQ:
    case BNE:
    case J:
    case JAL:
        return 0;
    case ORI:
    case LUI: // TODO: make module
    case ANDI:
    case ADDIU:
    case SLTIU:
    case SW:
    case SB:
    case LW:
    case LB:
        return 1;
    }
}

bool convert_Branch(uint8_t opcode) 
{
    switch (opcode)
    {
    case BEQ:
    case BNE:
        return 1;
    case R:
    case J:
    case JAL:
    case ADDIU:
    case ANDI:
    case SLTIU:
    case LUI: // TODO: make module
    case ORI:
    case SW:
    case SB:
    case LW:
    case LB:
        return 0;
    }
}

bool convert_MemWrite(uint8_t opcode)
{
    switch (opcode)
    {
    case SW:
    case SB:
        return 1;
    case BEQ:
    case BNE:
    case R:
    case J:
    case JAL:
    case ADDIU:
    case ANDI:
    case SLTIU:
    case LUI: // TODO: make module
    case ORI:
    case LW:
    case LB:
        return 0;
    }
}

bool convert_MemRead(uint8_t opcode)
{
    switch (opcode)
    {
    case LW:
    case LB:
        return 1;
    case SW:
    case SB:
    case BEQ:
    case BNE:
    case R:
    case J:
    case JAL:
    case ADDIU:
    case ANDI:
    case SLTIU:
    case LUI: // TODO: make module
    case ORI:
        return 0;
    }
}

uint8_t convert_MemToReg(uint8_t opcode)
{
    switch (opcode)
    {
    case LW:
    case LB:
        return 1;
    case SW:
    case SB:
    case BEQ:
    case BNE:
    case R:
    case J:
    case ADDIU:
    case ANDI:
    case SLTIU:
    case LUI: // TODO: make module
    case ORI:
        return 0;
    case JAL:
        return 2;
    }
}

bool convert_RegWrite(uint8_t opcode, uint8_t funct)
{
    switch (opcode)
    {
    case R:
        switch (funct)
        {
        case FUNCT_JR:
            return 0;
        }
    case LW:
    case LB:
    case ADDIU:
    case ANDI:
    case SLTIU:
    case ORI:
    case LUI: // TODO: make module
    case JAL:
        return 1;
    case SW:
    case SB:
    case BEQ:
    case BNE:
    case J:
        return 0;
    }
}

bool convert_BranchNot(uint8_t opcode)
{
    switch (opcode)
    {
    case BNE:
        return 1;
    case LW:
    case LB:
    case R:
    case ADDIU:
    case ANDI:
    case SLTIU:
    case ORI:
    case LUI:
    case SW:
    case SB:
    case BEQ:
    case J:
    case JAL:
        return 0;
    }
}

bool convert_MemByte(uint8_t opcode)
{
    switch (opcode)
    {
    case LB:
    case SB:
        return 1;
    case BNE:
    case LW:
    case R:
    case ADDIU:
    case ANDI:
    case SLTIU:
    case ORI:
    case LUI:
    case SW:
    case BEQ:
    case J:
    case JAL:
        return 0;
    }
}