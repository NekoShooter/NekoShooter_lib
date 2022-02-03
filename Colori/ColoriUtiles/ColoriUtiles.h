#ifndef __ColoriUtiles
#define __ColoriUtiles
#include "__GITICONST__.h"

#ifdef __cplusplus
extern "C"
{
#endif


BOOL Similaridad(cuInt ColorBase, cuInt ColorComparado, cuChar tolerancia);
BOOL Similaridad2(cuInt ColorBase, cuInt ColorComparado, cuChar tolerancia);
BOOL SimilaridadPorTolerancia(cuInt ColorBase, cuInt ColorComparado, cuChar tolerancia);

void RangoDeSimilaridad(cuInt original, uInt *max, uInt *min, cuChar umbral);


#ifdef __cplusplus
}
#endif
#endif // __ColoriUtiles
