#include "kartacoor.h"
#include <math.h>
#define PI 3.14159265
#define rad(ang) (ang * (PI/180))

QPointF coordenadasCirculares(const QPointF &CENTRO, cFloat &RADIO, cFloat &NumDeSecciones, cFloat &index, Karta::Sentido sentido){
    if(NumDeSecciones <= 0|| RADIO <= 0 || index < 0 || index > NumDeSecciones) return CENTRO;

    float x = 0;
    float y = 0;
    const float UNIDAD = 360/NumDeSecciones;

    switch (sentido) {
    case Karta::Horario:
        y = 90 -((UNIDAD * index) + UNIDAD);
        x = 90 - fabs(y);
        break;
    case Karta::Anti_horario:
        x = 90 -((UNIDAD * index) + UNIDAD);
        y = 90 - fabs(x);
        break;
    case Karta::Radial:
        x = 90 -(UNIDAD * index);
        y = 90 - fabs(x);
        break;
    default: return CENTRO;}

    double punto_coor_x = sin(rad(x)) * RADIO;
    double punto_coor_y = sin(rad(y)) * RADIO;

    return QPointF((CENTRO.x() + punto_coor_x),(CENTRO.y() - punto_coor_y));}



/***********************************************************************************************/


QRect posicionarCeldas(KCelda &C, KFormato &F, KScroll &S, KCursor &P, const Karta::Modo &modo){

    if(!C.esValido()) return QRect(0,0,0,0);
    S.rectificar();
    QPoint coor;
    QSize size = *C.Tam;
    if(modo == Karta::Relativo){
        coor.setX(((C.pos.indice[_H_] * C.Tam->width()) + S.scroll_h) + P.cursorX);
        coor.setY(((C.pos.indice[_V_] * C.Tam->height()) + S.scroll_v) +P.cursorY);}
    else if(modo == Karta::Absoluto){
        coor.setX(((C.pos.indice[_H_] + S.scroll_h)* C.Tam->width()) + P.cursorX);
        coor.setY(((C.pos.indice[_V_] + S.scroll_v) * C.Tam->height()) + P.cursorY);}
    else return QRect(0,0,0,0);

    if(coor.y() < S.limiteMin_v){
        if(modo ==  Karta::Relativo){
            size.setHeight(C.Tam->height() - (S.limiteMin_v - coor.y()));
            coor.setY(S.limiteMin_v);}
        else return QRect(0,0,0,0);}

    else if (coor.x() < S.limiteMin_h) {
        if(modo == Karta::Relativo){
            size.setWidth(C.Tam->width() - (S.limiteMin_h - coor.x()));
            coor.setX(S.limiteMin_h);}
        else return QRect(0,0,0,0);}

    else if(S.limiteMax_v &&(coor.y() + C.Tam->height()) > S.limiteMax_v){
         if(modo == Karta::Relativo)size.setHeight(S.limiteMax_v - coor.y());
         else if(coor.y() > S.limiteMax_v)return QRect(0,0,0,0);}

    else if (S.limiteMax_h &&(coor.x() + C.Tam->width()) > S.limiteMax_h) {
        if(modo == Karta::Relativo)size.setWidth(S.limiteMax_h - coor.x());
        else if(coor.x() > S.limiteMax_h) return QRect(0,0,0,0);}
    else size = *C.Tam;

    F.rectificar(C);

    if(F.moverEnX)coor.setX(coor.x()+ F.moverEnX);
    if(F.moverEnY)coor.setY(coor.y()+ F.moverEnY);
    if(F.margenX) size.setWidth(size.width() - (F.margenX * 2));
    if(F.margenY) size.setHeight(size.height() - (F.margenY * 2));

    if(size.height() <= 0 || size.width() <= 0) return QRect(0,0,0,0);

    switch (F.alineacion) {
        case Qt::AlignCenter:
            coor.setX(coor.x() + F.margenX);
            coor.setY(coor.y() + F.margenY);
            break;
        case Qt::AlignLeft:
            coor.setY(coor.y() + F.margenY);
            break;
        case Qt::AlignRight:
            coor.setX(coor.x() + (F.margenX * 2));
            coor.setY(coor.y() + F.margenY);
            break;
        case Qt::AlignTop:
            coor.setX(coor.x() + F.margenX);
            break;
        case Qt::AlignBottom:
            coor.setX(coor.x() + F.margenX);
            coor.setY(coor.y() + (F.margenY * 2));
            break;
        default:
            break;}




    return QRect(coor,size);}


QRect posicionarCeldas(KCelda &C, KScroll &S,  KCursor &P, const Karta::Modo &modo){
    KFormato F; return posicionarCeldas(C,F,S,P,modo);}
QRect posicionarCeldas(KCelda &C, KFormato &F, KScroll &S, const Karta::Modo &modo){
    KCursor P; return posicionarCeldas(C,F,S,P,modo);}
QRect posicionarCeldas(KCelda &C, KFormato &F, KCursor &P, const Karta::Modo &modo){
    KScroll S; return posicionarCeldas(C,F,S,P,modo);}
QRect posicionarCeldas(KCelda &C, KScroll &S,  const Karta::Modo &modo){
    KFormato F; KCursor P; return posicionarCeldas(C,F,S,P,modo);}
QRect posicionarCeldas(KCelda &C, KCursor &P,  const Karta::Modo &modo){
    KFormato F; KScroll S; return posicionarCeldas(C,F,S,P,modo);}
QRect posicionarCeldas(KCelda &C, KFormato &F, const Karta::Modo &modo){
    KScroll S;  KCursor P; return posicionarCeldas(C,F,S,P,modo);}
QRect posicionarCeldas(KCelda &C, const Karta::Modo &modo){
    KFormato F; KScroll S;  KCursor P; return posicionarCeldas(C,F,S,P,modo);}


/***********************************************************************************************/
