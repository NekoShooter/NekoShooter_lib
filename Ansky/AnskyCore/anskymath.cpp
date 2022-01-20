#include "anskymath.h"
#include "kartacoor.h"

QList<QPointF> Generar_triangulo(const QPointF &posicion,cDouble &base, cDouble &altura){
    return Generar_triangulo(posicion.x(),posicion.y(),base,altura);}

QList<QPointF> Generar_triangulo(const QPoint &posicion,cDouble &base, cDouble &altura){
    return Generar_triangulo(posicion.x(),posicion.y(),base,altura);}

QList <QPointF>Generar_triangulo(const QRect & rec){
    if(rec.isValid()){
        QList<QPointF> lista;
        return lista;}
    return Generar_triangulo(rec.x(),rec.y(),rec.width(),rec.height());}

QList <QPointF>Generar_triangulo(cDouble &pos_x, cDouble &pos_y, cDouble &base, cDouble &altura){
    QList<QPointF> lista;
    lista.append(QPointF((base/2) + pos_x, pos_y));
    lista.append(QPointF(base + pos_x, altura + pos_y));
    lista.append(QPointF(pos_x,altura + pos_y));
    return  lista;}




QList<QPointF> Generar_trianguloRec(const QPointF &posicion,cDouble &base, cDouble &altura){
    return Generar_trianguloRec(posicion.x(),posicion.y(),base,altura);}

QList<QPointF> Generar_trianguloRec(const QPoint &posicion,cDouble &base, cDouble &altura){
    return Generar_trianguloRec(posicion.x(),posicion.y(),base,altura);}

QList<QPointF> Generar_trianguloRec(const QRect &rec){
    if(!rec.isValid()){
        QList<QPointF> lista;
        return lista;}
    return Generar_trianguloRec(rec.x(),rec.y(),rec.width(),rec.height());}

QList<QPointF> Generar_trianguloRec(cDouble &pos_x, cDouble &pos_y, cDouble &base, cDouble &altura){
    QList<QPointF> lista;
    lista.append(QPointF(pos_x, pos_y));
    lista.append(QPointF(base + pos_x, altura + pos_y));
    lista.append(QPointF(pos_x,altura + pos_y));
    return  lista;}



void rotarQPoints(QList<QPoint> *lista, const QPoint &ancla, cDouble &ang){
    if(lista == nullptr || !ANGULO_VALIDO(ang)) return;
    for(QList<QPoint>::iterator l = lista->begin(); l != lista->end(); l++)
        *l = rotarCoordenada(ancla,*l,ang).toPoint();}

void rotarQPointFs(QList<QPointF> *lista, const QPointF &ancla, cDouble &ang){
    if(lista == nullptr || !ANGULO_VALIDO(ang)) return;
    for(QList<QPointF>::iterator l = lista->begin(); l != lista->end(); l++)
        *l = rotarCoordenada(ancla,*l,ang);}
