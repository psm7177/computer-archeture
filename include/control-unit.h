#ifndef _CONTROL_UNIT
#define _CONTROL_UNIT

typedef struct _control_unit control_unit_t;

#define R 0x0

#define ADDIU 0x9
#define ANDI 0xc
#define BEQ 0x4
#define BNE 0x5
#define LUI 0xf
#define LW 0x23
#define LB 0x20
#define ORI 0xd
#define SLTIU 0xb
#define SW 0x2b
#define SB 0x28

#define J 0x2
#define JAL 0x3

#define ALUOP_ADD 0b010
#define ALUOP_SUB 0b110
#define ALUOP_AND 0b000
#define ALUOP_OR 0b001
#define ALUOP_SLT 0b111
#define ALUOP_LW 0b010
#define ALUOP_SW 0b010
#define ALUOP_BEQ 0b110
#define ALUOP_R 0b100
#define ALUOP_J 0b1111

#define ALU_CTRL_AND 0b0000
#define ALU_CTRL_OR 0b0001
#define ALU_CTRL_ADD 0b0010
#define ALU_CTRL_SUB 0b0110
#define ALU_CTRL_SLT 0b0111
#define ALU_CTRL_NOR 0b1100

#define FUNCT_ADDU 0x21
#define FUNCT_AND 0x24
#define FUNCT_JR 0x8
#define FUNCT_NOR 0x27
#define FUNCT_OR 0x25
#define FUNCT_SLTU 0x2b
#define FUNCT_SLL 0x0
#define FUNCT_SRL 0x2
#define FUNCT_SUBU 0x23

#include <register.h>
#include <stdint.h>
#include <mux.h>
#include <dec.h>

struct _control_unit
{
    reg_file_t *reg_file;
    dec_t *dec;
};

void init_control_unit(control_unit_t *ctrl_unit, reg_file_t *reg_file, dec_t *dec);
void set_control_flag(control_unit_t *ctrl_unit, uint8_t opcode, uint8_t funct);

uint8_t convert_ALUOp(uint8_t opcode);
bool convert_RegDst(uint8_t opcode);
bool convert_ALUSrc(uint8_t opcode);
bool convert_Branch(uint8_t opcode);
bool convert_MemWrite(uint8_t opcode);
bool convert_MemRead(uint8_t opcode);
uint8_t convert_MemToReg(uint8_t opcode);
bool convert_RegWrite(uint8_t opcode, uint8_t funct);
bool convert_BranchNot(uint8_t opcode);
bool convert_MemByte(uint8_t opcode); // TODO: implement

#endif