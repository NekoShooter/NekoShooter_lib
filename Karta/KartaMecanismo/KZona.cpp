#include "KZona.h"
#include "KartaEsencial.h"
#include "KartaCoor.h"
#include "KartaMath.h"

#include <QWidget>
#include <QMatrix>
#include <QMouseEvent>
#include <QRect>


KZona::~KZona(){
    if(__vbordes) delete __vbordes;
    if(__ancla) delete __ancla;
    if(__rect) delete __rect;}


void KZona::__ReAsignar(){

    if(__xp != __x || __yp != __y){
        __xp = __xc = __x;
        __yp = __yc = __y;
        __modifcacionHecha = true;}
        SEGUROACTIVO = true;}


void KZona::ReAjustar(const QSize &tam){
    __infX = tam.width();
    __infY = tam.height();
    __supX = __supY = 0;
    __ReAsignar();}


void KZona::ReAjustar(const QRect &rect){
    if(!__rect) __rect = new QRect(rect);
    else *__rect = rect;
    QRect r = *__rect;
    if(__matrix) r = __matrix->mapRect(*__rect);


    __x.CambiarParametros(r.x(),r.width() + r.x());
    __y.CambiarParametros(r.y(),r.height() + r.y());
    __ReAsignar();}


void KZona::CambiarMargen(const short &margen){
    if(__margen == margen) return;
    __margen = margen;
    __modifcacionHecha = true;}

void KZona::CambiarQMatrix(QMatrix *&matrix){ __matrix = matrix; }


void KZona::ReAjustar(){
    if(__x.estaInvertido()) __x.ReAjustar();
    if(__y.estaInvertido()) __y.ReAjustar();
    __ReAsignar();}



void KZona::Expandir(const QPoint &punto){
    ExpandirPx(punto.x());
    ExpandirPy(punto.y());}


void KZona::ExpandirPx(const short &x){
    __x << x;
    __ReAsignar();}


void KZona::ExpandirPy(const short &y){
    __y << y;
    __ReAsignar();}



void KZona::Expandir(const QPoint& ancla, const QPoint &espacio, const Borde &b){
    if(__x.estaVacio() || __y.estaVacio()) return;

    short x = espacio.x() - ancla.x();
    short y = espacio.y() - ancla.y();

    if(!x && !y) return;

    switch (b) {
        case RECT:  __x.rmax() += x; __y.rmax() += y;
                    __x.rmin() += x; __y.rmin() += y; break;

        case EIDer: __x.rmax() += x; __y.rmax() += y; break;
        case EIIzq: __x.rmin() += x; __y.rmax() += y; break;
        case ESDer: __x.rmax() += x; __y.rmin() += y; break;
        case ESIzq: __x.rmin() += x; __y.rmin() += y; break;

        case LDer:  __x.rmax() += x; break;
        case LIzq:  __x.rmin() += x; break;
        case LSup:  __y.rmin() += y; break;
        case LInf:  __y.rmax() += y; break;

        default: return;}

    __ReAjustar();
    __modifcacionHecha = true;}


void KZona::__ReAjustar(){
    __xc.limpiar(); __yc.limpiar();
    __xc << __x;
    __yc << __y;

    __xp = __x;
    __yp = __y;
    if(__xp.estaInvertido())  __xp.invertir();
    if(__yp.estaInvertido())  __yp.invertir();}



void KZona::ActualizarBordes(){
    if(!__margen || !EsValido()) return;

    if(!__vbordes) {
        __modifcacionHecha = true;
        __vbordes = new QVector<QRect>(RECT);}

    if(__modifcacionHecha.estado()){
        QRect *borde = __vbordes->data();
        for(short i = 0; i < TOTAL; ++i)
            borde[i] = rectForm(static_cast<KZona::Borde>(i));}}



QRect KZona::rectForm(const KZona::Borde &indx) const{
    switch (indx) {
        case RECT: return rect();

        case EIDer: return InfDer (__margen);
        case EIIzq: return InfIzq (__margen);

        case ESDer: return SupDer (__margen);
        case ESIzq: return SupIzq (__margen);

        case LDer:  return LatDer (__margen);
        case LIzq:  return LatIzq (__margen);
        case LSup:  return LatSup (__margen);
        case LInf:  return LatInf (__margen);
        case INT:   return Interno(__margen);
        case TOTAL: return Total  (__margen);
        default: break;}

    return QRect();}



KZona::Borde KZona::IdxLimite(const QPoint &p)const{
    if(!EsValido() || !__vbordes) return Borde::VACIO;
/*
    if(!Total(__margen).contains(p)) return Borde::VACIO;

    else if(__margen < 0 && Interno(__margen).contains(p))
        return Borde::RECT;

    else if(rect().contains(p)) return Borde::RECT;
    */

    if(!__vbordes ) return Borde::VACIO;

    for(short i = 0; i != TOTAL; ++i){
        if(__vbordes->at(i).contains(p)) return static_cast<Borde>(i);}

    return Borde::VACIO;}



QRect KZona::rect(const Borde &p) const{
    if(p == Borde::VACIO) return QRect();
    if(p == RECT || !__margen) return rect();
    if(__vbordes && p < INT && !__modifcacionHecha) return __vbordes->at(p);
    return rectForm(p);}



QRect KZona::rect(const QPoint &p) const{ return rect(IdxLimite(p));}

QRect KZona::rectActivo() const{ return rect(__rectActivo);}



