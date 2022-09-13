#include "KartaEsencial.h"
//#include "HContenedor.h"
#include <QRect>



QRect KRect(const QPoint &puntoA, const QPoint &puntoB){
    if(puntoA == puntoB) return QRect();
    return KRect(puntoA.x(),puntoA.y(),puntoB.x(),puntoB.y());}



QRect KRect(short xA, short yA, short xB, short yB){
    HRango<short> x, y;
    x << xA << xB;
    y << yA << yB;
    return KRect(x,y);}



QRect KRect(const QVector<QPoint>& arreglo){
    if(arreglo.isEmpty() || arreglo.length() < 2) return QRect();
    HRango<short> x, y;

    for(QVector<QPoint>::const_iterator i = arreglo.begin(); i != arreglo.end(); ++i){
        x << i->x();
        y << i->y();}

    return KRect(x,y);}



QRect KRect(const QPoint *& arreglo, short tam){
    if(!arreglo || tam < 2) return QRect();
    HRango<short> x, y;

    for(short i = 0; i < tam ; ++i){
        x << arreglo[i].x();
        y << arreglo[i].y();}

    return KRect(x,y);}



QRect KRect(const HRango<short> &x, const HRango<short> &y){
    assert(!x.estaVacio() && !y.estaVacio());
    return QRect(x.min(),y.min(),x.max() - x.min(),y.max() - y.min());}



void KSimplificarRuta(QList<QPointF> &lista, QList<bool> &marcas,cuInt &inicio, cuInt &final, cDouble &tolerancia){
    if(final <= inicio || tolerancia <= 0) return;

    double distanciaMax = 0.0;
    uInt indice = inicio;

    QPointF s = lista[inicio] - lista[final]; //siguiente
    double distancia = (s.x() * s.x()) + (s.y() + s.y());


    for(uInt i = inicio + 1; i < final - 1; ++i){
        if(distancia){
            QPointF p = lista[i] - lista[inicio]; //previo
            distancia = sqrt(((p.x() * p.x()) + (p.y() * p.y())) - pow((p.x() * s.x()) +(p.y() * s.y()),2)/distancia);}

        if(distancia > distanciaMax){
            distanciaMax = distancia;
            indice = i;}}


    if(distanciaMax >= tolerancia){
        marcas.replace(indice, true);

        KSimplificarRuta(lista, marcas, inicio, indice, tolerancia);
        KSimplificarRuta(lista, marcas, indice, final, tolerancia);}}
