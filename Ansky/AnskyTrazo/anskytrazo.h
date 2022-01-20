#ifndef ANSKYTRAZO_H
#define ANSKYTRAZO_H
#include <QList>
#include <QPoint>
#include "__GITICONST__.h"
class QImage;

void UnirPuntos(QPainter &painter,const QList<QPointF> &lista_de_coor, const QPointF &ancla = QPointF(), cDouble &angulo = 0, const bool &anti_radial = false);
QImage *Colorear(QImage *imagen, const QPoint &coordenada, cuInt id_nuevo_color, const bool &capa_independiente = false);

#endif // ANSKYTRAZO_H
