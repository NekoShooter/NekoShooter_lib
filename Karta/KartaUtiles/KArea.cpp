#include "KArea.h"
#include <QRect>


KArea::KArea(const QSize &tam){ Reiniciar(tam);}

void KArea::Reiniciar(const QSize &tam){
    __infX = tam.width();
    __infY = tam.height();
    __supX = __supY = 0;}


void KArea::Agregar(const QPoint &punto){
    AgregarPx(punto.x());
    AgregarPy(punto.y());}

void KArea::AgregarPx(const short &x){
    if(__infX > x) __infX = x;
    if(__supX < x) __supX = x;}

void KArea::AgregarPy(const short &y){
    if(__infY > y) __infY = y;
    if(__supY < y) __supY = y;}

QRect KArea::rect()   const {
    if(!EsValido()) return QRect();
    return QRect(__infX, __infY, __supX - __infX, __supY - __infY);}

QSize KArea::size()   const {
    return QSize(abs(__supX - __infX),abs(__supY - __infY));}

QPoint KArea::point() const {return QPoint(__infX,__infY);}
