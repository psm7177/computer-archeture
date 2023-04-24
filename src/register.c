#include <register.h>
#include <stdio.h>
#include <debug.h>
void init_reg_file(reg_file_t *reg_file)
{
    for (int i = 0; i < NUM_REG; i++)
    {
        reg_file->reg[i] = 0;
    }
}

uint32_t read_register(reg_file_t *reg_file, uint8_t addr)
{
    dbprintf("read register: %d\n", addr);
    return reg_file->reg[addr];
}

void write_register(reg_file_t *reg_file, uint8_t addr, uint32_t value)
{
    dbprintf("write register: %d %x\n", addr, value);

    reg_file->reg[addr] = value;
    dbprintf("written register: %d %x", addr, reg_file->reg[addr]);
}