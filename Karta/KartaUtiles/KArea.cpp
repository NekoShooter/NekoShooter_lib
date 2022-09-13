#include "KArea.h"
#include "KartaEsencial.h"
#include <QWidget>
#include <QMouseEvent>
#include <QRect>
#include <QMatrix>


/*
KArea::~KArea(){
    if(__vbordes) delete __vbordes;
    if(__ancla) delete __ancla;}


void KArea::__ReAsignar(){
    if(__px != __infX || __py != __infY || __sx != __supX || __sy != __supY){
        __px = __infX;  __sx = __supX;
        __py = __infY;  __sy = __supY;
        __modifcacionHecha = true;}
        SEGUROACTIVO = true;}


void KArea::ReAjustar(const QSize &tam){
    __infX = tam.width();
    __infY = tam.height();
    __supX = __supY = 0;
    __ReAsignar();}


void KArea::ReAjustar(const QRect &rect){
    __infX = rect.x();
    __infY = rect.y();
    __supX = rect.width() + __infX;
    __supY = rect.height() + __infY;
    __ReAsignar();}


void KArea::CambiarMargen(const short &margen){
    if(__margen == margen) return;
    __margen = margen;
    __modifcacionHecha = true;}


void KArea::ReAjustar(){
    short tem;
    if(__infX > __supX){  tem  = __supX;
                        __supX = __infX;
                        __infX =  tem;}

    if(__infY > __supY){  tem  = __supY;
                        __supY = __infY;
                        __infY =  tem; }
    __ReAsignar();}



void KArea::Expandir(const QPoint &punto){
    ExpandirPx(punto.x());
    ExpandirPy(punto.y());}


void KArea::ExpandirPx(const short &x){
    if(__infX > x) __infX = x;
    if(__supX < x) __supX = x;
    __ReAsignar();}


void KArea::ExpandirPy(const short &y){
    if(__infY > y) __infY = y;
    if(__supY < y) __supY = y;
    __ReAsignar();}



void KArea::Expandir(const QPoint& ancla, const QPoint &espacio, const Borde &b){

    short x = espacio.x() - ancla.x();
    short y = espacio.y() - ancla.y();

    if(!x && !y) return;

    switch (b) {
        case CEN:   __supX += x; __supY += y;
                    __infX += x; __infY += y; break;

        case EIDer: __supX += x; __supY += y; break;
        case EIIzq: __infX += x; __supY += y; break;
        case ESDer: __supX += x; __infY += y; break;
        case ESIzq: __infX += x; __infY += y; break;

        case LDer:  __supX += x; break;
        case LIzq:  __infX += x; break;
        case LSup:  __infY += y; break;
        case LInf:  __supY += y; break;

        default: return;}

    __ReAjustar();
    __modifcacionHecha = true;}


void KArea::__ReAjustar(){
    if (__infX > __supX){
          __px = __supX;
          __sx = __infX;}
    else {__px = __infX;
          __sx = __supX;}

    if (__infY > __supY){
          __py = __supY;
          __sy = __infY;}
    else {__py = __infY;
          __sy = __supY;}}



void KArea::ActualizarBordes(){
    if(!__margen || !EsValido()) return;

    if(!__vbordes) {
        __modifcacionHecha = true;
        __vbordes = new QVector<QRect>(CEN);}

    if(__modifcacionHecha.estado()){
        QRect *borde = __vbordes->data();
        for(short i = 0; i < CEN; ++i)
            borde[i] = rectForm(static_cast<KArea::Borde>(i));}}



QRect KArea::rectForm(const KArea::Borde &indx) const{
    switch (indx) {
        case CEN: return rect();

        case EIDer: return EsqInfDer(__margen);
        case EIIzq: return EsqInfIzq(__margen);

        case ESDer: return EsqSupDer(__margen);
        case ESIzq: return EsqSupIzq(__margen);

        case LDer:  return LatDer(__margen);
        case LIzq:  return LatIzq(__margen);
        case LSup:  return LatSup(__margen);
        case LInf:  return LatInf(__margen);
        default: break;}
    return QRect();}



KArea::Borde KArea::IdxLimite(const QPoint &p)const{
    if(!EsValido() || !__vbordes) return Borde::VACIO;

    if(__margen < 0 && Interno(__margen).contains(p))
        return Borde::CEN;

    else if(rect().contains(p)) return Borde::CEN;

    if(!__vbordes ) return Borde::VACIO;

    for(short i = 0; i != CEN; ++i){
        if(__vbordes->at(i).contains(p)) return static_cast<Borde>(i);}

    return Borde::VACIO;}



QRect KArea::rect(const Borde &p) const{
    if(p == Borde::VACIO) return QRect();
    if(p == CEN || !__margen) return rect();
    if(__vbordes && p < CEN && !__modifcacionHecha) return __vbordes->at(p);
    return rectForm(p);}



QRect KArea::rect(const QPoint &p) const{ return rect(IdxLimite(p));}

QRect KArea::rectActivo() const{ return rect(__rectActivo);}



QRect KArea::rect()   const {
    if(!EsValido()) return QRect();
    return QRect(__px, __py, __sx - __px, __sy - __py);}



QSize KArea::size()   const { return QSize(abs(__sx - __px),abs(__sy - __py));}



QPoint KArea::pointEIIzq() const {return QPoint(__px, __sy);}
QPoint KArea::pointEIDer() const {return QPoint(__sx, __sy);}
QPoint KArea::pointESDer() const {return QPoint(__px, __py);}
QPoint KArea::pointESIzq() const {return QPoint(__sx, __py);}



QRect KArea::EsqSupDer(const short &margen) const{
    if(margen < 0)
        return QRect(__sx + margen,__py,abs(margen), abs(margen));
    return QRect(__sx, __py - margen, margen, margen);}

QRect KArea::EsqSupIzq(const short &margen) const{
    if(margen < 0)
        return QRect(__px, __py,abs(margen), abs(margen));
    return QRect(__px - margen, __py - margen, margen, margen);}

QRect KArea::EsqInfDer(const short &margen) const{
    if(margen < 0)
        return QRect(__sx + margen,__sy + margen, abs(margen),abs(margen));
    return QRect(__sx,__sy, margen,margen);}

QRect KArea::EsqInfIzq(const short &margen) const{
    if(margen < 0)
        return QRect(__px , __sy + margen, abs(margen),abs(margen));
    return QRect(__px - margen, __sy, margen, margen);}

QRect KArea::LatDer(const short &margen) const{
    if(margen < 0)
        return QRect(__sx + margen, __py - margen, abs(margen) , (__sy - __py ) + (2 * margen));
    return QRect(__sx, __py, margen , __sy - __py);}

QRect KArea::LatIzq(const short &margen) const{
    if(margen < 0)
        return QRect(__px, __py - margen, abs(margen),(__sy - __py ) + (2 * margen));
    return QRect(__px - margen, __py , margen,__sy - __py);}

QRect KArea::LatSup(const short &margen) const{
    if(margen < 0)
        return QRect(__px - margen,__py, (__sx - __px ) + (2 * margen), abs(margen));
    return QRect(__px,__py - margen, __sx - __px, margen);}

QRect KArea::LatInf(const short &margen) const{
    if(margen < 0)
        return QRect(__px - margen,__sy + margen,(__sx - __px ) + (2 * margen), abs(margen));
    return QRect(__px,__sy,__sx - __px, margen);}

QRect KArea::Interno(const short &margen) const{
    if(margen < 0)
        return QRect(__px - margen, __py - margen,(__sx - __px ) + (2 * margen),(__sy - __py ) + (2 * margen));
    return rect();}


void KArea::ActivarRastreo(bool activar){
    if(!__widget) return;
    __widget->setMouseTracking(activar);}

void KArea::mousePressEvent(QMouseEvent *event){
    if(!event) return;

    if(!__ancla) __ancla = new QPoint(event->pos());
    else *__ancla = event->pos();

    ActivarRastreo(true);

    ActualizarBordes();
    __rectActivo = IdxLimite(event->pos());

    if(__rectActivo == VACIO) SEGUROACTIVO = false;}


void KArea::mouseMoveEvent (QMouseEvent *event){
    if(!event) return;
    if(event->buttons() != Qt::NoButton){

        if(!SEGUROACTIVO){
            ReAjustar(KRect(*__ancla,event->pos()));
            __rectActivo = CEN;
            SEGUROACTIVO = false;
            return;}

        Expandir(*__ancla, event->pos(), __rectActivo);
        *__ancla = event->pos();}

    else __rectActivo = IdxLimite(event->pos());}



void KArea::mouseReleaseEvent(){
    ActualizarBordes();
    __rectActivo = VACIO;
    SEGUROACTIVO = true;}

/*

QRect KArea::rect()   const {
    //if(!EsValido()) return QRect();
    return QRect(__infX, __infY, __supX - __infX, __supY - __infY);}



QSize KArea::size()   const {
    return QSize(abs(__supX - __infX),abs(__supY - __infY));}



QPoint KArea::point() const {return QPoint(__infX, __infY);}



QRect KArea::EsqSupDer(const short &margen) const{
    if(margen < 0)
        return QRect(__supX + margen,__infY,abs(margen), abs(margen));
    return QRect(__supX, __infY - margen, margen, margen);}

QRect KArea::EsqSupIzq(const short &margen) const{
    if(margen < 0)
        return QRect(__infX, __infY,abs(margen), abs(margen));
    return QRect(__infX - margen, __infY - margen, margen, margen);}

QRect KArea::EsqInfDer(const short &margen) const{
    if(margen < 0)
        return QRect(__supX + margen,__supY + margen, abs(margen),abs(margen));
    return QRect(__supX,__supY, margen,margen);}

QRect KArea::EsqInfIzq(const short &margen) const{
    if(margen < 0)
        return QRect(__infX , __supY + margen, abs(margen),abs(margen));
    return QRect(__infX - margen, __supY, margen, margen);}

QRect KArea::LatDer(const short &margen) const{
    if(margen < 0)
        return QRect(__supX + margen, __infY - margen, abs(margen) , (__supY - __infY ) + (2 * margen));
    return QRect(__supX, __infY, margen , __supY - __infY);}

QRect KArea::LatIzq(const short &margen) const{
    if(margen < 0)
        return QRect(__infX, __infY - margen, abs(margen),(__supY - __infY ) + (2 * margen));
    return QRect(__infX - margen, __infY , margen,__supY - __infY);}

QRect KArea::LatSup(const short &margen) const{
    if(margen < 0)
        return QRect(__infX - margen,__infY, (__supX - __infX ) + (2 * margen), abs(margen));
    return QRect(__infX,__infY - margen, __supX - __infX, margen);}

QRect KArea::LatInf(const short &margen) const{
    if(margen < 0)
        return QRect(__infX - margen,__supY + margen,(__supX - __infX ) + (2 * margen), abs(margen));
    return QRect(__infX,__supY,__supX - __infX, margen);}

QRect KArea::Interno(const short &margen) const{
    if(margen < 0)
        return QRect(__infX - margen, __infY - margen,(__supX - __infX ) + (2 * margen),(__supY - __infY ) + (2 * margen));
    return rect();}

*/


