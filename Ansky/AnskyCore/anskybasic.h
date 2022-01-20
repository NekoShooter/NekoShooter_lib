#ifndef ANSKYBASIC_H
#define ANSKYBASIC_H
#include "__GITICONST__.h"
#include "__ANSKYCONST__.h"
#include <QList>

class QPainter;
class QRect;
class QPoint;

void Limpiar_lienzo(QPainter &painter, const QRect &area_a_limpiar);

void Dibujar_triangulo(QPainter &painter, const QRect &rec,const ansky_direccion rotar = ansky_direccion::NONE);
void Dibujar_triangulo(QPainter &painter, const QPoint &coor, cuShort &base, cuShort &altura);
void Dibujar_triangulo(QPainter &painter, cuShort &pos_x, cuShort &pos_y, cuShort &base, cuShort &altura, cShort &ancla_x = 0, cShort &ancla_y = 0, cuShort & ang = 0);

QList<QPointF> coor_triangulo(const QRect & rec, const QPointF &ancla = QPointF(), cuShort &ang = 0);
QList <QPointF>coor_triangulo(cShort &pos_x, cShort &pos_y, cuShort &base, cuShort &altura, cShort &ancla_x = 0, cShort &ancla_y = 0, cuShort &ang = 0);


#endif // ANSKYBASIC_H
