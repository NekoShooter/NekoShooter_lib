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
QPoint TransformaCoordenada(cDouble &x, cDouble &y, const QMatrix *matriz){
    return TransformaCoordenadaF(x,y,matriz).toPoint();}

QPointF TransformaCoordenadaF(cDouble &x, cDouble &y, const QMatrix *matriz){
    if(!matriz) return QPointF(x,y);
    return TransformaCoordenadaF(QPoint(x,y), *matriz);}

QPointF TransformaCoordenadaF(const QPoint &coordenada, const QMatrix &matriz){
    double x = (matriz.m11()*coordenada.x()) + (matriz.m21() * coordenada.y()) + matriz.dx();
    double y = (matriz.m12()*coordenada.x()) + (matriz.m22() * coordenada.y()) + matriz.dx();
    return QPointF(x,y);}

QPointF ReTransformaCoordenadaF(const QPoint &coordenada, const QMatrix &matriz){
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
    QPointF centroWidget = ReTransformaCoordenadaF(QPoint(twid.width()/2, twid.height()/2),m);
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


QPointF Invertida(const QPointF &ancla, const QPointF &punto){
    float desplazamientoX = punto.x() - ancla.x();
    float desplazamientoY = punto.y() - ancla.y();
    return QPointF(ancla.x() - desplazamientoX,ancla.y() - desplazamientoY);}


QPointF Escuadra(const QPointF &ancla, const QPointF &punto){
    float desplazamientoX = punto.x() - ancla.x();
    float desplazamientoY = punto.y() - ancla.y();
    return QPointF(ancla.x() - desplazamientoY, ancla.y() + desplazamientoX);}

QPointF EscuadraInvertida(const QPointF &ancla, const QPointF &punto){
    return Invertida(ancla, Escuadra(ancla,punto));}



QPointF PuntoMedio(const QPointF &A, const QPointF &B){
    return QPointF ((A.x() + B.x()) / 2,(A.y() + B.y()) / 2);}

QPointF PuntoDeLaCurvaLineal(const QPointF &p0, const QPointF &p1,const float &t){
    //assert(1 >= t && t >= 0);
    // P = (1-t)P1 + tP2

    float inv = 1 - t;
    return QPointF( (inv * p0.x()) + (t * p1.x()) , (inv * p0.y()) + (t * p1.y())); }
/*
    curva de Bézier
    P = (1−t)2P1 + 2(1−t)tP2 + t2P3
    P = (1−t)3P1 + 3(1−t)2tP2 +3(1−t)t2P3 + t3P4
*/


QPointF PuntoInterpoladoDelRiel(const QPointF &p0,const QPointF &p1,const QPointF &p2,const QPointF &p3, cFloat &t){
    assert(1 >= t && t >= 0);

    float te2 = t * t;
    float te3 = te2 * t;
    float q0 = -te3 + (2 * te2) - t;
    float q1 = (3 * te3) - (5 * te2) + 2;
    float q2 = (-3 * te3) + (4 * te2) + t;
    float q3 = te3 - te2;

    return QPointF ((.5 *(p0.x() * q0 + p1.x() * q1 + p2.x() * q2 + p3.x() * q3)),
                    (.5 *(p0.y() * q0 + p1.y() * q1 + p2.y() * q2 + p3.y() * q3)));

    /* Fuente
    [cubic Hermite spline] : https://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull–Rom_spline
    [video] : https://www.youtube.com/watch?v=9_aJGUTePYo
    [repo]  : https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_Splines1.cpp */}


QPointF PuntoGradienteDelRiel(const QPointF &p0,const QPointF &p1,const QPointF &p2,const QPointF &p3, cFloat &t){
    assert(1 >= t && t >= 0);

    float te2 = t * t;

    float q0 = -3 * te2 + 4  * t - 1;
    float q1 =  9 * te2 - 10 * t;
    float q2 = -9 * te2 + 8 * t + 1;
    float q3 =  3 * te2 - 2 * t;

    return QPointF ((.5f *(p0.x() * q0 + p1.x() * q1 + p2.x() * q2 + p3.x() * q3)),
                    (.5f *(p0.y() * q0 + p1.y() * q1 + p2.y() * q2 + p3.y() * q3)));
    /* Fuente
    [video] : https://www.youtube.com/watch?v=9_aJGUTePYo
    [repo]  : https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_Splines1.cpp */}

void PuntosGradientesInterpoladosDelRiel(QPointF &A, QPointF &B, const QPointF &PuntoInterpolado, const QPointF &PuntoGradiente, float TamPx){
    if(TamPx <= 0) return;
    float r = atan2(-PuntoGradiente.y() , PuntoGradiente.x());

    A.setX(TamPx * sin(r) + PuntoInterpolado.x());
    A.setY(TamPx * cos(r) + PuntoInterpolado.y());

    B.setX(- TamPx * sin(r) + PuntoInterpolado.x());
    B.setY(- TamPx * cos(r) + PuntoInterpolado.y());}
