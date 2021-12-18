#ifndef ANSKYBASIC_H
#define ANSKYBASIC_H
#include "__GITICONST__.h"
#include <QList>

class QPainter;
class QRect;
class QPoint;

void Limpiar_lienzo(QPainter &painter, const QRect &area_a_limpiar);

void Dibujar_triangulo(QPainter &painter, const QRect &rec);
void Dibujar_triangulo(QPainter &painter, const QPoint &coor, cuShort &base, cuShort &altura);
void Dibujar_triangulo(QPainter &painter, cuShort &pos_x, cuShort &pos_y, cuShort &base, cuShort &altura);
QList <QPoint>coor_triangulo(const QRect & rec,cuShort &ang = 0);
QList <QPoint>coor_triangulo(cuShort &pos_x, cuShort &pos_y, cuShort &base, cuShort &altura, cuShort &ang = 0);

void Dibujar_figura(QPainter &painter,const QList<QPoint> &lista_de_coor);


#endif // ANSKYBASIC_H
