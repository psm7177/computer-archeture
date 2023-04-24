#ifndef _REGISTER
#define _REGISTER

#include <stdbool.h>
#include <stdint.h>

#define NUM_REG 32
#define RA 31

typedef struct _reg_file reg_file_t;

struct _reg_file{
    uint32_t reg[NUM_REG];
};

void init_reg_file(reg_file_t * reg_file);

uint32_t read_register(reg_file_t * reg_file, uint8_t addr);
void write_register(reg_file_t * reg_file, uint8_t addr, uint32_t value);

#endif