void KArea::__inicializar(){
    __rectActivo = Borde::VACIO;

    SEGUROACTIVO = false;
    __modifcacionHecha = false;
    __matrix = nullptr;

    __vbordes = nullptr;
    __widget = nullptr;
    //__ancla = nullptr;
    anclaje = false;}

KArea::~KArea(){
    if(__vbordes) delete __vbordes;
    //if(__ancla) delete __ancla;
}


void KArea::__ReAsignar(){
    if(__x != __xp || __y != __yp){
        __xp = __x;
        __yp = __y;
        __modifcacionHecha = true;}
        SEGUROACTIVO = true;}

void KArea::CargarMatrix(QMatrix *&matrix){
    __matrix = matrix;}

void KArea::ReAjustar(const QSize &tam){
    __infX = tam.width();
    __infY = tam.height();
    __supX = __supY = 0;
    __ReAsignar();}


void KArea::ReAjustar(const QRect &rect){
    QRect r = rect;
    /*
    __rx.limpiar(); __ry.limpiar();
    __rx<<rect.x()<<rect.width() + rect.x();
    __ry<<rect.y()<<rect.height() + rect.y();*/
    __rx.CambiarParametros(rect.x(),rect.width() + rect.x());
    __ry.CambiarParametros(rect.y(),rect.height() + rect.y());
    if(__matrix) r = __matrix->mapRect(rect);
    __x << r.x() << r.width() + r.x();
    __y << r.y() << r.height() + r.y();
    __ReAsignar();}


