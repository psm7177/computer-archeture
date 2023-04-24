#ifndef _MUX
#define _MUX

typedef struct _mux2 mux2_t;
typedef struct _mux3 mux3_t;
typedef struct _mux4 mux4_t;

#include <stdbool.h>
#include <stdint.h>

struct _mux2
{
    bool signal;
};

struct _mux3
{
    uint8_t signal;
};

struct _mux4
{
    uint8_t signal;
};

uint32_t mux2(mux2_t *mux, uint32_t a, uint32_t b);
uint32_t mux3(mux3_t *mux, uint32_t a, uint32_t b, uint32_t c);
uint32_t mux4(mux4_t *mux, uint32_t a, uint32_t b, uint32_t c, uint32_t d);

#endif