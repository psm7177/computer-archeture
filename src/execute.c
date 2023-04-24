#include <execute.h>
#include <control-unit.h>
#include <stdio.h>
#include <debug.h>

void init_execute(execute_t *ex, dec_t *dec, alu_t *alu, mux2_t *mux2_ALUSrc)
{
    ex->dec = dec;
    ex->alu = alu;
    ex->mux2_ALUSrc = mux2_ALUSrc;
}

void execute_clock(execute_t *ex)
{
    ex->mux2_ALUSrc->signal = ex->dec->ALUSrc;
    dbprintf("mux2_ALUSrc: %d\n", ex->mux2_ALUSrc->signal);

    uint32_t read_data_2 = ex->dec->read_data_2;
    uint32_t imm = ex->dec->imm;

    uint32_t left = ex->dec->read_data_1;
    uint32_t right = mux2(ex->mux2_ALUSrc, read_data_2, imm);


    uint8_t ALUOp = ex->dec->ALUOp;
    uint8_t funct = ex->dec->funct;
    dbprintf("ALUOp: %d\n", ALUOp);
    dbprintf("funct: %x\n", funct);

    uint8_t ALUcontrol = convert_ALUcontrol(ALUOp, funct);

    uint32_t result = alu(ALUcontrol, left, right);
    dbprintf("alu: %d %d %d\n", ALUcontrol, left, right);
    dbprintf("result: %d\n", result);

    uint32_t branch_addr = ex->dec->next_pc + imm << 2;

    ex->branch_addr = branch_addr;
    ex->write_data = read_data_2;
    ex->next_pc = ex->dec->next_pc;
    ex->result = result;

    ex->Branch = ex->dec->Branch;
    ex->Zero = result == 0;
    ex->MemWrite = ex->dec->MemWrite;
    ex->MemtoReg = ex->dec->MemtoReg;
    ex->MemRead = ex->dec->MemRead;
    ex->MemByte = ex->dec->MemByte;
    ex->RegWrite = ex->dec->RegWrite;
    ex->write_addr = ex->dec->write_addr;
}

uint8_t convert_ALUcontrol(uint8_t ALUOp, uint8_t funct)
{
    switch (ALUOp)
    {
    case ALUOP_ADD:
        return ALU_CTRL_ADD;
    case ALUOP_SUB:
        return ALU_CTRL_SUB;
    case ALUOP_AND:
        return ALU_CTRL_AND;
    case ALUOP_OR:
        return ALU_CTRL_OR;
    case ALUOP_SLT:
        return ALU_CTRL_SLT;
    case ALUOP_R:
        switch (funct)
        {
        case FUNCT_ADDU:
        case FUNCT_JR:
            return ALU_CTRL_ADD;
        case FUNCT_AND:
            return ALU_CTRL_AND;
        case FUNCT_NOR:
            return ALU_CTRL_NOR;
        case FUNCT_OR:
        case FUNCT_SLL:
        case FUNCT_SRL:
            return ALU_CTRL_OR;
        case FUNCT_SLTU:
            return ALU_CTRL_SLT;
        case FUNCT_SUBU:
            return ALU_CTRL_SUB;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

