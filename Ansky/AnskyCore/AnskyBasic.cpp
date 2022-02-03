#include "AnskyBasic.h"
#include "AnskyTrazado.h"
#include <QPainter>
#include <QRect>
#include <QPoint>

void Limpiar_lienzo(QPainter &painter, const QRect &area_a_limpiar){}

void Dibujar_triangulo(QPainter &painter, const QRect &rec,const ansky_direccion rotar){
    if(!rec.isValid()) return;
    if(rotar){
        short ancla_x = 0;
        short ancla_y = 0;
        short ang = 0;
        ang = 270;
        switch (rotar){
            case ansky_direccion::DERECHA:
                ancla_x = rec.x();
                ancla_y = rec.y();
                break;
            default: break;
        }
    }
    Dibujar_triangulo(painter,rec.x(),rec.y(),rec.width(),rec.height());}

void Dibujar_triangulo(QPainter &painter, const QPoint &coor, cuShort &base, cuShort &altura){
    Dibujar_triangulo(painter,coor.x(),coor.y(),base,altura);}

void Dibujar_triangulo(QPainter &painter, cuShort &pos_x, cuShort &pos_y, cuShort &base, cuShort &altura, cShort &ancla_x, cShort &ancla_y, cuShort &ang){
    UnirPuntos(painter,coor_triangulo(pos_x,pos_y,base,altura,ancla_x,ancla_y,ang));}

QList <QPointF>coor_triangulo(const QRect & rec, const QPointF &ancla, cuShort &ang){
    return coor_triangulo(rec.x(),rec.y(),rec.width(),rec.height(),ancla.x(),ancla.y(),ang);}

QList <QPointF>coor_triangulo(cShort &pos_x, cShort &pos_y, cuShort &base, cuShort &altura, cShort &ancla_x, cShort &ancla_y, cuShort &ang){
    QList<QPointF> lista;
    lista.append(QPointF((base/2) + pos_x, pos_y));
    lista.append(QPointF(base + pos_x, altura + pos_y));
    lista.append(QPointF(pos_x,altura + pos_y));
    return  lista;}
