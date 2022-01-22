#ifndef COLORIUTILES_H
#define COLORIUTILES_H
#include "__GITICONST__.h"
#define NEKO 25

#ifdef __cplusplus
extern "C"
{
#endif


BOOL Similaridad(cuInt ColorBase, cuInt ColorComparado, cuChar tolerancia);
BOOL Similaridad2(cuInt ColorBase, cuInt ColorComparado, cuChar tolerancia);
BOOL SimilaridadPorTolerancia(cuInt ColorBase, cuInt ColorComparado, cuChar tolerancia);


#ifdef __cplusplus
}
#endif
#endif // COLORIUTILES_H
