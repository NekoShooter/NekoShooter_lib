#include "KSonda.h"
#include "Colori__rgb__.h"
#include "ColoriMath.h"
#include <assert.h>
#include <QDebug>

#include <QImage>


void KSonda::__inicializar(){
    __es_valido = false;
    __alto = __largo = 0;
    mapa = nullptr;}


KSonda::KSonda(cuInt &Largo, cuInt &Alto){
    __inicializar();
    CambiarDimencion(Largo,Alto);}


KSonda::KSonda(const QSize &tam){
    __inicializar();
    if(!tam.isEmpty())
        CambiarDimencion(tam.width(),tam.height());}

KSonda::KSonda(const QImage &imagen, cuInt &id_color, cuChar &umbral){
    __inicializar();
    if(!imagen.isNull()) Explorar(imagen,id_color,umbral);}


KSonda::KSonda(const QImage &img, const QPoint &coordenada, cuChar &umbral,bool limitar){
    __inicializar();
    if(!img.isNull()){
        //CambiarDimencion(img.width(),img.height());
        Explorar(img,coordenada,umbral,limitar);}
}

/*************************** generar un nuevo KMap ********************************/

kbool** KSonda:: __generarMapa(cuInt &Largo, cuInt &Alto){
    kbool ** mapa = new kbool *[Largo];

    for(uInt x = 0; x < Largo; ++x){
        mapa[x] = new kbool[Alto];

        for(uInt y = 0; y < Alto; ++y)
            mapa[x][y].on = false;}
    return mapa;}


/*************************** Limpiado y borrado ********************************/


void KSonda::Limpiar(){
    __borrarMapa();
    __inicializar();}

void KSonda::__borrarMapa(){
    if(mapa) delete mapa;
    mapa = nullptr;}

/*************************** Reasignacion ********************************/

void KSonda::CambiarDimencion(cuInt &Largo, cuInt &Alto){
    if(!Largo || !Alto ) return;
    Limpiar();
    mapa = new KMap(0,0,Largo,Alto);
    __alto = Alto;
    __largo = Largo;}


void KSonda::CambiarDimencion(const QSize &tam){
    if(tam.isEmpty()) return;
    CambiarDimencion(tam.width(),tam.height());}


/*************************** Mapeado ********************************/


// Mapeado por color;
void KSonda::Explorar(const QImage &img, cuInt &id_color, cuChar &umbral){
    if(img.isNull()) return;

    CambiarDimencion(img.size());

    c_rgb c_max = {id_color};
    c_rgb c_min = {id_color};
    autoIncrementarLuminicencia(&c_max, umbral);
    autoIncrementarLuminicencia(&c_min, -umbral);

    for(int x = 0; x < __largo; ++x){
        for(int y = 0; y < __alto; ++y){
            if(img.pixelColor(x,y).rgba() >= c_min.id_a && img.pixelColor(x,y).rgba() <= c_max.id_a){
                mapa->Marcar(x,y);}}}
    __es_valido = !mapa->estaVacio();}



// Mapeador por coordenada --metodo lineal
void KSonda::Explorar(const QImage &imagen, const QPoint &coordenada, cuChar &umbral, bool Limitar){
    if(imagen.isNull()) return;
    if(coordenada.x() > imagen.width() || coordenada.y() > imagen.height()) return;
    if(coordenada.x() < 0 || coordenada.y() < 0) return;

    CambiarDimencion(imagen.size());

    __explorar(&imagen,coordenada,umbral,Limitar);}



// algoritmo lineal
void KSonda::__explorar(const QImage *imagen, const QPoint &coordenada, cuChar &umbral, bool Limitar){

    img = imagen;
    max = new c_rgb{img->pixelColor(coordenada).rgba()};
    min = new c_rgb{max->id_a};
    autoIncrementarLuminicencia(max,umbral);
    autoIncrementarLuminicencia(min,-umbral);

    lista = new QList<QPoint>;
    lista->append(coordenada);

    bool ok1, ok2;

    while(!lista->isEmpty()){
        const QPoint p = lista->back();
                         lista->pop_back();
        ok1 = __escaneoLinal(p,Limitar, 1);
        ok2 = __escaneoLinal(p,Limitar,-1);

        if(!ok1 || !ok2) break;};

    __es_valido = ok1 && ok2;

    delete max;
    delete min;
    delete lista;}



//escaneo lineal
bool KSonda::__escaneoLinal(QPoint p,const bool& limitar, const char &siguiente_espacio){
    mapa->Marcar(p.rx(),p.ry());

    bool agregar_sup = true,
         agregar_inf = true;

    while(p.rx() >= 0 && p.rx() < img->width()){
        __hayarSiguienteCoordenada(p.x(),p.y() - 1,agregar_sup); //arriba
        __hayarSiguienteCoordenada(p.x(),p.y() + 1,agregar_inf); //abajo

        p.rx() = p.rx() + siguiente_espacio;

        mapa->Marcar(p.rx(),p.ry());

        if(img->pixelColor(p).rgba() < min->id_a || img->pixelColor(p).rgba() > max->id_a)
            return true;}

    return !limitar;}



void KSonda::__hayarSiguienteCoordenada(cuInt &x, cuInt &y,bool &condicion){

    if(img->pixelColor(x,y).rgba() >= min->id_a && img->pixelColor(x,y).rgba() <= max->id_a){
        if(!mapa->Marcado(x,y) && condicion){
                lista->append(QPoint(x,y));}
        condicion = false;}

    else {
        mapa->Marcar(x,y);
        condicion = true;}}
