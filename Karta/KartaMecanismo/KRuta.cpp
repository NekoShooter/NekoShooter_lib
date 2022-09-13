#include "KRuta.h"
#include "KartaCoor.h"
#include "KartaAlgoritmo.h"
#include <QWidget>

void KRuta::__inicializar(){
    __widget = nullptr;
    __matrix = nullptr;

    __lastre = nullptr;
    __nodoSeleccionado = nullptr;
    __nodoVisible = nullptr;

    __numeroDelNodo = 0;
    __radioNodo = 1;

    __nuevosPuntosAgregados = false;
    __nuevoCambio = __ruta->pNotificador();

    __arrancarGeneradoDeRuta = true;

    __modo = NULO;

    __rect = QRect();}



KRuta::KRuta(){
    __ruta = new HPtr<QList<QPointF>>;
    __inicializar(); }


KRuta::KRuta(const QList<QPointF> &ListaDeCoordenadas, QWidget *widget){
    __ruta = new HPtr<QList<QPointF>>;
    __inicializar();
    __widget = widget;
    CambiarListaDeCoordenadas(ListaDeCoordenadas);}



KRuta::KRuta(QList<QPointF> *ListaDeCoordenadas, QWidget *widget){
    __ruta = new HPtr<QList<QPointF>>;
    __inicializar();
    __widget = widget;
    EnlazarListaDeCoordenadas(ListaDeCoordenadas);}



void KRuta::EnlazarListaDeCoordenadas(QList<QPointF> *listaDeCoordenadas){
    if(!listaDeCoordenadas) return;
    *__ruta = listaDeCoordenadas;}


void KRuta::CambiarListaDeCoordenadas(const QList<QPointF> &listaDeCoordenadas){
    if(listaDeCoordenadas.isEmpty()){ __ruta->limpiar(); return;}
    *__ruta = listaDeCoordenadas;}



void KRuta::Resetear(){
    __ruta->destruir();
    __inicializar();}



void KRuta::Limpiar(){
    if(__ruta->esValido()){
        __ruta->ptr->clear();
        __x.limpiar();
        __y.limpiar();}}


void KRuta::ActivarRastreo(bool activar){
    if(!__widget) return;
    __widget->setMouseTracking(activar);}



void KRuta::FinalizarRuta(){
    if(not __ruta->esValido()) return;
    __deslastrarRuta();
    ActivarRastreo(false);
    __arrancarGeneradoDeRuta = false;}



void KRuta::ReanudarRuta(){
    if(not __ruta->esValido()) return;
    __lastrarRuta(*(__ruta->ptr->end() - 1));
    ActivarRastreo(true);
    __arrancarGeneradoDeRuta = true;}



void KRuta::AgregarPunto(const QPoint &punto){
    __ruta->CARGAR();

    if(__matrix) __ruta->ptr->append(__matrix->inverted().map(punto));
    else __ruta->ptr->append(punto);

    __x << __ruta->ptr->last().x();
    __y << __ruta->ptr->last().y();

    __nuevosPuntosAgregados = true;}


void KRuta::AgregarPunto(const QPointF &punto){
    /* proxima a eliminar */
    __ruta->CARGAR();
    __ruta->ptr->append(punto);}



QRect KRuta::ContornoNodo(QList<QPointF>::iterator nodo){
    if(nodo.i == nullptr) return QRect();
    short radio2 = __radioNodo * 2;
    return QRect((*nodo).x() - __radioNodo,(*nodo).y() - __radioNodo,radio2,radio2);}



QRect KRuta::ContornoNodoSelecionado(){return ContornoNodo(__nodoSeleccionado);}


QRect KRuta::ContornoNodoVisible(){
    if(__nodoVisible == __lastre) return QRect();
    return  ContornoNodo(__nodoVisible);}



void KRuta::EliminarNodoSelecionado(){
    if(!__ruta->esValido() || __nodoSeleccionado.i == nullptr) return;

    __ruta->ptr->removeAt(__numeroDelNodo - 1);
    __numeroDelNodo = 0;
    __nodoSeleccionado = nullptr;
    *__nuevoCambio = true;}



QList<QPointF>::iterator KRuta::Nodo(const QPoint &coordenada){
    __numeroDelNodo = 0;
    if(!__ruta->esValido() || !Rect().contains(coordenada) || __modo & LIBRE) return nullptr;
    short n = 1;
    for(QList<QPointF>::iterator i = __ruta->ptr->begin(); i != __ruta->ptr->end(); ++i,++n){
        if(ContornoNodo(i).contains(coordenada)) {
            __numeroDelNodo = n;
            return i;}}

    return nullptr;}



void KRuta::__identificarNodoVisible(const QPoint &coor){ __nodoVisible = Nodo(coor);}


const QRect &KRuta::Rect(){
    __generarRect();
    return  __rect;}


void KRuta::EnlazarMatrix(QMatrix * matrix){
    if(!matrix) return;
    __matrix = matrix;
    __invertedMatrix();}


