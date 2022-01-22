#include "KSonda.h"
#include "Colori__rgb__.h"
#include "ColoriMath.h"

#include <QImage>



void KSonda::__inicializar(){
    __es_valido = false;
    __num_marcas = __alto = __largo = 0;
    __XSup = __XInf = __YSup = __YInf  = 0;}


KSonda::KSonda(cuInt &Largo, cuInt &Alto){
    __inicializar();
    CambiarDimencion(Largo,Alto);}


KSonda::KSonda(const QSize &tam){
    __inicializar();
    if(!tam.isEmpty())
        CambiarDimencion(tam.width(),tam.height());}


KSonda::KSonda(const QImage &img, const QPoint &coordenada, cuChar &umbral){
    __inicializar();
    if(img.isNull())
        Explorar(img,coordenada,umbral);}


void KSonda::CambiarDimencion(const QSize &tam){
    if(!tam.isEmpty())
        CambiarDimencion(tam.width(),tam.height());}



bool** KSonda:: __generarMapa(cuInt &Largo, cuInt &Alto){
    bool ** mapa = new bool *[Largo];

    for(uInt x = 0; x < Largo; ++x){
        mapa[x] = new bool[Alto];

        for(uInt y = 0; y < Alto; ++y)
            mapa[x][y] = false;}
    return mapa;}


void KSonda::CambiarDimencion(cuInt &Largo, cuInt &Alto){

    if(Largo && Alto){
        if(esNull())
            __map = __generarMapa(Largo,Alto);
        if(not estaVacio()){

        }

        __largo = Largo;
        __alto = Alto;
    }}






void KSonda::Limpiar(){
    if(estaVacio()) return;
}

void KSonda::Borrar(){
    if(!__map) return;
    for(uInt x = 0; x < __largo; ++x)
        delete [] __map[x];
    delete [] __map;
    __map = nullptr;
    __inicializar();}


void KSonda::Marcar(const QPoint &coordenada){
    Marcar(coordenada.x(),coordenada.y());}

void KSonda::Marcar(cuInt &x, cuInt &y){
    if(x > __largo || y > __alto) return;
    if(__map) {
        __map[x][y] = true;
        ++__num_marcas;}}



void KSonda::Desmarcar(const QPoint &coordenada){
    Desmarcar(coordenada.x(),coordenada.y());}

void KSonda::Desmarcar(cuInt &x, cuInt &y){
    if(x > __largo || y > __alto) return;
    if(__map) {
        __map[x][y] = false;
        if(__num_marcas) --__num_marcas;}}



bool KSonda::EstaMarcado(const QPoint &coordenada)const{
    return EstaMarcado(coordenada.x(),coordenada.y());}

bool KSonda::EstaMarcado(cuInt &x, cuInt &y) const{
    if(!__map || !__num_marcas) return false;
    if(x > __largo || y > __alto) return false;
    return __map[x][y];}




void KSonda::Reiniciar(cuInt &Largo, cuInt &Alto){
    if(__map) Borrar();
    CambiarDimencion(Largo,Alto);}

void KSonda::Reiniciar(const QSize &tam){
    if(tam.isEmpty()) return;
    Reiniciar(tam.width(),tam.height());}

void KSonda::Reiniciar(const QImage &img, const QPoint &coordenada, cuChar &umbral){
    if(img.isNull()) return;
    Reiniciar(img.size().width(),img.size().height());
    Explorar(img,coordenada,umbral);}




void KSonda::Explorar(const QImage &imagen, const QPoint &coordenada, cuChar &umbral){
    if(imagen.isNull()) return;

    if(__map) {
        if(size() == imagen.size()) Limpiar();
        else Reiniciar(imagen.size());}

    else CambiarDimencion(imagen.size());

    img = &imagen;
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
        ok1 = __escaneoLinal(p);
        ok2 = __escaneoLinal(p,true);

        if(!ok1 || !ok2) break;};

    __es_valido = ok1 && ok2;

    delete max;
    delete min;
    delete lista;}



bool KSonda::__escaneoLinal(QPoint p, bool mod_inverso){
    char siguiente_espacio =  1;            //derecha
    if(mod_inverso) siguiente_espacio = -1; //izquierda

    bool agregar_sup = true,
         agregar_inf = true;

    Marcar(p);

    while(true){
        __hayarSiguienteCoordenada(p.x(),p.y() - 1,agregar_sup); //arriba
        __hayarSiguienteCoordenada(p.x(),p.y() + 1,agregar_inf); //abajo

        p.rx() = p.rx() + siguiente_espacio;

        if(p.rx() < 0 || p.rx() > img->width()) return false;

        if(img->pixelColor(p).rgba() >= min->id_a && img->pixelColor(p).rgba() <= max->id_a)
            Marcar(p);
        else return true;}}


void KSonda::__hayarSiguienteCoordenada(cuInt &x, cuInt &y,bool &condicion){
    if(img->pixelColor(x,y).rgba() >= min->id_a && img->pixelColor(x,y).rgba() <= max->id_a){
        if(!__map[x][y] && condicion)
            if(!lista->contains(QPoint(x,y)))
                lista->append(QPoint(x,y));
        condicion = false;}

    else condicion = true;
}


