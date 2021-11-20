#include "kartamath.h"
#include <QPoint>
#include <QSize>
#include <math.h>

#define grados(val) (val * (180/M_PI))

double longitud_de_la_recta(const QPoint &punto_1, const QPoint &punto_2){
    if(punto_1.isNull() || punto_2.isNull()) return 0;
    //         _________________________
    //        /(X2 - X1)^2 + (Y2 - Y1)^2
    return sqrt(pow((punto_2.x() - punto_1.x()),2) + pow((punto_2.y() - punto_1.y()),2));}

double *angulo_de_la_recta(const QPoint &punto_1, const QPoint &punto_2){
    if(punto_1.isNull() || punto_2.isNull()) return nullptr;
/*        (Y2 - Y1)       _1                         _.-`| (X1,Y1) a<
      m = ---------    tan   (m)               m _.-`   _|
          (X2 - X1)               (X2,Y2) a< _.-`______|_|           */

    int m = (punto_2.y() - punto_1.y())/(punto_2.x() - punto_1.x());
    double * angulos = new double[2];
    angulos[0] = fabs(grados(atan(m)));
    angulos[1] = 90 - angulos[0];
    return angulos;}

k_index encontrar_index(const QPoint& click,const kcelda &celda){
    if(!celda.esValido() || click.isNull())return  k_index{0};

}
