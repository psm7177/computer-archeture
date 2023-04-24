#ifndef _MEMORY
#define _MEMORY

#define TEXT_SECTION_ADDR 0x00400000
#define DATA_SECTION_ADDR 0x10000000

#define WORD_SIZE 4
#include <stddef.h>
#include <stdint.h>

typedef struct _memory memory_t;

struct _memory
{
    size_t size_data;
    size_t size_text;
    void* data;
    void* text;
};

void init_memory(memory_t *mem, size_t text_size, size_t data_size);

uint32_t read_word(memory_t *mem, uint32_t addr);
void write_word(memory_t * mem, uint32_t addr, uint32_t word);

int32_t read_byte(memory_t *mem, uint32_t addr);
void write_byte(memory_t *mem, uint32_t addr, uint8_t word);

uint32_t big2little(uint32_t word);
uint32_t little2big(uint32_t word);
#endif