#ifndef KARTAALGORITMO_H
#define KARTAALGORITMO_H

#include <QList>

QPointF PuntoCatmull_Rom(const QPointF &p0,const QPointF &p1,const QPointF &p2,const QPointF &p3, const float &t);
QPointF Catmull_Rom(const QList<QPointF> &lista, const float &t);
QPointF PuntoCurvaLineal(const QPointF &p0, const QPointF &p1,const float &t);
QPointF PuntoCurvaCuadratica(const QPointF &p0, const QPointF &p1, const QPointF &p2,const float &t);
#endif // KARTAALGORITMO_H