void KRuta::__generarRect(){
    if(!__ruta->esValido() || __ruta->ptr->isEmpty()) return;
    if(!(__nuevosPuntosAgregados || __nuevoCambio->contenido()))return;
    if(__nuevoCambio->estado()){
        __x = __ruta->ptr->begin()->x();
        __y = __ruta->ptr->begin()->y();

        for( QList<QPointF>::iterator i = __ruta->ptr->begin() + 1 ;i != __ruta->ptr->end(); ++i){
            __x << i->x();
            __y << i->y();}}

    short ancho = __x.esSimetrico() ? __radioNodo * 2: (__x.max() + (__radioNodo * 2) - __x.min());
    short alto  = __y.esSimetrico() ? __radioNodo * 2: (__y.max() + (__radioNodo * 2) - __y.min());

    __rect.setRect(__x.min() - __radioNodo ,__y.min() - __radioNodo ,ancho , alto);}



void KRuta::__invertedMatrix(){
    if(!__ruta->esValido() || !__matrix) return;
    for(QList<QPointF>::iterator i = __ruta->ptr->begin();i != __ruta->ptr->end(); ++i)
        *i = __matrix->inverted().map(*i);
    *__nuevoCambio = true;}



void KRuta::__mapMatrix(){
    if(!__ruta->esValido() || !__matrix) return;
    for(QList<QPointF>::iterator i = __ruta->ptr->begin();i != __ruta->ptr->end(); ++i)
        *i = __matrix->map(*i);
    *__nuevoCambio = true;}



void KRuta::__modRuta_modNodo(const QPointF &coordenada){
    if(!__ruta->esValido()) return;

    if(__nodoSeleccionado.i && *__nodoSeleccionado != coordenada){
        *__nodoSeleccionado = coordenada;
        *__nuevoCambio = true;}}



void KRuta::__deslastrarRuta(){
    if(__lastre.i){
        __lastre = nullptr;
        __ruta->ptr->pop_back();}}



void KRuta::__lastrarRuta(const QPointF &coordenada){
    if(!__ruta->esValido() || !__widget) return;

    if(__modo == EDICION) __lastre = nullptr;

    else if(!__lastre.i){
        __ruta->ptr->append(coordenada);
        __lastre = __ruta->ptr->end() - 1;}
    else
        *__lastre = coordenada;}



void KRuta::mousePressEvent(QMouseEvent *event){
    if(!event || !__arrancarGeneradoDeRuta || !__modo) return;
    __deslastrarRuta();

    if(__modo & EDICION){
        __nodoSeleccionado = Nodo(event->pos());
        if(__modo == EDICION) return;}

    if(__nodoSeleccionado.i){
        ActivarRastreo(false);
        return;}

    AgregarPunto(event->pos());

    if(__modo & GUIA){
        ActivarRastreo(true);
        __lastrarRuta(event->pos());}}



void KRuta::mouseReleaseEvent(QMouseEvent * event){
    __nodoSeleccionado = nullptr;
    *__nuevoCambio = true;

    if(__modo & GUIA){
        ActivarRastreo(true);
        __lastrarRuta(event->pos());}
    else FinalizarRuta();}



void KRuta::mouseMoveEvent(QMouseEvent * event){
    if(!__arrancarGeneradoDeRuta) return;

    if(__nodoSeleccionado.i)
        *__nodoSeleccionado = event->pos();



    if(event->buttons() == Qt::NoButton && __modo & (GUIA|EDICION)){
        if(__lastre.i)*__lastre = event->pos();
        if(__modo & EDICION)__identificarNodoVisible(event->pos());}

    else if(__modo & LIBRE) {
        __deslastrarRuta();
        AgregarPunto(event->pos());}}


KRuta::iterator KRuta::begin(){
    return __ruta && __ruta->esValido() ? __ruta->ptr->begin() : nullptr;}

KRuta::iterator KRuta::end(){
    return __ruta && __ruta->esValido() ? __ruta->ptr->end() : nullptr;}



void KRuta::SimplificarRuta(){
    short __tolerancia = 1;
    if (!__ruta->esValido() || __tolerancia <= 0) return;

    QList<bool> PuntosMarcados;
    for(int i = 0; i < __ruta->ptr->size() - 1; ++i)
        PuntosMarcados.append(false);

    PuntosMarcados[0] = true;
    PuntosMarcados[__ruta->ptr->size() - 1] = true;

    __marcarRuta(PuntosMarcados, 0 , __ruta->ptr->size() - 1);

    QList<QPointF> TEMP;

    for(int i = 0; i < __ruta->ptr->size() - 1; ++i)
        if(PuntosMarcados[i]) TEMP.append((*__ruta->ptr)[i]);

    Limpiar();
    *__ruta = TEMP;}




void KRuta::__marcarRuta(QList<bool> &marcas, const int &inicio, const int &final){
    if(final <= inicio) return;

    double distanciaMax = 0.0;
    int indice = inicio;

    QPointF p = (*__ruta->ptr)[inicio] - (*__ruta->ptr)[final]; //partida
    double distancia = (p.x() * p.x()) + (p.y() + p.y());


    for(int i = inicio + 1; i < final - 1; ++i){
        if(distancia){
            QPointF s = (*__ruta->ptr)[i] - (*__ruta->ptr)[inicio]; //siguiente
            distancia = sqrt(((s.x() * s.x()) + (s.y() * s.y())) - pow((s.x() * p.x()) +(s.y() * p.y()),2)/distancia);}

        if(distancia > distanciaMax){
            distanciaMax = distancia;
            indice = i;}}

    short __tolerancia = 1;
    if(distanciaMax >= __tolerancia){
        marcas.replace(indice, true);

        __marcarRuta (marcas, inicio, indice);
        __marcarRuta (marcas, indice, final);}}
