#include "KartaMath.h"
#include <QPoint>
#include <QSize>
#include <QMatrix>
#include <math.h>

#define grados(val) (val * (180/M_PI))

short cuadrante_de_la_recta(const QPointF &punto_1, const QPointF &punto_2){
    return cuadrante_de_la_recta(punto_1.x(),punto_1.y(),punto_2.x(),punto_2.y());}

short cuadrante_de_la_recta(const QPoint &punto_1, const QPoint &punto_2){
    return cuadrante_de_la_recta(punto_1.x(),punto_1.y(),punto_2.x(),punto_2.y());}

short cuadrante_de_la_recta(cDouble &Origen_x, cDouble &Origen_y, cDouble &Fin_x,cDouble &Fin_y){
    if(Origen_x == Fin_x && Origen_y == Fin_y) return  0;

    else if(Fin_x < Origen_x && Fin_y <= Origen_y)
        return 2;

    else if(Fin_x <= Origen_x && Fin_y > Origen_y)
        return 3;

    else if(Fin_x > Origen_x && Fin_y > Origen_y)
        return 4;

    return 1;}


/*
          [-x, +y ]         90º         [+x ,+y ]
                   +---------|---------+
                   |         |         |
                   |    2    |    1    |
                   |         |         |
              180º |---------o---------| 0º
                   |         |         |
                   |    3    |    4    |
                   |         |         |
                   +---------|---------+
          [+x, -y ]         270º        [+x, -y ]
*/

/********************************************************************************/

double longitud_de_la_recta(const QPointF &punto_1, const QPointF &punto_2){
    if(punto_1.isNull() || punto_2.isNull()) return 0;
    return longitud_de_la_recta(punto_1.x(),punto_1.y(),punto_2.x(),punto_2.y());}

double longitud_de_la_recta(const QPoint &punto_1, const QPoint &punto_2){
    if(punto_1.isNull() || punto_2.isNull()) return 0;
    return longitud_de_la_recta(punto_1.x(),punto_1.y(),punto_2.x(),punto_2.y());}

double longitud_de_la_recta(cDouble &P1_x, cDouble &P1_y, cDouble &P2_x,cDouble &P2_y){
    return sqrt(pow((P2_x - P1_x),2) + pow((P2_y - P1_y),2));}
//         _________________________
//        /(X2 - X1)^2 + (Y2 - Y1)^2


/********************************************************************************/



double adyasente_de_la_recta(const QPointF &punto_1,const QPointF &punto_2){
    if(punto_1.isNull() || punto_2.isNull()) return  0;
    return adyasente_de_la_recta(punto_1.x(),punto_1.y(),punto_2.x(),punto_2.y());}

double adyasente_de_la_recta(const QPoint &punto_1,const QPoint &punto_2){
    if(punto_1.isNull() || punto_2.isNull()) return  0;
    return adyasente_de_la_recta(punto_1.x(),punto_1.y(),punto_2.x(),punto_2.y());}

double adyasente_de_la_recta(cDouble &P1_x, cDouble &P1_y, cDouble &P2_x,cDouble &P2_y){
    double m = (P2_y - P1_y)/(P2_x - P1_x);
    return fabs(grados(atan(m)));}

/*        (Y2 - Y1)       -1                         _.-`| (X1,Y1) a<
      m = ---------    tan   (m)               m _.-`   _|
          (X2 - X1)               (X2,Y2) a< _.-`______|_|           */

/********************************************************************************/



double angulo_de_la_coordenada(const QPointF &referencia,const QPointF &coor){
    if(referencia.isNull() || coor.isNull()) return  0;
    return angulo_de_la_coordenada(referencia.x(),referencia.y(),coor.x(),coor.y());}

double angulo_de_la_coordenada(const QPoint &referencia,const QPoint &coor){
    if(referencia.isNull() || coor.isNull()) return  0;
    return angulo_de_la_coordenada(referencia.x(),referencia.y(),coor.x(),coor.y());}

double angulo_de_la_coordenada(cDouble &Ref_x, cDouble &Ref_y, cDouble &coor_x,cDouble &coor_y){
    if(Ref_x == coor_x && Ref_y == coor_y) return  0;

    else if(coor_x < Ref_x && coor_y <= Ref_y)
        return (90 - (adyasente_de_la_recta(Ref_x,Ref_y,coor_x,coor_y))) + 90;

    else if(coor_x <= Ref_x && coor_y > Ref_y)
        return adyasente_de_la_recta(Ref_x,Ref_y,coor_x,coor_y) + 180;

    else if(coor_x > Ref_x && coor_y > Ref_y)
        return (90 - (adyasente_de_la_recta(Ref_x,Ref_y,coor_x,coor_y))) + 270;

    return adyasente_de_la_recta(Ref_x,Ref_y,coor_x,coor_y);}

/********************************************************************************/



double diferencia_angular(cDouble &anguloInicial, cDouble &anguloFinal){
    if(ANGULO_ERRONEO(anguloInicial) || ANGULO_ERRONEO(anguloFinal)) return  0;

    double resultado = anguloInicial - anguloFinal;

    if(resultado < 0) resultado += 360;

    return 360 - resultado;}



double adicion_angular(cDouble &anguloInicial, cDouble &anguloFinal){
    if(ANGULO_ERRONEO(anguloInicial) || ANGULO_ERRONEO(anguloFinal)) return  0;

    double resultado = anguloInicial + (360 - anguloFinal);

    if(resultado > 360) resultado -= 360;

    return resultado;
}


// QMatrix matriz(m11,m21,m12,m22,dx,dy)
// m11*x + m21*y + dx = x'
// m12*x + m22*y + dy = y'

double abscisa(cDouble &x, const QMatrix * matrix){
    if(!matrix) return x;
    return matrix->m11() * x + matrix->dx();}

double ordenada(cDouble &y, const QMatrix * matrix){
    if(!matrix) return y;
    return matrix->m22() * y + matrix->dy();}
