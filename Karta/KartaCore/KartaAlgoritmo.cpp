#include "KartaAlgoritmo.h"
#include <assert.h>
#include <QPointF>


QPointF PuntoCatmull_Rom(const QPointF &p0,const QPointF &p1,const QPointF &p2,const QPointF &p3, const float &t){
    //fuente :  https://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull–Rom_spline
    assert(1 >= t && t >= 0);

    float te2 = t * t;
    float te3 = te2 * t;

    float q0 = -te3 + (2 * te2) - t;
    float q1 = (3 * te3) - (5 * te2) + 2;
    float q2 = (-3 * te3) + (4 * te2) + t;
    float q3 = te3 - te2;

    return QPointF ((.5 *(p0.x() * q0 + p1.x() * q1 + p2.x() * q2 + p3.x() * q3)),
                    (.5 *(p0.y() * q0 + p1.y() * q1 + p2.y() * q2 + p3.y() * q3)));}



QPointF Catmull_Rom(const QList<QPointF> &lista, const float &t){
    assert(lista.size() > 2 && lista.size() - 1 >= t);

        const QPointF &p1 = lista.at((short)t);
        const QPointF &p0 = (short)t ? lista.at(short(t) - 1) : p1;
        const QPointF &p2 = lista.at(short(t) + 1);
        const QPointF &p3 = (short)t + 2 < lista.size() ? lista.at(short(t) + 2) : p2;

        return PuntoCatmull_Rom(p0,p1,p2,p3,t - (short)t);
}



QPointF PuntoCurvaLineal(const QPointF &p0, const QPointF &p1,const float &t){
    // P = (1-t)P0 + tP1
    return ((1 - t) * p0) + (t * p1);}


QPointF PuntoCurvaCuadratica(const QPointF &p0, const QPointF &p1, const QPointF &p2, const float &t){
    // P = (1−t)^2P0 + 2t(1−t)P1 + t^2P1
    float inv = 1 - t;
    float inve2 = inv * inv;
    float te2 = t * t;
    return (inve2 * p0) + ((2 * t) * inv * p1) + te2 * p2;}
