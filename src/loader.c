#include <stdio.h>
#include <stdlib.h>
#include <mips-memory.h>
#include <loader.h>
#include <parser.h>
#include <stdint.h>
#include <debug.h>

void load_memory(memory_t *mem, char *filename)
{
    FILE *p_file = fopen(filename, "r");

    if (p_file == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char buff[512];

    fscanf(p_file, "%s", buff);
    size_t text_section_size = str_hex2int(buff);
    fscanf(p_file, "%s", buff);
    size_t data_section_size = str_hex2int(buff);
    init_memory(mem, text_section_size, data_section_size);

    for (int i = 0; i < text_section_size; i += WORD_SIZE)
    {
        unsigned int *p_text = mem->text + i;
        fscanf(p_file, "%s", buff);
        unsigned int word = str_hex2int(buff);
        *p_text = big2little(word);
    }

    for (int i = 0; i < data_section_size; i += WORD_SIZE)
    {
        unsigned int *p_data = mem->data + i;
        fscanf(p_file, "%s", buff);
        unsigned int word = str_hex2int(buff);
        *p_data = big2little(word);
    }

    fclose(p_file);
}