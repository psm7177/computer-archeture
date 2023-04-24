#include <mem.h>
#include <mips-memory.h>
#include <stdio.h>

void init_mem(mem_t *mem, execute_t *ex, memory_t *memory)
{
    mem->ex = ex;
    mem->memory = memory;
}

void mem_clock(mem_t *mem)
{
    // dbprintf();
    uint32_t read_data = 0;

    if (mem->ex->MemRead)
    {
        if (mem->ex->MemByte)
        {
            read_data = read_byte(mem->memory, mem->ex->result);
        }
        else
        {
            read_data = read_word(mem->memory, mem->ex->result);
        }
    }

    if (mem->ex->MemWrite)
    {
        if (mem->ex->MemByte)
        {
            write_byte(mem->memory, mem->ex->result, mem->ex->write_data);
        }
        else
        {
            write_word(mem->memory, mem->ex->result, mem->ex->write_data);
        }
    }

    mem->read_data = read_data;
    mem->result = mem->ex->result;
    mem->next_pc = mem->ex->next_pc;
    mem->MemtoReg = mem->ex->MemtoReg;
    mem->RegWrite = mem->ex->RegWrite;
    mem->write_addr = mem->ex->write_addr;
}
