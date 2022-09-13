#ifndef HPTR_H
#define HPTR_H

#include "HNotificador.h"

template <typename T> class HPtr{
    public:
        HPtr(){ __inicializar();}
        ~HPtr(){__eliminar();}

        HPtr(const HPtr &copia);
        HPtr(T *punteroMaestro);
        HPtr(const T& tipo);

        T* crearPtr(T* punteroMaestro = nullptr);
        T* crearPtr(const T& tipo);

        void especificarConstruccion(T *punteroConstruido);
        inline void reAsignarse(){ptr = __almacen;}

        void destruirRespaldo();
        void crearRespaldo();
        void restaurar();

        void CARGAR();

        void copiar(const HPtr &htpr);

        enum HPtrElemento{Principal = 0X1, Nucleo = 0x2, Especificacion = 0x4, Respaldo = 0x8,
                         Todos = Principal|Nucleo|Especificacion|Respaldo};

        void absorverHPtr( HPtr & hptr, const HPtrElemento &p = Todos);
        void intercambiar(HPtr &hptr, const HPtrElemento &p = Todos);
        void intercambiar(const HPtrElemento &A, const HPtrElemento &B);
        const T* damePtrConst(const HPtrElemento &p = Principal) const{ return damePtr(p);}
        T* damePtr(const HPtrElemento &p = Principal);

        void limpiar();
        void destruir(){__eliminar(); __inicializar();}

        HPtr &operator =(const HPtr &hptr);
        T* operator =( T *punteroMaestro){ return crearPtr(punteroMaestro);}
        const T& operator =(const T& tipo){return crearPtr(tipo) ? *ptr : T();}
        void operator <<(HPtr &hptr){absorverHPtr(hptr);}
        void operator ^ (HPtr &hptr){intercambiar(hptr);}

        inline bool esIndependiente() const {return !__almacen;}
        inline bool esValido() const{ return ptr;}
        inline bool esNulo() const {return !ptr && !__almacen;}
        inline bool estaVacio() const{return esNulo() && !__ptrDemo && !__respaldo;}

        HNotificador &Notificador(){return __cambioHecho;}
        HNotificador *pNotificador(){return &__cambioHecho;}
        const bool &CambioRealizado(){return __cambioHecho.estado();}

        T* ptr;
    private:
        T* __almacen;
        T* __ptrDemo;
        T* __respaldo;
        HNotificador __cambioHecho;
        void __inicializar();
        void __eliminar();};

template <class T>HPtr<T>::HPtr(T *punteroMaestro){
    __inicializar();
    crearPtr(punteroMaestro);}

template <class T>HPtr<T>::HPtr(const T& tipo){
    __inicializar();
    crearPtr(tipo);}

template <class T> HPtr<T>::HPtr(const HPtr &copia){
    __inicializar();
    copiar(copia);}

template <class T> void HPtr<T>::CARGAR(){
    if(!ptr && __almacen) reAsignarse();
    else if(esNulo()) crearPtr();}


template <class T> void HPtr<T>::__inicializar(){
    __cambioHecho = false;
    __respaldo = __ptrDemo = ptr = __almacen = nullptr;}


template <class T> void HPtr<T>::__eliminar(){
    if(__almacen) delete __almacen;
    if(__ptrDemo) delete __ptrDemo;
    if(__respaldo) delete __respaldo;}


template <class T> void HPtr<T>::limpiar(){
    if(__almacen) delete __almacen;
    ptr = __almacen = nullptr;
    __cambioHecho = true;}


template <class T> void HPtr<T>::especificarConstruccion(T *punteroConstruido){
    if(punteroConstruido == nullptr || (__almacen && (&(*__almacen) == &(*punteroConstruido)))) return;
    if(__ptrDemo) {
        if(&(*punteroConstruido) == &(*__ptrDemo)) return;
        delete __ptrDemo;}
    __ptrDemo = punteroConstruido;}


template <class T> T* HPtr<T>::crearPtr(T *punteroMaestro){
    if(punteroMaestro){
        if(__almacen && &(*__almacen) == &(*punteroMaestro)) return punteroMaestro;
        limpiar();
        ptr = punteroMaestro;}
    else if(!__almacen){
        ptr = __almacen = __ptrDemo ? new T(*__ptrDemo): new T;
        __cambioHecho = true; }

    return ptr;}


template <class T> T* HPtr<T>::crearPtr(const T& tipo){
    crearPtr();
    if(!ptr) reAsignarse();
    *__almacen = tipo;
    __cambioHecho = true;
    return ptr;}

template <class T> void HPtr<T>::crearRespaldo(){
    T* p = __almacen ? __almacen : ptr;
    if(!p) return;
    if(!__respaldo) __respaldo = new T(*p);
    else *__respaldo = *p;}


template <class T> void HPtr<T>::restaurar(){
    if(!__respaldo) return;
    if(__almacen) {
        *__almacen = *__respaldo;
        ptr = __almacen;}
    else if(ptr) *ptr = *__respaldo;
    else ptr = __almacen = new T(*__respaldo);
    __cambioHecho = true;}


template <class T> void HPtr<T>::destruirRespaldo(){
    if(__respaldo) delete __respaldo;
    __respaldo = nullptr;}


template <class T> HPtr<T>& HPtr<T>::operator =(const HPtr<T> &hptr){
    copiar(hptr);
    return *this;}


template <class T> void HPtr<T>::copiar(const HPtr & hptr){
    if(&*this == &hptr) return;
    limpiar();
    if(not hptr.esIndependiente()) {
        __almacen = new T;
       *__almacen = *hptr.__almacen;
        ptr = __almacen;}
    else { ptr = hptr.ptr;}
    __cambioHecho = true;}


template <class T> void HPtr<T>::absorverHPtr(HPtr &hptr, const HPtrElemento &p){
    if(p <= 0 || p > Todos ) return;

    if(p & Principal){
        ptr = hptr.ptr;
        hptr.ptr = nullptr;}
    if(p & Nucleo){
        if(__almacen) delete __almacen;
        __almacen = hptr.__almacen;
        hptr.__almacen = nullptr;}
    if(p & Especificacion){
        if(__ptrDemo) delete __ptrDemo;
        __ptrDemo = hptr.__ptrDemo;
        hptr.__ptrDemo = nullptr;}
    if(p & Respaldo){
        if(__respaldo) delete __respaldo;
        __respaldo = hptr.__respaldo;
        hptr.__respaldo = nullptr;}
    __cambioHecho = true;}


template <class T> void HPtr<T>::intercambiar(HPtr &hptr, const HPtrElemento &p){
    if(p <= 0 || p > Todos ) return;

    if(p & Principal){
        T* tptr = ptr;
        ptr = hptr.ptr;
        hptr.ptr = tptr;}

    if(p & Nucleo){
         T* talmacen = __almacen;
         __almacen = hptr.__almacen;
         hptr.__almacen = talmacen;}

    if(p & Especificacion){
        T* tptrDemo = __ptrDemo;
        __ptrDemo = hptr.__ptrDemo;
        hptr.__ptrDemo = tptrDemo; }

    if(p & Respaldo){
        T* trespaldo = __respaldo;
        __respaldo = hptr.__respaldo;
        hptr.__respaldo = trespaldo;}

    __cambioHecho= true;}


template <class T> T* HPtr<T>::damePtr(const HPtrElemento &p){
    switch (p) {
        case Principal: return ptr;
        case Nucleo: return __almacen;
        case Respaldo: return __respaldo;
        case Especificacion: return __ptrDemo;
        default: return nullptr;}}


#endif // HPTR_H
