#include <ifetch.h>
#include <stdbool.h>

void init_iftech(ifetch_t *ifetch, memory_t *mem, int max_instr)
{
    ifetch->pc = TEXT_SECTION_ADDR;
    ifetch->mem = mem;
    ifetch->count_exe_instr = 0;
    ifetch->max_instr = max_instr;
}

bool iftech_clock(ifetch_t *ifetch)
{
    if (ifetch->max_instr != -1 && ifetch->max_instr <= ifetch->count_exe_instr)
    {
        return false;
    }
    if (TEXT_SECTION_ADDR <= ifetch->pc && ifetch->pc < TEXT_SECTION_ADDR + ifetch->mem->size_text)
    {
        ifetch->Instr = read_word(ifetch->mem, ifetch->pc);
        ifetch->pc += WORD_SIZE;
        ifetch->next_pc = ifetch->pc;
        ifetch->count_exe_instr++;
        return true;
    }

    return false;
}
