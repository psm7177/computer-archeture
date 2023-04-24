#include <write-back.h>

void init_write_back(write_back_t *wr_back, mem_t *mem, reg_file_t *reg, mux3_t *mux3_MemtoReg)
{
    wr_back->mem = mem;
    wr_back->reg = reg;
    wr_back->mux3_MemtoReg = mux3_MemtoReg;
}

void write_back_clock(write_back_t *wr_back)
{
    wr_back->mux3_MemtoReg->signal = wr_back->mem->MemtoReg;

    uint32_t word = mux3(wr_back->mux3_MemtoReg, wr_back->mem->result, wr_back->mem->read_data, wr_back->mem->next_pc);

    if (wr_back->mem->RegWrite)
    {
        write_register(wr_back->reg, wr_back->mem->write_addr, word);
    }
}