#include "KartaCoor.h"
#include "KartaMath.h"
#include <QPointF>
#include <assert.h>
#include <math.h>
#include <QMatrix>

#define rad(ang) (ang * (M_PI/180))

QPointF coordenadasCirculares(const QPointF &CENTRO, cFloat &RADIO, cFloat &NumDeSecciones, cFloat &index, Karta::Sentido sentido){
    if(NumDeSecciones <= 0|| RADIO <= 0 || index < 0 || index > NumDeSecciones) return CENTRO;

    double x = 0;
    double y = 0;
    cDouble UNIDAD = 360/NumDeSecciones;

    switch (sentido) {
    case Karta::Horario:
        y = 90 -((UNIDAD * index) + UNIDAD);
        x = 90 - fabs(y);
        break;
    case Karta::Anti_horario:
        x = 90 -((UNIDAD * index) + UNIDAD);
        y = 90 - fabs(x);
        break;
    case Karta::Radial:
        x = 90 -(UNIDAD * index);
        y = 90 - fabs(x);
        break;
    default: return CENTRO;}

    double punto_coor_x = sin(rad(x)) * RADIO;
    double punto_coor_y = sin(rad(y)) * RADIO;

    return QPointF((CENTRO.x() + punto_coor_x),(CENTRO.y() - punto_coor_y));}




/***********************************************************************************************/


QPointF rotarCoordenada(const QPointF &ancla, const QPointF &coor, cDouble &ang, const bool &anti_radial){
    if(ancla == coor || !ANGULO_VALIDO(ang)) return coor;
    return rotarCoordenada(ancla.x(),ancla.y(),coor.x(), coor.y(),ang, anti_radial);}

QPointF rotarCoordenada(const QPoint &ancla, const QPoint &coor, cDouble &ang, const bool &anti_radial){
    if (ancla == coor || !ANGULO_VALIDO(ang)) return coor;
    return rotarCoordenada(ancla.x(),ancla.y(),coor.x(), coor.y(),ang, anti_radial);}

QPointF rotarCoordenada(cDouble &ancla_x, cDouble &ancla_y, cDouble &coor_x, cDouble &coor_y, cDouble &ang, const bool &anti_radial){
    assert(ang < 360 && ang >  0);
    double longitud = longitud_de_la_recta(ancla_x,ancla_y,coor_x,coor_y);
    double angulo = angulo_de_la_coordenada(ancla_x,ancla_y,coor_x,coor_y) + (!anti_radial ? ang : 360 - ang);
    double x = 90 - (angulo > 360 ? angulo - 360 : angulo);
    double y = 90 - fabs(x);

    double punto_x = sin(rad(x)) * longitud;
    double punto_y = sin(rad(y)) * longitud;
    return QPointF((ancla_x + punto_x), (ancla_y - punto_y));}



/***********************************************************************************************/


QPointF ReCalcularCoordenada(const QPoint &coordenada, const QMatrix &matriz){
    if(!matriz.m11() || !matriz.m22()) return QPointF(-1,-1); // Error

    if(matriz.m11() == 1 && matriz.m22() == 1 && !matriz.m21() && !matriz.m12()&& !matriz.dx()&& !matriz.dy())
        return  coordenada;
    // QMatrix matriz(m11,m21,m12,m22,dx,dy)
    // m11*x + m21*y + dx = x'
    // m12*x + m22*y + dy = y'


    double Rx = coordenada.x() - matriz.dx();
    double Ry = coordenada.y() - matriz.dy();
    if(!Rx || !Ry) return QPointF(-1,-1);

    if(matriz.m11() == 1 && matriz.m22() == 1 && !matriz.m21() && !matriz.m12())
        return QPointF(Rx,Ry);

    // m11*x + m21*y = Rx
    // m12*x + m22*y = Ry

    double x,y, divisor;

    if(!matriz.m21()){
        x = Rx / matriz.m11();
        y = (Ry -(matriz.m12() * x)) /  matriz.m22();
        // y = (Ry - m12(x)) / m22
        return  QPointF(x,y);}

    if(!matriz.m12()){
        y = Ry / matriz.m22();
        x = (Rx - (matriz.m21() * y)) /  matriz.m11();
        return  QPointF(x,y);}

    divisor = (matriz.m11() * matriz.m22()) - (matriz.m21()* matriz.m12());

    x = ((Rx * matriz.m22()) - (matriz.m21() * Ry)) / divisor;
    y = (Ry - (matriz.m12() * x)) /  matriz.m22();

    return QPointF(x,y);}

    /*
    m11*x + m21*y = Rx    <--
    a       b       c
    m12*x + m22*y = Ry
    d       e       f

     e(a + b = c)
    -b(d + e = f)

     ae + be = ce
    -bd - be = -bf
    ae - bd = ce - bf


    x = (ce -bf) / (ae -bd)
    y = (af -cd) / (ae -bd)

    x = (Rx*m22) - (m21*Ry) / (m11*m22) -(m21*m12)
    y = (m11*Ry) - (Rx*m12) / (m11*m22) -(m21*m12)
*/

QPointF ReCentro(const QSize &timg, const QSize &twid, const QMatrix &m){
    if(timg.isEmpty()) return QPointF(-1,-1);
    QPointF centroWidget = ReCalcularCoordenada(QPoint(twid.width()/2, twid.height()/2),m);
    QPointF centroImagen = QPointF((timg.width()/2)+m.dx(),(timg.height()/2)+m.dy());
    return QPointF(centroWidget-centroImagen);}


QMatrix Rotacion(const QPointF &ancla, const QPointF &partida,const QPointF &destino){
    //fallida
    QPointF ini = partida - ancla;
    QPointF fin = destino - ancla;
    double inicio = sqrt( ini.x() * ini.x() + ini.y() * ini.y());
    double final  = sqrt( fin.x() * fin.x() + fin.y() * fin.y());

    double cose =  (ini.x() * fin.x() + ini.y() * fin.y()) / inicio * final;
    double seno = (-ini.x() * fin.y() + ini.y() * fin.x()) / inicio * final;
    return QMatrix(cose,-seno,seno,cose,0,0);}
