#ifndef KARTAMATH_H
#define KARTAMATH_H
#include "kartacoor.h"

class QPoint;
class QSize;

double longitud_de_la_recta(const QPoint &punto_1, const QPoint &punto_2);
double *angulo_de_la_recta(const QPoint &punto_1, const QPoint &punto_2);
k_index encontrar_index(const QPoint& click,const kcelda &celda);

#endif // KARTAMATH_H
