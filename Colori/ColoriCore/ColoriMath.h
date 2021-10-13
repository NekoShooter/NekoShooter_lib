/* COLORI MATH: una libreria de arimetica de colores */

#ifndef __ColoriMath
#define __ColoriMath
#include "Colori__rgb__.h"
#ifdef __cplusplus
extern "C"
{
#endif

short dividir_tono (short Tono, short *Claro, short *Oscuro, double Nivel_Brillo, double Nivel_Oscuro);
short brillo_y_sombra(const c_rgb *color,c_rgb *Brillo, c_rgb *Sombra, double Nivel_Brillo, double Nivel_Oscuro);

c_rgb * suma_de_color(const c_rgb * origen, const c_rgb * destino, short desplazamiento);

c_rgb nivel_de_luminicencia(c_rgb Color,short intencidad);
c_rgb nivelacion_luminica(const c_rgb * ColorA,const c_rgb * ColorB);

void mover_rgb(c_rgb *crgb, uChar tipo_de_movimiento);
void convertir_a_inverso(c_rgb *original);
c_rgb *inverso(const c_rgb *original);
c_rgb *tercio(const c_rgb *original,uChar orientacion);
c_rgb *sexto(const c_rgb *original,uChar orientacion);


void buscar_familia(c_rgb *_rgb_);

void definir_limite_desendente(uShort refencia, uChar *limite_min, uChar *limite_max);
void definir_limite_ascendente(uShort refencia, uChar *limite_min, uChar *limite_max);
coloriFamilia rgbSort(const c_rgb * Crgb,uChar* idx_max, uChar *idx_med, uChar * idx_min);
coloriFamilia purezaRGB(const c_rgb *original);





#ifdef __cplusplus
}
#endif
#endif // __ColoriMath
