#include "GitiBits.h"


short aBytes(long *_int,unsigned char nBits){
    if (!_int) return GITI_ERROR;

    long intFull = (*_int >> nBits)<<nBits;
    short bytes = *_int ^ intFull;
    *_int = intFull >> nBits;
    return bytes;}



char int4bitsAhex (unsigned short int4bits, BOOL invertir){
    if(15 < int4bits) return INVALIDO;
    const char * Hexadecimal = "0123456789abcdef";

    if (invertir)
        return Hexadecimal[15 - int4bits];
    else
        return Hexadecimal[int4bits]; }



short charHexAint4bits(const char _char){
    if(_char >= '0' && _char <= '9')
        return(short)_char - 48;
    else if(_char >= 'A' && _char <= 'F')
        return(short)_char - 55;
    else if(_char >= 'a' && _char <= 'f')
        return(short)_char - 87;
    else
         return GITI_ERROR;}




short intAhex(long _int,char *Hexadecimal,unsigned short longitudHexa,BOOL hashtag){
    if(Hexadecimal == INVALIDO) return GITI_ERROR;

    short valor, limite = -1;

    if(hashtag){
        Hexadecimal[0] = '#';
        limite = 0;}

    short i = longitudHexa - 2;
    Hexadecimal[longitudHexa - 1] = '\0';

    while(i > limite){
        valor = aBytes(&_int,4);
        Hexadecimal[i]= int4bitsAhex(valor,False);
        if(Hexadecimal[i]== INVALIDO)
            return  GITI_ERROR;
        --i;}

    if(_int) return GITI_ERROR;
    else     return GITI_OK;}




long hexAint(const char *Hexadecimal){
        if(Hexadecimal == INVALIDO) return GITI_ERROR;

        short dimencion,i    = 0,
                        bits = 0;

        long _int = 0,
             int4bits;

        for(dimencion = 1; Hexadecimal[dimencion];++dimencion);
        for(i = dimencion - 1; i > -1; --i){

            if(Hexadecimal[i] == '#'&& i != 0) return GITI_ERROR;
            else if(Hexadecimal[i] == '#')     break;

            int4bits = charHexAint4bits(Hexadecimal[i]);
            if(int4bits != GITI_ERROR){
                _int +=(int4bits << bits);
                bits += 4;}
            else
                return GITI_ERROR;}
        return _int;}