void KArea::CambiarMargen(const short &margen){
    if(__margen == margen) return;
    __margen = margen;
    __modifcacionHecha = true;}


void KArea::ReAjustar(){
    __xp.ReAjustar();
    __yp.ReAjustar();
    __ReAsignar();}



void KArea::Expandir(const QPoint &punto){
    ExpandirPx(punto.x());
    ExpandirPy(punto.y());}


void KArea::ExpandirPx(const short &x){
    __x << x;
    __ReAsignar();}


void KArea::ExpandirPy(const short &y){
    __y << y;
    __ReAsignar();}



void KArea::Expandir(const QPoint& ancla, const QPoint &espacio, const Borde &b){

    short x = espacio.x() - ancla.x();
    short y = espacio.y() - ancla.y();

    if(!x && !y) return;

    switch (b) {
        case CEN:   __x.rmax() += x; __y.rmax() += y;
                    __x.rmin() += x; __y.rmin() += y;

                    __rx.rmax() += x; __ry.rmax() += y;
                    __rx.rmin() += x; __ry.rmin() += y;break;

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


void KArea::__ReAjustar(){
    __rx.ReAjustar(); __ry.ReAjustar();
    __xp.limpiar(); __yp.limpiar();
    __xp << __x;
    __yp << __y;}



void KArea::ActualizarBordes(){
    if(!__margen || !EsValido()) return;

    if(!__vbordes) {
        __modifcacionHecha = true;
        __vbordes = new QVector<QRect>(CEN);}

    if(__modifcacionHecha.estado()){
        QRect *borde = __vbordes->data();
        for(short i = 0; i < CEN; ++i)
            borde[i] = rectForm(static_cast<KArea::Borde>(i));}}



QRect KArea::rectForm(const KArea::Borde &indx) const{
    if(!__xp.estaVacio() && !__yp.estaVacio()){
        switch (indx) {
            case CEN: return rect();

            case EIDer: return EsqInfDer(__margen);
            case EIIzq: return EsqInfIzq(__margen);

            case ESDer: return EsqSupDer(__margen);
            case ESIzq: return EsqSupIzq(__margen);

            case LDer:  return LatDer(__margen);
            case LIzq:  return LatIzq(__margen);
            case LSup:  return LatSup(__margen);
            case LInf:  return LatInf(__margen);
        default: break;}}
    return QRect();}



KArea::Borde KArea::IdxLimite(const QPoint &p)const{
    if(!EsValido() || !__vbordes) return Borde::VACIO;

    if(__margen < 0 && Interno(__margen).contains(p))
        return Borde::CEN;

    else if(rect(false).contains(p)) return Borde::CEN;

    if(!__vbordes ) return Borde::VACIO;

    for(short i = 0; i != CEN; ++i){
        if(__vbordes->at(i).contains(p)) return static_cast<Borde>(i);}

    return Borde::VACIO;}



QRect KArea::rect(const Borde &p) const{
    if(p == Borde::VACIO) return QRect();
    if(p == CEN || !__margen) return rect();
    if(__vbordes && p < CEN && !__modifcacionHecha) return __vbordes->at(p);
    return rectForm(p);}



QRect KArea::rect(const QPoint &p) const{ return rect(IdxLimite(p));}

QRect KArea::rectActivo() const{
    if(EsValido()) return rectForm(__rectActivo);
    return rect(VACIO);}



QRect KArea::rect(bool matrixActivada)   const {
    if(!EsValido()) return QRect();
    //if(__matrix && matrixActivada) return __matrix->inverted().mapRect(QRect(__xp.min(), __yp.min(), __xp.max() - __xp.min(), __yp.max() - __yp.min()));
    return QRect(__rx.min(), __ry.min(), __rx.max() - __rx.min(), __ry.max() - __ry.min());}



QSize KArea::size()   const { return QSize(abs(__xp.max() - __xp.min()),abs(__yp.max() - __yp.min()));}



QPoint KArea::pointEIIzq() const {return QPoint(__xp.min(), __yp.max());}
QPoint KArea::pointEIDer() const {return QPoint(__xp.max(), __yp.max());}
QPoint KArea::pointESDer() const {return QPoint(__xp.min(), __yp.min());}
QPoint KArea::pointESIzq() const {return QPoint(__xp.max(), __yp.min());}



QRect KArea::EsqSupDer(const short &margen) const{
    if(margen < 0)
        return QRect(__xp.max() + margen,__yp.min(),abs(margen), abs(margen));
    return QRect(__xp.max(), __yp.min() - margen, margen, margen);}

QRect KArea::EsqSupIzq(const short &margen) const{
    if(margen < 0)
        return QRect(__xp.min(), __yp.min(),abs(margen), abs(margen));
    return QRect(__xp.min() - margen, __yp.min() - margen, margen, margen);}

QRect KArea::EsqInfDer(const short &margen) const{
    if(margen < 0)
        return QRect(__xp.max() + margen,__yp.max() + margen, abs(margen),abs(margen));
    return QRect(__xp.max(),__yp.max(), margen,margen);}

QRect KArea::EsqInfIzq(const short &margen) const{
    if(margen < 0)
        return QRect(__xp.min() , __yp.max() + margen, abs(margen),abs(margen));
    return QRect(__xp.min() - margen, __yp.max(), margen, margen);}

QRect KArea::LatDer(const short &margen) const{
    if(margen < 0)
        return QRect(__xp.max() + margen, __yp.min() - margen, abs(margen) , (__yp.max() - __yp.min() ) + (2 * margen));
    return QRect(__xp.max(), __yp.min(), margen , __yp.max() - __yp.min());}

QRect KArea::LatIzq(const short &margen) const{
    if(margen < 0)
        return QRect(__xp.min(), __yp.min() - margen, abs(margen),(__yp.max() - __yp.min() ) + (2 * margen));
    return QRect(__xp.min() - margen, __yp.min() , margen,__yp.max() - __y.min());}

QRect KArea::LatSup(const short &margen) const{
    if(margen < 0)
        return QRect(__xp.min() - margen,__yp.min(), (__xp.max() - __xp.min() ) + (2 * margen), abs(margen));
    return QRect(__xp.min(),__yp.min() - margen, __xp.max() - __xp.min(), margen);}

QRect KArea::LatInf(const short &margen) const{
    if(margen < 0)
        return QRect(__xp.min() - margen,__yp.max() + margen,(__xp.max() - __xp.min() ) + (2 * margen), abs(margen));
    return QRect(__xp.min(),__yp.max(),__xp.max() - __xp.min(), margen);}

QRect KArea::Interno(const short &margen) const{
    if(margen < 0)
        return QRect(__xp.min() - margen, __yp.min() - margen,(__xp.max() - __xp.min() ) + (2 * margen),(__yp.max() - __yp.min() ) + (2 * margen));
    return rect();}

QRect KArea::Contorno()const{
    return QRect(__xp.min(), __yp.min(), __xp.max() - __xp.min(), __yp.max() - __yp.min());}


void KArea::ActivarRastreo(bool activar){
    if(!__widget) return;
    __widget->setMouseTracking(activar);}

void KArea::mousePressEvent(QMouseEvent *event){
    if(!event) return;

    if(!__xp.estaVacio() && !__yp.estaVacio()){
        __ancla = event->pos();

        ActivarRastreo(true);

        ActualizarBordes();
        __rectActivo = IdxLimite(event->pos());

        if(__rectActivo == VACIO) SEGUROACTIVO = false;
        return;}
    __rectActivo = VACIO; SEGUROACTIVO = false;}


void KArea::mouseMoveEvent (QMouseEvent *event){
    if(!event) return;
    if(event->buttons() != Qt::NoButton){
        if(!SEGUROACTIVO){
            QRect r;
            if (__matrix) r = KRect(__matrix->inverted().map(__ancla),__matrix->inverted().map(event->pos()));
            else r = KRect(__ancla,event->pos());
            ReAjustar(r);
            __rectActivo = CEN;
            SEGUROACTIVO = false;
            return;}

        //if(__matrix) Expandir(__matrix->inverted().map(__ancla),__matrix->inverted().map(event->pos()),__rectActivo);
        Expandir(__ancla, event->pos(), __rectActivo);
        __ancla = event->pos();}

    else __rectActivo = IdxLimite(event->pos());}



void KArea::mouseReleaseEvent(){
    ActualizarBordes();
    __rectActivo = VACIO;
    SEGUROACTIVO = true;}




