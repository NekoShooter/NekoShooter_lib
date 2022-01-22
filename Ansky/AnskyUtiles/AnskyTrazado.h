#ifndef ANSKYTRAZADO_H
#define ANSKYTRAZADO_H

#include <QList>
#include "__GITICONST__.h"

void UnirPuntos(QPainter &painter,const QList<QPointF> &lista_de_coor, const QPointF &ancla = QPointF(), cDouble &angulo = 0, const bool &anti_radial = false);


#endif // ANSKYTRAZADO_H
