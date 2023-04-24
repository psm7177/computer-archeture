#include <dec.h>
#include <stdio.h>
#include <debug.h>
void init_dec(dec_t *dec, ifetch_t *ifetch, control_unit_t *ctrl_unit, reg_file_t *reg_file, mux2_t *mux_regdst, mux4_t *mux_PCSrc)
{
    dec->ifetch = ifetch;
    dec->reg_file = reg_file;
    dec->ctrl_unit = ctrl_unit;
    dec->mux2_RegDst = mux_regdst;
    dec->mux4_PCSrc = mux_PCSrc;
}

void dec_clock(dec_t *dec)
{
    uint32_t instr = dec->ifetch->Instr;
    uint8_t opcode = instr >> 26;
    uint8_t funct = (instr << 26) >> 26;
    dbprintf("opcode: %x\n", opcode);
    dbprintf("funct: %x\n", funct);
    set_control_flag(dec->ctrl_unit, opcode, funct);

    uint8_t addr1 = (instr << 6) >> 27;
    dbprintf("addr1: %x\n", addr1);

    uint32_t data1 = read_register(dec->reg_file, addr1);
    dbprintf("data1: %d\n", data1);
    uint8_t addr2 = (instr << 11) >> 27;
    dbprintf("addr2: %x\n", addr2);

    uint32_t data2 = read_register(dec->reg_file, addr2);
    dbprintf("data2: %d\n", data2);

    uint8_t addr3 = (instr << 16) >> 27;
    dbprintf("addr3: %x\n", addr3);

    uint8_t write_addr = mux2(dec->mux2_RegDst, addr2, addr3);
    dbprintf("write_addr: %x\n", write_addr);

    // lui implement
    uint8_t shamt = (instr << 21) >> 27;
    uint16_t imm = instr;

    

    int32_t ext_imm;
    if (convert_ZeroExtend(opcode))
    {
        ext_imm = zero_extend(imm);
    }
    else
    {
        ext_imm = sign_extend(imm);
    }
    dbprintf("ext_imm: %x\n", ext_imm);

    uint32_t target = ((instr << 6) >> 4) | ((dec->ifetch->pc >> 28) << 28);

    bool Branch = dec->Branch;
    bool BranchNot = dec->BranchNot;
    bool Zero = (data1 - data2) == 0;
    bool Jump = convert_Jump(opcode, funct);
    bool JumpSrc = convert_JumpSrc(opcode, funct);

    dec->mux4_PCSrc->signal = convert_PCSrc(Branch, BranchNot, Zero, Jump, JumpSrc);

    int32_t branch_offset = dec->ifetch->next_pc + (ext_imm << 2);
    dbprintf("PCSrc: %d\n", dec->mux4_PCSrc->signal);
    dbprintf("branch_offset: %x\n", branch_offset);
    dec->ifetch->pc = mux4(dec->mux4_PCSrc, dec->ifetch->next_pc, branch_offset, target, data1);

    dec->next_pc = dec->ifetch->next_pc;

    if (convert_Sll(opcode, funct))
    {
        data2 = sll(data2, shamt);
    }

    if (convert_Srl(opcode, funct))
    {
        data2 = srl(data2, shamt);
    }

    if (convert_Lui(opcode))
    {
        ext_imm = lui(imm);
        dbprintf("lui: %x\n", ext_imm);
    }
    if (convert_Jal(opcode))
    {
        write_addr = RA;
    }

    dec->read_data_1 = data1;
    dec->read_data_2 = data2;

    dec->imm = ext_imm;
    dec->write_addr = write_addr;
    dec->funct = funct;
}

uint32_t zero_extend(uint16_t imm)
{
    return (int32_t)(uint32_t)imm;
}

int32_t sign_extend(uint16_t imm)
{
    return (int32_t)(int16_t)imm;
}

uint32_t sll(uint32_t word, size_t amount)
{
    return word << amount;
}
uint32_t srl(uint32_t word, size_t amount)
{
    return word >> amount;
}
uint32_t lui(uint16_t imm)
{
    return ((uint32_t)imm << 16);
}

bool convert_ZeroExtend(uint8_t opcode)
{
    if (opcode == ANDI || opcode == ORI)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool convert_Sll(uint8_t opcode, uint8_t funct)
{
    if (opcode == R && funct == FUNCT_SLL)
    {
        return 1;
    }
    return 0;
}

bool convert_Srl(uint8_t opcode, uint8_t funct)
{
    if (opcode == R && funct == FUNCT_SRL)
    {
        return 1;
    }
    return 0;
}

bool convert_Lui(uint8_t opcode)
{
    if (opcode == LUI)
    {
        return 1;
    }
    return 0;
}

bool convert_Jal(uint8_t opcode)
{
    if (opcode == JAL)
    {
        return 1;
    }
    return 0;
}

uint8_t convert_PCSrc(bool Branch, bool BranchNot, bool Zero, bool Jump, bool JumpSrc)
{
    // Branch :Branch instr
    // Branch :Not
    // Zero: alu zero
    // Jump: Jump instr
    // JumpSrc:

    // 0 -> if->pc
    // 1 -> branch
    // 2 -> target
    // 3 -> read_data_1

    if (Branch == 1 && Zero != BranchNot)
    {
        return 1;
    }
    if (Jump == 1)
    {
        if (JumpSrc == 0)
        {
            return 2;
        }
        else
        {
            return 3;
        }
    }

    return 0;
}

bool convert_Jump(uint8_t opcode, uint8_t funct)
{
    switch (opcode)
    {
    case J:
    case JAL:
        return 1;
    case R:
        switch (funct)
        {
        case FUNCT_JR:
            return 1;
        default:
            return 0;
        }
        return ALUOP_R;
    case BEQ:
    case BNE:
    case ADDIU:
    case ANDI:
    case LUI: // TODO: make module
    case LW:
    case LB:
    case ORI:
    case SLTIU:
    case SW:
    case SB:
        return 0;
    }
}

bool convert_JumpSrc(uint8_t opcode, uint8_t funct)
{
    switch (opcode)
    {
    case J:
    case JAL:
        return 0;
    case R:
        switch (funct)
        {
        case FUNCT_JR:
            return 1;
        default:
            return 0;
        }
        return ALUOP_R;
    case BEQ:
    case BNE:
    case ADDIU:
    case ANDI:
    case LUI: // TODO: make module
    case LW:
    case LB:
    case ORI:
    case SLTIU:
    case SW:
    case SB:
        return 0;
    }
}
