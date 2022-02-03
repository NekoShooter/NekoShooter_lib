#include "KSonda.h"
#include "Colori__rgb__.h"
#include "ColoriMath.h"
#include <assert.h>
#include <QDebug>

#include <QImage>


/*************************** Inicio ********************************/


void KSonda::__inicializar(){
    iter_init = __es_valido = false;
    __num_marcas = __alto = __largo = 0;
    __XSup = __XInf = __YSup = __YInf  = 0;
    iter_x = nullptr; iter_y = nullptr; iter_contador = nullptr;}


KSonda::KSonda(cuInt &Largo, cuInt &Alto){
    __inicializar();
    CambiarDimencion(Largo,Alto);}


KSonda::KSonda(const QSize &tam){
    __inicializar();
    if(!tam.isEmpty())
        CambiarDimencion(tam.width(),tam.height());}


KSonda::KSonda(const QImage &img, const QPoint &coordenada, cuChar &umbral,bool limitar){
    __inicializar();
    if(!img.isNull())
        Explorar(img,coordenada,umbral,limitar);}


void KSonda::CambiarDimencion(const QSize &tam){
    if(!tam.isEmpty())
        CambiarDimencion(tam.width(),tam.height());}



kbool** KSonda:: __generarMapa(cuInt &Largo, cuInt &Alto){
    kbool ** mapa = new kbool *[Largo];

    for(uInt x = 0; x < Largo; ++x){
        mapa[x] = new kbool[Alto];

        for(uInt y = 0; y < Alto; ++y)
            mapa[x][y].on = false;}
    return mapa;}

/*************************** Cambio ********************************/


void KSonda::CambiarDimencion(cuInt &Largo, cuInt &Alto){

    if(!Largo || !Alto) return;

    if(esNull()){
        __map = __generarMapa(Largo,Alto);
        __XInf = __largo = Largo;
        __YInf = __alto = Alto;}

    else if(!estaVacio()){

        kbool ** nuevoMapa = __generarMapa(Largo,Alto);
        __XInf = Largo;
        __YInf = Alto;
        __num_marcas = __XSup = __YSup = 0;
        for(uInt x = 0; x < Largo; ++x){
            for(uInt y = 0; y < Alto; ++y){
                if(EstaMarcado(x,y)){
                    nuevoMapa[x][y].on = true;
                    ++__num_marcas;
                    if(x < __XInf) __XInf = x;
                    if(y < __YInf) __YInf = y;
                    if(x > __XSup) __XSup = x;
                    if(y > __YSup) __YSup = y; }}}
        __alto = Alto;
        __largo = Largo;
        __borrar_matriz();
        __map = nuevoMapa;}}




/*************************** Limpiado y borrado ********************************/



void KSonda::Limpiar(){
    if(estaVacio()) return;
    __iter_borrar();
    if(__num_marcas) {
        for(uInt x = xBegin(); x < xEnd(); ++x){
            for(uInt y = yBegin(); y < yEnd(); ++y)
                __map[x][y].on = false;}}
    __inicializar();}

void KSonda::Borrar(){
    if(!__map) return;
    __borrar_matriz();
    __iter_borrar();
    __inicializar();}

void KSonda::__borrar_matriz(){
    for(uInt x = 0; x < __largo; ++x)
        delete [] __map[x];
    delete [] __map;
    __map = nullptr;}



/*************************** Marcado y agregado ********************************/



void KSonda::Marcar(const QPoint &coordenada){
    Marcar(coordenada.x(),coordenada.y());}

void KSonda::Marcar(cuInt &x, cuInt &y){
    if(x >= __largo || y >= __alto) return;
    if(__map && !__map[x][y].on) Marcar_v(x,y);}

void KSonda::Marcar_v(cuInt &x, cuInt &y){
    __map[x][y].on = true;
    ++__num_marcas;
    if(x < __XInf) __XInf = x;
    if(y < __YInf) __YInf = y;
    if(x > __XSup) __XSup = x;
    if(y > __YSup) __YSup = y;}



void KSonda::Desmarcar(const QPoint &coordenada){
    Desmarcar(coordenada.x(),coordenada.y());}

void KSonda::Desmarcar(cuInt &x, cuInt &y){
    if(x > __largo || y > __alto) return;
    if(__map && __map[x][y].on) {
        __map[x][y].on = false;
        --__num_marcas;}}



bool KSonda::EstaMarcado(const QPoint &coordenada)const{
    return EstaMarcado(coordenada.x(),coordenada.y());}

bool KSonda::EstaMarcado(cuInt &x, cuInt &y) const{
    if(!__map || !__num_marcas || !__es_valido) return false;
    if(x > __largo || y > __alto) return false;
    return __map[x][y].on;}



