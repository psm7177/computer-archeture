#include <debug.h>

void dbprintf(const char *format, ...)
{
#ifdef DEBUG
    va_list args;
    va_start(args, format);

    vfprintf(stderr, format, args);

    va_end(args);
#endif
}