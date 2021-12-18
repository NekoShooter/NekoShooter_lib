#include "kartamath.h"
#include <QPoint>
#include <QSize>
#include <math.h>

#define grados(val) (val * (180/M_PI))

double longitud_de_la_recta(const QPointF &punto_1, const QPointF &punto_2){
    if(punto_1.isNull() || punto_2.isNull()) return 0;
    return longitud_de_la_recta(punto_1.x(),punto_1.y(),punto_2.x(),punto_2.y());}

double longitud_de_la_recta(const QPoint &punto_1, const QPoint &punto_2){
    if(punto_1.isNull() || punto_2.isNull()) return 0;
    return longitud_de_la_recta(punto_1.x(),punto_1.y(),punto_2.x(),punto_2.y());}

double longitud_de_la_recta(cDouble &P1_x, cDouble &P1_y, cDouble &P2_x,cDouble &P2_y){
    //         _________________________
    //        /(X2 - X1)^2 + (Y2 - Y1)^2
    return sqrt(pow((P2_x - P1_x),2) + pow((P2_y - P1_y),2));}


/********************************************************************************/

double *angulo_de_la_recta(const QPointF &punto_1, const QPointF &punto_2){
    if(punto_1.isNull() || punto_2.isNull()) return nullptr;
    return angulo_de_la_recta(punto_1.x(),punto_1.y(),punto_2.x(),punto_2.y());}

double *angulo_de_la_recta(const QPoint &punto_1, const QPoint &punto_2){
    if(punto_1.isNull() || punto_2.isNull()) return nullptr;
    return angulo_de_la_recta(punto_1.x(),punto_1.y(),punto_2.x(),punto_2.y());}

double *angulo_de_la_recta(cDouble &P1_x, cDouble &P1_y, cDouble &P2_x,cDouble &P2_y){
/*        (Y2 - Y1)       -1                         _.-`| (X1,Y1) a<
      m = ---------    tan   (m)               m _.-`   _|
          (X2 - X1)               (X2,Y2) a< _.-`______|_|           */

    int m = (P2_y - P1_y)/(P2_x - P1_x);
    double * angulos = new double[2];
    angulos[0] = fabs(grados(atan(m)));
    angulos[1] = 90 - angulos[0];
    return angulos;
}
