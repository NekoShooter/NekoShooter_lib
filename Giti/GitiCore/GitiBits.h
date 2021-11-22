/* GITI BITS: una libreria para la convercion de datos a datos primitivos */
#ifndef __GitiBits
#define __GitiBits

#include "__GITICONST__.h"

#ifdef __cplusplus
extern "C"
{
#endif

short aBytes(long *_int, unsigned char nBits);

char int4bitsAhex(unsigned short int4bits,GITI_OPCION invertir);
short  charHexAint4bits(const char _char);

short intAhex(long _int, char *Hexadecimal, unsigned short dimencion, BOOL hashtag);
long hexAint(const char *hex);

#ifdef __cplusplus
}
#endif
#endif // __GitiBits
