#include "ColoriUtiles.h"
#include <math.h>
#include "Colori__rgb__.h"
#include "ColoriMath.h"

BOOL Similaridad(cuInt ColorBase, cuInt ColorComparado, cuChar tolerancia){
    if(ColorBase == ColorComparado) return True;
    c_rgb b = {ColorBase};
    c_rgb c = {ColorComparado};
    char i = _B_;
    if(b.id == c.id) i = _A_;

    for(; i < _F_; ++i){
        double porcentaje = c.rgb[(short)i] * (b.rgb[(short)i] / 100);
        if( !(porcentaje >= (100 - tolerancia) && porcentaje <= (100 + tolerancia)))
            return False;}
    return True;}

BOOL Similaridad2(cuInt ColorBase, cuInt ColorComparado, cuChar tolerancia){
    if(ColorBase == ColorComparado) return True;
    c_rgb b = {ColorBase};
    c_rgb c = {ColorComparado};
    autoIncrementarLuminicencia(&b,tolerancia);
    autoIncrementarLuminicencia(&c,tolerancia);
    short i = _B_;
    if(b.id == c.id) return True;;
    while(i < _A_){
        char max, min;
        definir_limite_ascendente(b.rgb[(short)i],&max,&min);
        if(c.rgb[(short)i] < max && c.rgb[(short)i] > min) ++i;
        else return False;}
    return True;
}

BOOL SimilaridadPorTolerancia(cuInt ColorBase, cuInt ColorComparado, cuChar tolerancia){
    if(ColorBase == ColorComparado) return True;
    c_rgb b = {ColorBase};
    c_rgb c = {ColorComparado};
    double T = 0;
    for(char i = _B_; i != _F_; ++i) T += sqrt(b.rgb[(short)i] - c.rgb[(short)i]);
    return T <= tolerancia;}
