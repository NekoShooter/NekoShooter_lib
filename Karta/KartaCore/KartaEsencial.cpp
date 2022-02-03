#include "KartaEsencial.h"
#include <QRect>

QRect KRect(const QPoint &puntoA, const QPoint &puntoB){
    if(puntoA == puntoB) return QRect();
    return KRect(puntoA.x(),puntoA.y(),puntoB.x(),puntoB.y());}

QRect KRect(short xA, short yA, short xB, short yB){
    short  *minX, *maxX,
           *minY, *maxY;

    if(xA < xB){ minX = &xA;  maxX = &xB; }
    else       { minX = &xB;  maxX = &xA; }

    if(yA < yB){ minY = &yA;  maxY = &yB; }
    else       { minY = &yB;  maxY = &yA; }

    return QRect(*minX,*minY,*maxX - *minX,*maxY - *minY);}
