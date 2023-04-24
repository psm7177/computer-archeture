#include <stdio.h>
#include <stdlib.h>
#include <debug.h>
#include <mips-memory.h>

void init_memory(memory_t *mem, size_t text_size, size_t data_size)
{
    mem->size_data = data_size;
    mem->size_text = text_size;

    mem->data = malloc(mem->size_data);
    mem->text = malloc(mem->size_text);
}

uint32_t read_word(memory_t *mem, uint32_t addr)
{
    if (TEXT_SECTION_ADDR <= addr && addr < TEXT_SECTION_ADDR + mem->size_text)
    {
        int offset = addr - TEXT_SECTION_ADDR;

        uint32_t *p_word = mem->text + offset;
        return big2little(*p_word);
    }

    if (DATA_SECTION_ADDR <= addr && addr < DATA_SECTION_ADDR + mem->size_data)
    {
        int offset = addr - DATA_SECTION_ADDR;
        uint32_t *p_word = mem->data + offset;
        dbprintf("read data addr: %x %x\n", offset, big2little(*p_word));
        return big2little(*p_word);
    }
    return 0;
}

void write_word(memory_t *mem, uint32_t addr, uint32_t word)
{
    if (TEXT_SECTION_ADDR <= addr && addr < TEXT_SECTION_ADDR + mem->size_text)
    {
        int offset = addr - TEXT_SECTION_ADDR;
        *((uint32_t *)(mem->text + offset)) = little2big(word);
        return;
    }

    if (DATA_SECTION_ADDR <= addr && addr < DATA_SECTION_ADDR + mem->size_data)
    {
        int offset = addr - DATA_SECTION_ADDR;
        dbprintf("write word addr: %x\n", offset);
        *((uint32_t *)(mem->data + offset)) = little2big(word);
        return;
    }
}

int32_t read_byte(memory_t *mem, uint32_t addr)
{
    if (TEXT_SECTION_ADDR <= addr && addr < TEXT_SECTION_ADDR + mem->size_text)
    {
        int offset = addr - TEXT_SECTION_ADDR;
        int8_t *p_word = mem->text + offset;
        return *p_word;
    }

    if (DATA_SECTION_ADDR <= addr && addr < DATA_SECTION_ADDR + mem->size_data)
    {
        int offset = addr - DATA_SECTION_ADDR;
        int8_t *p_word = mem->data + offset;
        dbprintf("read data addr: %x %x\n", offset, *p_word);
        return *p_word;
    }
    return 0;
}

void write_byte(memory_t *mem, uint32_t addr, uint8_t word)
{
    if (TEXT_SECTION_ADDR <= addr && addr < TEXT_SECTION_ADDR + mem->size_text)
    {
        int offset = addr - TEXT_SECTION_ADDR;
        *((uint8_t *)(mem->text + offset)) = word;
        return;
    }

    if (DATA_SECTION_ADDR <= addr && addr < DATA_SECTION_ADDR + mem->size_data)
    {
        int offset = addr - DATA_SECTION_ADDR;
        dbprintf("write byte addr: %x\n", offset);
        *((uint8_t *)(mem->data + offset)) = word;
        return;
    }
}

uint32_t big2little(uint32_t word)
{
    return ((word >> 24) & 0xff) |
           ((word << 8) & 0xff0000) |
           ((word >> 8) & 0xff00) |
           ((word << 24) & 0xff000000);
}
uint32_t little2big(uint32_t word)
{
    return ((word & 0x000000ff) << 24) |
           ((word & 0x0000ff00) << 8) |
           ((word & 0x00ff0000) >> 8) |
           ((word & 0xff000000) >> 24);
}