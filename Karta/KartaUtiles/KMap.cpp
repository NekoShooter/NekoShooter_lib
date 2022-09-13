#include "KMap.h"

void KMap::__inicializar(){
    __map = nullptr;
    __numMarcas  = 0;
    __xPos = __w = 0;
    __yPos = __h = 0;

    iter_x = iter_y = iter_contador = nullptr;
    iter_iniciado = false;}


kbool **KMap:: __mapa(cuInt &largo, cuInt &alto){
    if(!largo || !alto) return nullptr;

    kbool ** m = new kbool *[largo];
    for(uInt x = 0; x < largo; ++x){
        m[x] = new kbool[alto];
        for(uInt y = 0; y < alto; ++y){
            m[x][y].on = false;}}
    return m;}


void KMap:: __borraMap(){
    if(__map){
        for(int x = 0; x < __w; ++x){
            delete[] __map[x];}
        delete[] __map;}
    __numMarcas  = 0;
    __xPos = __w = 0;
    __yPos = __h = 0;
    __x.limpiar();
    __y.limpiar();
    __map = nullptr;}

KMap::KMap(const QSize &tam){
    __inicializar();
    if(tam.isNull() || tam.isEmpty()) return;
    ReDimencionar(0,0,tam.width(),tam.height());}

KMap::KMap(const QRect &rect){
    __inicializar();
    if(rect.isNull() || rect.isEmpty()) return;
    ReDimencionar(rect.x(),rect.y(),rect.width(),rect.height());}

KMap::KMap(cShort &x, cShort &y, cuShort &w, cuShort &h){
    __inicializar();
    ReDimencionar(x,y,w,h);}

void KMap::ReDimencionar(cShort &x,cShort &y, cuShort &w, cuShort &h){
    if(!w || !h || (__xPos == x && __yPos == y && __w == w && __h == h)) return;

    if(!__numMarcas) __borraMap();

    if(!__map){
        __xPos = x; __yPos = y; __w = w; __h = h;
        __map = __mapa(w-x,h-y);}
/*
    else{
        kbool **map = __mapa(w,h);
        short marcas = __copiar(map,x,y,w,h);
        __borraMap();
        __xPos = x; __yPos = y; __w = w; __h = h;
        __numMarcas = marcas;
        __map = map;
    }*/
}

short KMap::__copiar(kbool ** nuevo, cShort &x, cShort &y, cuShort &w, cuShort &h){
    if(!__map || !nuevo) return 0;
    HRango<short> X, Y;
    X << x << __xPos;
    Y << y << __yPos;

    //pendiente
    return 0;}


void KMap::Unir(const KMap &map){
    if(map.esNulo()) return;}

KMap KMap::Union(const KMap &map){
    if(esNulo()&& !map.esNulo()) return map;
    else if (map.esNulo()) return *this;
    return *this;
    }

void KMap::Optimizar(){}
void KMap::Intersectar(const KMap &map){
    if(map.esNulo() || map.estaVacio()) return;
}

KMap KMap::Interseccion(const KMap &map){
    if(esNulo()&& !map.esNulo()) return map;
    else if (map.esNulo()) return *this;
    return *this;
}

void KMap::Marcar(const QPoint & coordenada){
    Marcar(coordenada.x(),coordenada.y());}

void KMap::Marcar(cShort &x, cShort &y){
    if(!__map || (x >= (__w + __xPos) || y >= (__h + __yPos))||((x - __xPos) < 0 || (y - __yPos) < 0)) return;
    if(!__map[x - __xPos][y - __yPos].on){
        __map[x - __xPos][y - __yPos].on = true;
        __x << x - __xPos;
        __y << y - __yPos;
        ++__numMarcas;}}

void KMap::DesMarcar(const QPoint &p){
    DesMarcar(p.x(),p.y());}

void KMap::DesMarcar(cShort &x, cShort &y){
    if(!__map || (x >= (__w + __xPos) || y >= (__h + __yPos))||((x - __xPos) < 0 || (y - __yPos) < 0)) return;
    if(__map[x - __xPos][y - __yPos].on){
        __map[x - __xPos][y - __yPos].on = false;
        --__numMarcas;}}


bool KMap::Marcado(const QPoint & coordenada){
    return Marcado(coordenada.x(), coordenada.y());}

bool KMap::Marcado(cShort &x, cShort &y){
    if(!__map || (x >= (__w + __xPos) || y >= (__h + __yPos))||((x - __xPos) < 0 || (y - __yPos) < 0)) return false;
    return __map[x - __xPos][y - __yPos].on;}

uShort KMap::begin(){
    if(__map && !estaVacio()){
        iter_iniciado = true;
        if(!iter_x) iter_x = new int;
        if(!iter_y) iter_y = new int;
        if(!iter_contador) iter_contador = new int;

        *iter_x = __x.min();
        *iter_y = __y.min();
        *iter_contador = __numMarcas;}
    return 0;}


QPoint KMap::iterator(){
    assert(iter_iniciado);
    QPoint p;

    while(*iter_x <= __x.max()){

        if(*iter_y > __y.max()){
            ++*iter_x;
            *iter_y = __y.min();}

        if(__map[*iter_x][*iter_y].on){
            p.ry() = *iter_y + __yPos;
            p.rx() = *iter_x + __xPos;
            ++*iter_y;
            --*iter_contador;
            if(!*iter_contador)
                __iter_borrado();
            break;}

        ++*iter_y;}

    return p;}


void KMap::__iter_borrado(){
    iter_iniciado = false;

    if(iter_x) delete iter_x;
    if(iter_y) delete iter_y;
    if(iter_contador) delete iter_contador;

    iter_x = nullptr;
    iter_y = nullptr;
    iter_contador = nullptr;}

void KMap::Limpiar(){
    __borraMap();
    __iter_borrado();}
