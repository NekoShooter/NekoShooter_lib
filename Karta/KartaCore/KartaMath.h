#ifndef __KartaMath
#define __KartaMath
#include "KartaCoor.h"

//class QPointF;
class QMatrix;

short cuadrante_de_la_recta(const QPointF &punto_1, const QPointF &punto_2);
short cuadrante_de_la_recta(const QPoint &punto_1, const QPoint &punto_2);
short cuadrante_de_la_recta(cDouble &Origen_x, cDouble &Origen_y, cDouble &Fin_x, cDouble &Fin_y);

double longitud_de_la_recta(const QPointF &punto_1, const QPointF &punto_2);
double longitud_de_la_recta(const QPoint &punto_1, const QPoint &punto_2);
double longitud_de_la_recta(cDouble &P1_x, cDouble &P1_y, cDouble &P2_x,cDouble &P2_y);

double adyasente_de_la_recta(const QPointF &punto_1,const QPointF &punto_2);
double adyasente_de_la_recta(const QPoint &punto_1,const QPoint &punto_2);
double adyasente_de_la_recta(cDouble &P1_x, cDouble &P1_y, cDouble &P2_x,cDouble &P2_y);

double angulo_de_la_coordenada(const QPointF &referencia,const QPointF &coor);
double angulo_de_la_coordenada(const QPoint &referencia,const QPoint &coor);
double angulo_de_la_coordenada(cDouble &Ref_x, cDouble &Ref_y, cDouble &coor_x,cDouble &coor_y);

double diferencia_angular(cDouble &anguloInicial, cDouble &anguloFinal);
double adicion_angular(cDouble &anguloInicial, cDouble &anguloFinal);

double abscisa(cDouble &x, const QMatrix * matrix);
double ordenada(cDouble &y, const QMatrix * matrix);
#endif // __KartaMath
