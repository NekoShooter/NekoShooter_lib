#ifndef KARTAMATH_H
#define KARTAMATH_H
#include "kartacoor.h"

class QPointF;

double longitud_de_la_recta(const QPointF &punto_1, const QPointF &punto_2);
double longitud_de_la_recta(const QPoint &punto_1, const QPoint &punto_2);
double longitud_de_la_recta(cDouble &P1_x, cDouble &P1_y, cDouble &P2_x,cDouble &P2_y);


double *angulo_de_la_recta(const QPointF &punto_1, const QPointF &punto_2);
double *angulo_de_la_recta(const QPoint &punto_1, const QPoint &punto_2);
double *angulo_de_la_recta(cDouble &P1_x, cDouble &P1_y, cDouble &P2_x,cDouble &P2_y);
#endif // KARTAMATH_H