QRect KZona::rect()   const {
    if(EsValido() || !SEGUROACTIVO){
        if(__rect) return *__rect;
        if(__matrix) return __matrix->inverted().mapRect(QRect(SupDer(), size()));
        else return QRect(SupDer(), size());}
    return QRect();}


QSize KZona::size()   const {
    return QSize(__xp.max() - __xp.min(), __yp.max() - __yp.min());}


QPoint KZona::SupIzq() const{ return QPoint(__xp.max(), __yp.min());}
QPoint KZona::SupDer() const{ return QPoint(__xp.min(), __yp.min());}
QPoint KZona::InfIzq() const{ return QPoint(__xp.min(), __yp.max());}
QPoint KZona::InfDer() const{ return QPoint(__xp.max(), __yp.max());}



QRect KZona::SupDer(const short &margen) const{
    if(margen < 0)
        return QRect(__xc.max() + margen,__yc.min(),abs(margen), abs(margen));
    return QRect(__xc.max(), __yc.min() - margen, margen, margen);}


QRect KZona::SupIzq(const short &margen) const{
    if(margen < 0)
        return QRect(__xc.min(), __yc.min(),abs(margen), abs(margen));
    return QRect(__xc.min() - margen, __yc.min() - margen, margen, margen);}


QRect KZona::InfDer(const short &margen) const{
    if(margen < 0)
        return QRect(__xc.max() + margen,__yc.max() + margen, abs(margen),abs(margen));
    return QRect(__xc.max(),__yc.max(), margen,margen);}


QRect KZona::InfIzq(const short &margen) const{
    if(margen < 0)
        return QRect(__xc.min() , __yc.max() + margen, abs(margen),abs(margen));
    return QRect(__xc.min() - margen, __yc.max(), margen, margen);}


QRect KZona::LatDer(const short &margen) const{
    if(margen < 0)
        return QRect(__xc.max() + margen, __yc.min() - margen, abs(margen) , (__yc.max() - __yc.min()) + (2 * margen));
    return QRect(__xc.max(), __yc.min(), margen , __yc.max() - __yc.min());}


QRect KZona::LatIzq(const short &margen) const{
    if(margen < 0)
        return QRect(__xc.min(), __yc.min() - margen, abs(margen),(__yc.max() - __yc.min() ) + (2 * margen));
    return QRect(__xc.min() - margen, __yc.min(), margen,__yc.max() - __yc.min());}


QRect KZona::LatSup(const short &margen) const{
    if(margen < 0)
        return QRect(__xc.min() - margen,__yc.min(), (__yc.max() - __xc.min() ) + (2 * margen), abs(margen));
    return QRect(__xc.min(),__yc.min() - margen, __xc.max() - __xc.min(), margen);}


QRect KZona::LatInf(const short &margen) const{
    if(margen < 0)
        return QRect(__xc.min() - margen,__yc.max() + margen,(__xc.max() - __xc.min() ) + (2 * margen), abs(margen));
    return QRect(__xc.min(),__yc.max(),__xc.max() - __xc.min(), margen);}


QRect KZona::Interno(const short &margen) const{
    if(margen < 0)
        return QRect(__xc.min() - margen, __yc.min() - margen,(__xc.max() - __xc.min() ) + (2 * margen),(__yc.max() - __yc.min() ) + (2 * margen));
    return Contorno();}


QRect KZona::Contorno()const{
    if(__matrix)
        return QRect(__xc.min(), __yc.min(), __xc.max() - __xc.min(), __yc.max() - __yc.min());
    else return rect();}

QRect KZona::Total(const short &margen)const{
    if(margen > 0)
        return QRect(__xc.min() - margen, __yc.min() - margen, (__xc.max() - __xc.min()) + margen, (__yc.max() - __yc.min()) + margen);
    else return Contorno();}


void KZona::ActivarRastreo(bool activar){
    if(!__widget) return;
    __widget->setMouseTracking(activar);}

void KZona::mousePressEvent(QMouseEvent *event){
    if(!event) return;
    if(!EsValido()) return;

    if(!__ancla) __ancla = new QPoint(event->pos());
    else *__ancla = event->pos();

    ActivarRastreo(true);

    ActualizarBordes();
    if(__matrix) __rectActivo = IdxLimite(__matrix->inverted().map(event->pos()));
    else __rectActivo = IdxLimite(event->pos());
    //return;

    if(__rectActivo == VACIO) SEGUROACTIVO = false;}


void KZona::mouseMoveEvent (QMouseEvent *event){
    if(!event) return;
    if(!EsValido()) return;
    if(event->buttons() != Qt::NoButton){

        if(!SEGUROACTIVO){
            if(__matrix) ReAjustar(KRect(__matrix->inverted().map(*__ancla),__matrix->inverted().map(event->pos())));
            else
                ReAjustar(KRect(*__ancla,event->pos()));
            __rectActivo = RECT;
            SEGUROACTIVO = false;
            return;}
        if(__matrix) Expandir(__matrix->inverted().map(*__ancla), __matrix->inverted().map(event->pos()), __rectActivo);
        else Expandir(*__ancla, event->pos(), __rectActivo);
        *__ancla = event->pos();}

    else {
        if(__matrix) __rectActivo = IdxLimite(__matrix->inverted().map(event->pos()));
        else __rectActivo = IdxLimite(event->pos());}
    //else __rectActivo = IdxLimite(event->pos());
}



void KZona::mouseReleaseEvent(){
    ActualizarBordes();
    __rectActivo = VACIO;
    SEGUROACTIVO = true;}
