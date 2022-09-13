#ifndef __KartaEsencial
#define __KartaEsencial
#include <QVector>
#include <QList>
#include "HRango.h"
#include "__GITICONST__.h"

class QRect;
class QPoint;

QRect KRect(const QPoint &puntoA, const QPoint &puntoB);
QRect KRect(short xA, short yA, short xB, short yB);
QRect KRect(const QVector<QPoint>& arreglo);
QRect KRect(const QPoint *& arreglo, short tam);

QRect KRect(const HRango<short> &x, const HRango<short> &y);

void KSimplificarRuta(QList<QPointF> &lista, QList<bool> &marcas, cuInt &inicio, cuInt &final, cDouble &tolerancia);


#endif // __KartaEsencial
