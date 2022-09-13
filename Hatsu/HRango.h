#ifndef HRANGO_H
#define HRANGO_H
#include <assert.h>

template <typename T> class HRango
{
public:
    HRango();
    HRango(const T & minimo, const  T& maximo);
    ~HRango();

    void Agregar(const T& parametro);
    void CambiarParametros(const T& minimo, const T& maximo);
    void ReAjustar();

    bool estaInvertido() const;
    void invertir();
    void limpiar();

    bool operator == (const HRango<T> &rango);
    bool operator != (const HRango<T> &rango);
    HRango<T> operator + (const HRango<T> & rango);
    HRango<T> operator - (const HRango<T> & rango);
    HRango<T> operator * (const HRango<T> & rango);

    HRango<T>& operator = (const HRango<T> & rango);
    HRango<T>& operator = (const T &tipo);
    HRango<T>& operator << (const HRango<T> & rango);
    HRango<T>& operator << (const T& parametro);

    bool esSimetrico() const{ return esNulo() ? false : *__a == *__b;}
    inline bool estaVacio() const{return esNulo() || *__a == *__b;}
    inline bool esNulo() const{return !__a || !__b;}

    const T &max() const;
    T &rmax();

    const T &min() const;
    T &rmin();

private:
    T *__max, *__a;
    T *__min, *__b;

    void __crearMax(const T& max);
    void __crearMin(const T& min);
};

/* --------------------------------------------------------------------- */


template <class T> HRango<T>::HRango(){
    __max = __a = nullptr;
    __min = __b = nullptr;}

template <class T> void HRango<T>::__crearMax(const T& max){
    __a = new T(max);  __max = __a;}

template <class T> void HRango<T>::__crearMin(const T& min){
    __b = new T(min);  __min = __b;}

template <class T> const T &HRango<T>::max()const{
    assert(!esNulo());
    return *__max;}

template <class T> const T &HRango<T>::min()const{
    assert(!esNulo());
    return *__min;}

template <class T> T &HRango<T>::rmax(){
    assert(!esNulo());
    return *__max;}

template <class T> T &HRango<T>::rmin(){
    assert(!esNulo());
    return *__min;}

template <class T> void HRango<T>::limpiar(){
    if(__a) delete __a;
    if(__b) delete __b;
    __max = __a = nullptr;
    __min = __b = nullptr;}

template <class T> HRango<T>::~HRango(){
    if(__a) delete __a;
    if(__b) delete __b;}

template <class T> HRango<T>::HRango(const T& minimo, const T &maximo){
    CambiarParametros(minimo,maximo);}


template <class T> void HRango<T>::Agregar(const T& parametro){
    if(esNulo()) CambiarParametros(parametro,parametro);
    else {
        if(*__max < parametro) *__max = parametro;
        if(*__min > parametro) *__min = parametro;}}


template <class T> void HRango<T>::CambiarParametros(const T& minimo, const T& maximo){
    if(!__a)__crearMax(maximo);
    else *__max = maximo;

    if(!__b)__crearMin(minimo);
    else *__min = minimo;}

template <class T> bool HRango<T>::estaInvertido() const{
    if(estaVacio()) return false;
    return *__max < *__min;}

template <class T>void HRango<T>::ReAjustar(){
    if(estaVacio()) return;
    if (estaInvertido()){
        __min = __b < __a ? __b : __a;
        __max = __a > __b ? __a : __b;}}

template <class T>void HRango<T>::invertir(){
    if(estaVacio()) return;
    if(estaInvertido()) ReAjustar();
    else{
        __min = __a > __b ? __a : __b;
        __max = __b < __a ? __b : __a;}}

template <class T>bool HRango<T>::operator == (const HRango<T> &rango){
    if(estaVacio() && rango.estaVacio()) return true;
    if(estaVacio() || rango.estaVacio()) return false;
    return *__max == rango.max() && *__min == rango.min();}

template <class T>bool HRango<T>::operator != (const HRango<T> &rango){
    return !(*this == rango);}

template <class T> HRango<T> HRango<T>::operator + (const HRango<T> & rango){
    if(this->estaVacio() && !rango.estaVacio()) return rango;
    if(!this->estaVacio() && rango.estaVacio()) return *this;
    T MAX = rango.max() > *__max ? rango.max() : *__max;
    T MIN = rango.min() > *__min ? rango.min() : *__min;
    HRango<T> resulado;
    resulado << MAX << MIN;
    return resulado;}

template <class T> HRango<T> HRango<T>::operator - (const HRango<T> & rango){
    if(this->estaVacio() && !rango.estaVacio()) return rango;
    if(!this->estaVacio() && rango.estaVacio()) return *this;
    T MAX = rango.max() < *__max ? rango.max() : *__max;
    T MIN = rango.min() < *__min ? rango.min() : *__min;
    HRango<T> resulado;
    resulado << MAX << MIN;
    return resulado;}

template <class T> HRango<T> HRango<T>::operator * (const HRango<T> & rango){
    if(this->estaVacio() && !rango.estaVacio()) return rango;
    if(!this->estaVacio() && rango.estaVacio()) return *this;
    HRango<T> resulado = *this;
    resulado << rango;
    return resulado;}

template <class T> HRango<T>& HRango<T>::operator = (const HRango<T> & rango){
    if(rango.estaVacio()) return *this;
    CambiarParametros(rango.min(),rango.max());
    return *this;}

template <class T> HRango<T>& HRango<T>::operator = (const T& tipo){
    CambiarParametros(tipo,tipo);
    return *this;}

template <class T>HRango<T> &HRango<T>::operator <<(const HRango<T> & rango){
    if(!rango.estaVacio() && *this != rango){
        Agregar(rango.max());
        Agregar(rango.min());}
    return *this;}

template <class T>HRango<T> &HRango<T>::operator << (const T& parametro){
    Agregar(parametro);
    return *this;}

#endif // HRANGO_H
