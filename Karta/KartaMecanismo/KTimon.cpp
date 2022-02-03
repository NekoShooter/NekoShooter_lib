#include "KTimon.h"
#include "KartaCoor.h"
#include "KartaMath.h"
#include <QImage>
#include <QMatrix>
#include <QWidget>
#include <QMouseEvent>

KTimon::KTimon(const QSize &tamBase, const QSize &tam){
    __Inicializar();
    __NuevoQMatrix();
    CambiarParametros(__qmatrix,tamBase,tam,QPoint(0,0));}


KTimon::KTimon(const QSize &tamBase, const QSize &tam, const QPoint &posicion){
    __Inicializar();
    __NuevoQMatrix();
    CambiarParametros(__qmatrix,tamBase,tam,posicion);}


KTimon::KTimon(const QSize &tamBase, const QRect &rect){
    __Inicializar();
    if(rect.isEmpty()) return;
    __NuevoQMatrix();
    CambiarParametros(__qmatrix,tamBase,rect);}


KTimon::KTimon(const QSize &tamBase, const QImage &img){
    __Inicializar();
    if(img.isNull()) return;
    __NuevoQMatrix();
    CambiarParametros(__qmatrix,tamBase,img,QPoint(0,0));}


KTimon::KTimon(const QSize &tamBase, const QImage &img, const QPoint &posicion){
    __Inicializar();
    if(img.isNull()) return;
    __NuevoQMatrix();
    CambiarParametros(__qmatrix,tamBase,img,posicion);}


KTimon::KTimon(QMatrix *&matrix,const QSize &tamBase, const QSize &tam){
    __Inicializar();
    if(!matrix)return;
    CambiarParametros(__qmatrix,tamBase,tam,QPoint(0,0));}


KTimon::KTimon(QMatrix *&matrix,const QSize &tamBase, const QSize &tam, const QPoint &posicion){
    __Inicializar();
    CambiarParametros(matrix,tamBase,tam,posicion);}


KTimon::KTimon(QMatrix *&matrix,const QSize &tamBase, const QRect &rect){
    __Inicializar();
    CambiarParametros(matrix,tamBase,rect);}


KTimon::KTimon(QMatrix *&matrix,const QSize &tamBase, const QImage &img){
    __Inicializar();
    CambiarParametros(matrix,tamBase,img.rect());}


KTimon::KTimon(QMatrix *&matrix,const QSize &tamBase, const QImage &img, const QPoint &posicion){
    __Inicializar();
    CambiarParametros(matrix,tamBase,img.size(),posicion);}


void KTimon::CambiarParametros(QMatrix *&matrix,const QSize &tamBase, const QImage &img, const QPoint &posicion){
    CambiarParametros(matrix,tamBase,img.size(),posicion);}


void KTimon::CambiarParametros(QMatrix *&matrix,const QSize &tamBase, const QRect &rect){
    CambiarParametros(matrix,tamBase,rect.size(),QPoint(rect.x(),rect.y()));}


void KTimon::CambiarParametros(QMatrix *&matrix,const QSize &tamBase, const QSize &tam, const QPoint &posicion){
    if(!matrix || tam.isNull() || tamBase.isNull()) return;
    AdoptarQMatrix(matrix);
    CambiarTamBase(tamBase);
    CambiarTam(tam);
    CambiarPosicion(posicion);
    Actualizar();}


void KTimon::CambiarPosicion(const QPoint &posicion){
    if(!__posicion) __posicion = new QPointF(posicion);
    else *__posicion = posicion;}


void KTimon::CambiarPosicion(const QPointF &posicion){
    if(!__posicion) __posicion = new QPointF(posicion);
    else *__posicion = posicion;}


void KTimon::CambiarTam(const QSize &tam){
    if(tam.isNull()) return;
    if(!__tam) __tam = new QSize(tam);
    else *__tam = tam;}


void KTimon::CambiarTamBase(const QSize &tam){
    if(tam.isNull()) return;
    if(!__tamBase) __tamBase = new QSize(tam);
    else *__tamBase = tam;}


void KTimon::CambiarQMatrix(const QMatrix &matrix){
    if(!__qmatrix) __NuevoQMatrix();
    *__qmatrix = matrix;
    *__qmatrixRes = matrix;}


void KTimon::AdoptarQMatrix(QMatrix *&matrix){
    if(!matrix) return;
    if(__qmatrix && &(*__qmatrix) == &(*matrix)) return;
    __BorrarQMatrix();
    __qmatrix = matrix;
    *__qmatrixRes = *__qmatrix;}


void KTimon::ReIniciar(){
    __movX   = __movXAncla   = 0;
    __movY   = __movYAncla   = 0;
    __grados = __gradosAncla = 0;
    __zoom   = __zoomAncla   = 1;
    Actualizar();}


