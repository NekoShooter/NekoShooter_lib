#ifndef __Colori__rgb__
#define __Colori__rgb__
#include "__COLORICONST__.h"
#include "__GITICONST__.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define _F_ 4 // Familia del color
#define _A_ 3
#define _R_ 2
#define _G_ 1
#define _B_ 0

union c_rgb {
    unsigned long long info:40;
    unsigned int id_a: 32;
    unsigned int id : 24;
    unsigned char rgb[5];} __attribute__((packed));

typedef union c_rgb c_rgb;

c_rgb *nuevo_rgb(short tam);
void liberar(c_rgb *rgb_aEliminar);

c_rgb *circulo_cromatico(const c_rgb *rgb_original,coloridx seccion, uChar estilo);

c_rgb *mezclar_colores(const c_rgb *ColorA, const c_rgb *ColorB);

c_rgb *complemento(const c_rgb *original,uChar estilo);
c_rgb *adyasente(const c_rgb *original, coloridx posicion,uChar estilo);
c_rgb *contiguo(const c_rgb *original,coloridx posicion,uChar estilo);



#ifdef __cplusplus
}
#endif
#endif //__Colori__rgb__
