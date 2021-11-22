/* COLORI BASIC: una libreria de convercion de datos a un sistema de colores */

#ifndef __ColoriBasic
#define __ColoriBasic

#ifdef __cplusplus
extern "C"
{
#endif

long  rgb_a_int(unsigned  long r,unsigned int g,  unsigned short b);
short rgb_a_hex(unsigned short r,unsigned short g,unsigned short b,char *Hexadecimal, short dimencion);
short rgb_a_css(unsigned short r,unsigned short g,unsigned short b,char *CSS);

short int_a_css(long Valor,char *CSS);
short int_a_rgb(long Valor, short *r, short *g, short *b);
short int_a_hex(long Valor,char *Hexadecimal,short longitudHexa);

long  hex_a_int(const char *Hexadecimal);
short hex_a_rgb(const char *Hexadecimal,short *r,short *g,short *b);
short hex_a_css(const char *Hexadecimal, char *CSS);

long  css_a_int(const char *CSS);
short css_a_rgb(const char *CSS ,short *r,short *g,short *b);
short css_a_hex(const char *CSS,char *Hexadecimal);

#ifdef __cplusplus
}
#endif
#endif // __ColoriBasic
