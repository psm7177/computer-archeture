#include <mux.h>

uint32_t mux2(mux2_t *mux, uint32_t a, uint32_t b)
{
    if (mux->signal == 0)
    {
        return a;
    }
    else
    {
        return b;
    }
}

uint32_t mux3(mux3_t *mux, uint32_t a, uint32_t b, uint32_t c)
{
    switch (mux->signal)
    {
    case 0:
        return a;
    case 1:
        return b;
    case 2:
        return c;
    default:
        break;
    }
}

uint32_t mux4(mux4_t *mux, uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    switch (mux->signal)
    {
    case 0:
        return a;
    case 1:
        return b;
    case 2:
        return c;
    case 3:
        return d;
    default:
        break;
    }
}