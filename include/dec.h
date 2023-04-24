#ifndef _DEC
#define _DEC

typedef struct _dec dec_t;

#include <ifetch.h>
#include <register.h>
#include <control-unit.h>
#include <mux.h>

struct _dec
{
    ifetch_t *ifetch;
    reg_file_t *reg_file;
    control_unit_t *ctrl_unit;

    mux2_t *mux2_RegDst;
    mux4_t *mux4_PCSrc;

    uint32_t next_pc;
    int32_t read_data_1;
    int32_t read_data_2;
    int32_t imm;
    uint8_t write_addr;
    uint8_t funct;

    uint8_t ALUOp;
    bool ALUSrc;

    bool Branch;
    bool BranchNot;
    bool MemWrite;
    bool MemRead;
    bool MemByte;

    uint8_t MemtoReg;
    bool RegWrite;
};

void init_dec(dec_t *dec, ifetch_t *ifetch, control_unit_t *ctrl_unit, reg_file_t *reg_file, mux2_t *mux_regdst, mux4_t *mux_PCSrc);
void dec_clock(dec_t *dec);

uint32_t zero_extend(uint16_t imm);
int32_t sign_extend(uint16_t imm);
uint32_t sll(uint32_t word, size_t amount);
uint32_t srl(uint32_t word, size_t amount);
uint32_t lui(uint16_t imm);

bool convert_ZeroExtend(uint8_t opcode);
bool convert_Sll(uint8_t opcode, uint8_t funct);
bool convert_Srl(uint8_t opcode, uint8_t funct);
bool convert_Lui(uint8_t opcode);
bool convert_Jal(uint8_t opcode);

bool convert_Jump(uint8_t opcode, uint8_t funct);
bool convert_JumpSrc(uint8_t opcode, uint8_t funct);
uint8_t convert_PCSrc(bool Branch, bool BranchNot, bool Zero, bool Jump, bool JumpSrc);
#endif