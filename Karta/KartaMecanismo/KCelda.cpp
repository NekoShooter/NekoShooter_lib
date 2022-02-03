#include "KCelda.h"
#include <QMouseEvent>
#include <QWidget>

KCelda::KCelda(const QSize &tamanyo, const Karta::Modo &Modo){
    __cargarDatos();
    recargar(tamanyo,nullptr,Modo);}

KCelda::KCelda(const QWidget *WIDGET){
    __cargarDatos();
    widget = WIDGET;}

KCelda::KCelda(const QSize &tamanyo, const QWidget *WIDGET){
    __cargarDatos();
    recargar(tamanyo,WIDGET);}

KCelda::KCelda(const QSize &tamanyo, const QWidget *WIDGET, const Karta::Modo &Modo){
    __cargarDatos();
    recargar(tamanyo,WIDGET,Modo);}

void KCelda::recargar(const QSize &tamanyo, const QWidget *WIDGET, const Karta::Modo &Modo){
    if(tamanyo.isEmpty()) return;
    *Tam = tamanyo;
    widget = WIDGET;
    modo = Modo;}

void KCelda::__cargarDatos(){
    Tam = new QSize;
    frame = QSize(0,0);
    cursor_desplazado = new QPoint;
    cursor_click = new QPoint;
    margenH_der = margenV_sup = moverEnH = scroll_h = 0;
    margenH_izq = margenV_inf = moverEnV = scroll_v = 0;
    indices.data = KARTA_ERROR;
    mov_h = mov_v = true;
    widget = nullptr;}

KCelda::~KCelda(){
    if(Tam)   delete Tam;
    delete cursor_desplazado;
    delete cursor_click;}

void KCelda::cambiarTam(const QSize &tamanyo){
    if(tamanyo.isEmpty()) return;
    *Tam = tamanyo;}

bool KCelda::esValido() const{return !(!Tam || Tam->isEmpty());}

void KCelda::limpiar(){
    if(Tam)delete Tam;
    Tam = nullptr;
    margenH_der = margenH_izq = margenV_sup = margenV_inf = 0;
    BorrarRecuadro();}



void KCelda::BorrarRecuadro(){
    frame.setWidth(0);
    frame.setHeight(0);
    moverEnH = moverEnV = 0;}



void KCelda::restringirMov(const Karta::orientacion &mov){
    switch (mov) {
    case Karta::Horizontal:
        mov_v = false;
        mov_h = true;
        break;
    case Karta::Vertical:
        mov_h = false;
        mov_v = true;
        break;
    default:
        mov_h = mov_v = true;
        break;}}



void KCelda::Recuadro(const QSize &recuadro_interno, const Qt::Alignment &Alineacion){
    if(recuadro_interno.isEmpty() || (Tam->height() < recuadro_interno.height() || Tam->width() < recuadro_interno.width()))
        return;
    frame = recuadro_interno;
    alineacion = Alineacion;}

void KCelda::mouseMoveEvent(QMouseEvent *event){
    if(!event) return;
    *cursor_desplazado = event->pos();}

const k_index &KCelda::mousePressEvent(QMouseEvent *event){
    if(event) *cursor_click = event->pos();
    return mousePos(event);}

const k_index &KCelda::mousePos(QMouseEvent *event){
    indices.data = KARTA_ERROR;
    if(event){
        if(widget && ((event->pos().rx() >= widget->size().rwidth() - margenH_der) ||
                      (event->pos().ry() >= widget->size().rheight() - margenV_inf)))
            return indices;
        if((event->pos().rx() < margenH_izq) || event->pos().ry() < margenV_sup)
            return indices;

        indices.indice[_H_] = (event->pos().rx() - margenH_izq)/Tam->rwidth();
        indices.indice[_V_] = (event->pos().ry() - margenV_sup)/Tam->rheight();}
    return indices;}



QRect KCelda::qrect(cuShort &idx_h, cuShort &idx_v){
    if(!esValido()) return QRect(0,0,0,0);
    QSize size = *Tam;
    if(modo == Karta::Relativo){
        coor.setX((idx_h * Tam->width()) + margenH_izq + scroll_h);
        coor.setY((idx_v * Tam->height())+ margenV_sup + scroll_v);}
    else if(modo == Karta::Absoluto){
        coor.setX(((idx_h + scroll_h)* Tam->width() ) + margenH_izq);
        coor.setY(((idx_v + scroll_v)* Tam->height()) + margenV_sup);}
    else return QRect(0,0,0,0);

    if(!cursor_desplazado->isNull()){
        if(indices.indice[_H_] == idx_h && indices.indice[_V_] == idx_v){
            if(mov_h) coor.setX(coor.rx() + (cursor_desplazado->rx() - cursor_click->rx()));
            if(mov_v) coor.setY(coor.ry() + (cursor_desplazado->ry() - cursor_click->ry()));}}

    if(coor.ry() < margenV_sup){
        if(modo ==  Karta::Relativo){
            size.setHeight(Tam->height() - (margenV_sup- coor.ry()));
            coor.setY(margenV_sup);}
        else return QRect(0,0,0,0);}

    if (coor.rx() < margenH_izq) {
         if(modo == Karta::Relativo){
            size.setWidth(Tam->width() - (margenH_izq - coor.rx()));
            coor.setX(margenH_izq);}
        else return QRect(0,0,0,0);}

    if (widget &&((coor.ry() + Tam->height()) > (widget->size().height() - margenV_inf))){
         if(coor.ry() >= (widget->size().height() - margenV_inf)) return QRect(0,0,0,0);
         if(modo == Karta::Relativo)
             size.setHeight((widget->size().height() - margenV_inf) - coor.ry());
         else return QRect(0,0,0,0);}

    if (widget &&((coor.rx() + Tam->width()) > (widget->size().width() - margenH_der))) {
         if(coor.rx() >= (widget->size().width() - margenH_der)) return QRect(0,0,0,0);
         if(modo == Karta::Relativo){
             size.setWidth((widget->size().width() - margenH_der) - coor.rx());}
         else return QRect(0,0,0,0);}


    if(!frame.isEmpty()){
        cuShort margenX = Tam->width() - frame.width();
        cuShort margenY = Tam->height() - frame.height();
        coor.setX(coor.rx()+ moverEnH);
        coor.setY(coor.ry()+ moverEnV);
        size.setWidth(size.width() - margenX);
        size.setHeight(size.height() - margenY);

        switch (alineacion) {
            case Qt::AlignCenter:
                coor.setX(coor.rx() + (margenX / 2));
                coor.setY(coor.ry() + (margenY / 2));
                break;
            case Qt::AlignRight:
                coor.setX(coor.rx() + margenX);
                break;
            case Qt::AlignBottom:
                coor.setY(coor.ry() + margenY);
                break;
            default:
                break;}}

    if(size.height() <= 0 || size.width() <= 0) return QRect(0,0,0,0);

    return QRect(coor,size);}