/*************************** Reasignacion ********************************/

void KSonda::Reiniciar(cuInt &Largo, cuInt &Alto){
    if(__map){
        if(size() == QSize(Largo,Alto)) Limpiar();
        else { Borrar();
               CambiarDimencion(Largo,Alto);} }

    else CambiarDimencion(Largo,Alto);}

void KSonda::Reiniciar(const QSize &tam){
    if(tam.isEmpty()) return;
    Reiniciar(tam.width(),tam.height());}

void KSonda::Reiniciar(const QImage &img, const QPoint &coordenada, cuChar &umbral, bool limitar){
    if(img.isNull()) return;
    Reiniciar(img.size().width(),img.size().height());
    Explorar(img,coordenada,umbral,limitar);}


/*************************** Mapeado ********************************/



void KSonda::Explorar(const QImage &img){
    if(img.isNull()) return;
    // -- PENDIENTE --
    // retornara una lista de los colores principales
}




// Mapeado por color;
void KSonda::Explorar(const QImage &img, cuInt &id_color, cuChar &umbral, bool alfa ){
    if(img.isNull()) return;

    Reiniciar(img.size());

    for(int x = 0; x < __largo; ++x){
        for(int y = 0; y < __alto; ++y){
            if(!__map[x][y].on && id_color == img.pixel(x,y)){
                __explorar(&img,QPoint(x,y),umbral);}}}}



// Mapeador por coordenada --metodo lineal
void KSonda::Explorar(const QImage &imagen, const QPoint &coordenada, cuChar &umbral, bool Limitar){
    if(imagen.isNull()) return;
    if(coordenada.x() > imagen.width() || coordenada.y() > imagen.height()) return;
    if(coordenada.x() < 0 || coordenada.y() < 0) return;

    Reiniciar(imagen.size());

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
        ok1 = __escaneoLinal(p,Limitar);
        ok2 = __escaneoLinal(p,Limitar,true);

        if(!ok1 || !ok2) break;};

    __es_valido = ok1 && ok2;

    delete max;
    delete min;
    delete lista;}



//escaneo lineal
bool KSonda::__escaneoLinal(QPoint p,const bool& limitar, bool mod_inverso){
    char siguiente_espacio =  1;            //derecha
    if(mod_inverso) siguiente_espacio = -1; //izquierda
    else Marcar(p.rx(),p.ry());

    bool agregar_sup = true,
         agregar_inf = true;

    while(p.rx() >= 0 && p.rx() < img->width()){
        __hayarSiguienteCoordenada(p.x(),p.y() - 1,agregar_sup); //arriba
        __hayarSiguienteCoordenada(p.x(),p.y() + 1,agregar_inf); //abajo

        p.rx() = p.rx() + siguiente_espacio;

        Marcar(p.rx(),p.ry());

        if(img->pixelColor(p).rgba() < min->id_a || img->pixelColor(p).rgba() > max->id_a)
            return true;}

    return !limitar;}



void KSonda::__hayarSiguienteCoordenada(cuInt &x, cuInt &y,bool &condicion){

    if(img->pixelColor(x,y).rgba() >= min->id_a && img->pixelColor(x,y).rgba() <= max->id_a){
        if(!__map[x][y].on && condicion){
                lista->append(QPoint(x,y));}
        condicion = false;}

    else {
        Marcar(x,y);
        condicion = true;}}



/*************************** Iterador ********************************/


//Funciona pero es demasiado lento para implentar:
//en busqueda de un mejor codigo

QPoint KSonda::iterator(){
    assert(iter_init);
    QPoint p;
    while(*iter_x <= __XSup){

        if(*iter_y > __YSup){
            ++*iter_x;
            *iter_y = __YInf;}

        if(__map[*iter_x][*iter_y].on){
            p.ry() = *iter_y;
            p.rx() = *iter_x;
            ++*iter_y;
            --*iter_contador;
            if(!*iter_contador)
                __iter_borrar();
            return p;}

        ++*iter_y;}
    return  p;}


uShort KSonda::begin(){
    if(__map && __es_valido){
        iter_init = true;
        if(!iter_x) iter_x = new uint;
        if(!iter_y) iter_y = new uint;
        if(!iter_contador) iter_contador = new uint;

        *iter_x = __XInf;
        *iter_y = __YInf;
        *iter_contador = __num_marcas;}
    return 0;}


void KSonda::__iter_borrar(){
    iter_init = false;

    if(iter_x) delete iter_x;
    if(iter_y) delete iter_y;
    if(iter_contador) delete iter_contador;

    iter_x = nullptr;
    iter_y = nullptr;
    iter_contador = nullptr;}
