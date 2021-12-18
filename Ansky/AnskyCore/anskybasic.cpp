#include "anskybasic.h"
#include <QPainter>
#include <QRect>
#include <QPoint>

void Limpiar_lienzo(QPainter &painter, const QRect &area_a_limpiar){}

void Dibujar_triangulo(QPainter &painter, const QRect &rec){
    if(!rec.isValid()) return;
    Dibujar_triangulo(painter,rec.x(),rec.y(),rec.width(),rec.height());}

void Dibujar_triangulo(QPainter &painter, const QPoint &coor, cuShort &base, cuShort &altura){
    Dibujar_triangulo(painter,coor.x(),coor.y(),base,altura);}

void Dibujar_triangulo(QPainter &painter, cuShort &pos_x, cuShort &pos_y, cuShort &base, cuShort &altura){
    Dibujar_figura(painter,coor_triangulo(pos_x,pos_y,base,altura));}

QList <QPoint>coor_triangulo(const QRect & rec, cuShort &ang){
    return coor_triangulo(rec.x(),rec.y(),rec.width(),rec.height(),ang);}

QList <QPoint>coor_triangulo(cuShort &pos_x, cuShort &pos_y, cuShort &base, cuShort &altura, cuShort &ang){
    QList<QPoint> lista;
    lista.append(QPoint((base/2) + pos_x, pos_y));
    lista.append(QPoint(base + pos_x, altura + pos_y));
    lista.append(QPoint(pos_x,altura + pos_y));
    return  lista;}

void Dibujar_figura(QPainter &painter, const QList<QPoint> &lista_de_coor){
    if(lista_de_coor.isEmpty()) return;
    auto i = lista_de_coor.begin();
    for(;i + 1 != lista_de_coor.end(); i++){
        painter.drawLine(*i,*(i + 1));}
    painter.drawLine(*i,*lista_de_coor.begin());}
