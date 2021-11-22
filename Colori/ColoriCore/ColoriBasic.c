#include "ColoriBasic.h"
#include "GitiBits.h"
#include "__COLORICONST__.h"


/************************ RGB ***************************/

long rgb_a_int(unsigned long r,unsigned int g,unsigned short b){
    if(r > 255 || g > 255 || b > 255) return COLORI_ERROR;
    return b + (g << 8)+(r << 16);}


short rgb_a_hex(unsigned short r,unsigned short g,unsigned short b,char *Hexadecimal, short dimencion){
    BOOL hashtag = False;
    if(Hexadecimal[0] == '#')  hashtag = True ;

    return intAhex(rgb_a_int(r,g,b),Hexadecimal,dimencion,hashtag);}


#define RGBaCSS(rgb) rgb * 15/255
short rgb_a_css(unsigned short r,unsigned short g,unsigned short b,char *CSS){
    if(CSS == Indefinido) return COLORI_ERROR;
    short rgb[3];
    rgb[0] = RGBaCSS(r)+.5;
    rgb[1] = RGBaCSS(g)+.5;
    rgb[2] = RGBaCSS(b)+.5;
    CSS[0] = '#';
    for(short i = 0; i < 3; ++i){
        CSS[i + 1] = int4bitsAhex(rgb[i],NO_INVERTIR);
        if(CSS[i + 1] == INVALIDO)
            return COLORI_ERROR;}
    CSS[4] = '\0';
    return COLORI_OK;}


/************************ int ***************************/


short int_a_css(long Valor,char *CSS){
    if(Valor > BLANCO || Valor < NEGRO) return COLORI_ERROR;
    short r, g, b;
    int_a_rgb(Valor,&r,&g,&b);
    return rgb_a_css(r,g,b,CSS);}


short int_a_rgb(long Valor,short *r,short *g,short *b){
    if(Valor > BLANCO || Valor < NEGRO) return COLORI_ERROR;
    *b = aBytes(&Valor,8);
    *g = aBytes(&Valor,8);
    *r = aBytes(&Valor,8);
    return  COLORI_OK;}


short int_a_hex(long Valor,char *Hexadecimal,short longitudHexa){
    BOOL hashtag = True;
    return intAhex(Valor,Hexadecimal,longitudHexa,hashtag);}


/************************ hex *****************************/


long  hex_a_int(const char*Hexadecimal){
    return hexAint(Hexadecimal);}


short hex_a_rgb(const char *Hexadecimal,short *r,short *g,short *b){
    long Valor = hexAint(Hexadecimal);
    if(Valor == COLORI_ERROR) return COLORI_ERROR;
    return int_a_rgb(Valor,r,g,b);}


short hex_a_css(const char *Hexadecimal, char *CSS){
    if(Hexadecimal == INVALIDO || CSS == INVALIDO) return COLORI_ERROR;
    short r, g, b;
    if(hex_a_rgb(Hexadecimal,&r,&g,&b) == COLORI_ERROR)
        return  COLORI_ERROR;
    return rgb_a_css(r,g,b,CSS);}


/************************ css *****************************/


long css_a_int(const char *CSS){
    if(CSS == INVALIDO) return COLORI_ERROR;
    char Hexadecimal[8];
    if(css_a_hex(CSS,Hexadecimal)==COLORI_ERROR)
        return COLORI_ERROR;
    return hexAint(Hexadecimal);}



short css_a_rgb(const char *CSS, short *r,short *g,short *b){
    if(CSS == INVALIDO) return COLORI_ERROR;
    char Hexadecimal[8];
    if(css_a_hex(CSS,Hexadecimal)== COLORI_ERROR)
        return  COLORI_ERROR;
    return hex_a_rgb(Hexadecimal,r,g,b);}



short css_a_hex(const char *CSS,char *Hexadecimal){
    if(CSS==INVALIDO||(Hexadecimal==INVALIDO))return COLORI_ERROR;
    unsigned short j = 0,
                   i = 1;

    if(CSS[0]== '#')j = 1;
    Hexadecimal[0] = '#';
    Hexadecimal[7] = '\0';

    while(i < 7){
        if(charHexAint4bits(CSS[j]) == COLORI_ERROR)
            return COLORI_ERROR;
        Hexadecimal[i] = CSS[j];
        Hexadecimal[i + 1]  = CSS[j];

        i += 2;   ++j;}

    return  COLORI_OK;}