void KTimon::ReIniciarRotacion(){
    __grados = __gradosAncla = 0;   Actualizar();}

void KTimon::ReIniciarNevegacion(){
    __movX = __movXAncla = 0;
    __movY = __movYAncla = 0;   Actualizar();}

void KTimon::ReIniciarZoom(){
    __zoom = __zoomAncla = 1;   Actualizar();}



void KTimon::Actualizar(){
    if(!__qmatrix ||!__tamBase || !__tam || !__posicion ) return;

    QMatrix zoom(__zoom,0,0,__zoom,0,0);

    if(__grados){
        const double rad =  (M_PI/180) * __grados;
        const double seno = sin(rad);
        const double cose = cos(rad);
        QMatrix girar(cose,seno,-seno,cose,0,0);
        *__qmatrix = *__qmatrixRes * zoom * girar;}

    else
        *__qmatrix = *__qmatrixRes * zoom;

    QPointF medio = ReCentro(*__tam,*__tamBase, *__qmatrix);

    __qmatrix->translate(medio.x()+__movX + __posicion->x(),medio.y()+__movY + __posicion->y());}



void KTimon::Zoom(cDouble &zoom){
    if( __zoomAncla * zoom > .1 )
        __zoom = __zoomAncla * zoom;}


void KTimon::Rotar(cDouble &grados){
    if(!__qmatrix) return;
    if(grados <= 0 || grados >= 360)
        __grados = __gradosAncla;
    else
        __grados = adicion_angular(__gradosAncla,grados);}

void KTimon::MoverEnX(cDouble &moverEnX){ __movX = __movXAncla + moverEnX;}
void KTimon::MoverEnY(cDouble &moverEnY){ __movY = __movYAncla + moverEnY;}
void KTimon::Mover(cDouble &moverEnX,cDouble &moverEnY){
    MoverEnX(moverEnX); MoverEnY(moverEnY);}


void KTimon::Navegar(cDouble &moverEnX, cDouble &moverEnY, cDouble &zoom, cDouble &grados){
    MoverEnX(moverEnX);  Zoom(zoom);
    MoverEnY(moverEnY);  Rotar(grados);}


void KTimon::mousePressEvent(QMouseEvent *event, const bool &rotacionActiva){
    if(!event) return;
    if(!__puntoAncla) __puntoAncla = new QPoint(event->pos());
    else * __puntoAncla = event->pos();
    if(rotacionActiva && __tamBase)
        __angInicial = angulo_de_la_coordenada(QPoint(__tamBase->width()/2,__tamBase->height()/2),event->pos());}


void KTimon::mouseMoveEventZoom(QMouseEvent *event, cDouble &distanciaFocal){
    if(!event || !__puntoAncla || distanciaFocal <= 0) return;
    double zoom = (__puntoAncla->y() - event->pos().y()) * distanciaFocal;
    Zoom(exp(zoom));}


void KTimon::mouseMoveEventRotar(QMouseEvent *event){
    if(!__tamBase) return;
    double ang = angulo_de_la_coordenada(QPoint(__tamBase->width()/2,__tamBase->height()/2),event->pos());
    Rotar(diferencia_angular(__angInicial,ang));}


void KTimon::mouseMoveEventMover(QMouseEvent *event){
    if(!event || !__puntoAncla ) return;
    MoverEnX( - (__puntoAncla->x() - event->pos().x()));
    MoverEnY( - (__puntoAncla->y() - event->pos().y()));}


void KTimon::Anclar(){
     __movXAncla   = __movX;
     __movYAncla   = __movY;
     __zoomAncla   = __zoom;
     __gradosAncla = __grados;
     __angInicial = 0;}

void KTimon::__Inicializar(){
    __qmatrix = nullptr;
    __qmatrix_autogenerada = nullptr;
    __qmatrixRes = new QMatrix(1,0,0,1,0,0);
    __tam = nullptr;
    __tamBase = nullptr;
    __posicion = nullptr;
    __puntoAncla = nullptr;
    __movX = __movXAncla = 0;
    __movY = __movYAncla = 0;
    __zoom = __zoomAncla = 1;
    __grados = __gradosAncla = 0;}


void KTimon::__NuevoQMatrix(){
    if(!__qmatrix_autogenerada)
        __qmatrix_autogenerada = new QMatrix(1,0,0,1,0,0);
    __qmatrix = __qmatrix_autogenerada;}


void KTimon::__BorrarQMatrix(){
    if(__qmatrix_autogenerada){
        delete __qmatrix_autogenerada;
        __qmatrix_autogenerada = nullptr;}
    __qmatrix = nullptr;}


KTimon::~KTimon(){
    __BorrarQMatrix();
    delete __qmatrixRes;
    if(__posicion)     delete __posicion;
    if(__tam)          delete __tam;
    if(__tamBase)      delete __tamBase;
    if(__puntoAncla)   delete __puntoAncla;}
