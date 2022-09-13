#ifndef __KSonda
#define __KSonda
#include "__GITICONST__.h"
#include <QList>
#include "KMap.h"

union c_rgb;
class KSonda
{
public:
    KSonda(){__inicializar();}
    ~KSonda(){__borrarMapa();}

    KSonda(cuInt &Largo, cuInt &Alto);
    KSonda(const QSize &tam);
    KSonda(const QImage &imagen, cuInt &id_color, cuChar &umbral = 0);
    KSonda(const QImage &img, const QPoint &coordenada, cuChar &umbral = 0, bool limitar = false);

    void CambiarDimencion(cuInt &Largo, cuInt &Alto);
    void CambiarDimencion(const QSize &tam);

    void Explorar(const QImage &imagen, const QPoint &coordenada, cuChar &umbral = 0, bool Limitar = false);
    void Explorar(const QImage &imagen, cuInt &id_color, cuChar &umbral = 0);
    void Limpiar();

    QSize size(){return QSize(__largo,__alto);}

    inline cuShort &alto()const {return __alto;}
    inline cuShort &largo()const {return __largo;}

    inline const bool &esValido()const{return __es_valido;}

    KMap *Mapa(){return mapa;}



private:
    KMap *mapa;
    bool __es_valido;
    uShort __largo, __alto;


    void __inicializar();
    kbool** __generarMapa(cuInt &Largo, cuInt &Alto);
    void __borrar_matriz();
    void __borrarMapa();


    //-  ESCANEO ->
    c_rgb *max, *min;
    const QImage *img;
    QList<QPoint> *lista;

    void __explorar(const QImage *imagen, const QPoint &coordenada, cuChar &umbral = 0, bool Limitar = false);
    bool __escaneoLinal(QPoint p, const bool &limitar, const char &siguiente_espacio);
    void __hayarSiguienteCoordenada(cuInt &x, cuInt &y, bool &condicion);
    //<- ESCANEO FIN -


    //-  ITERADOR ->
    uInt * iter_x, *iter_y, *iter_contador;
    bool iter_init;
    void __iter_borrar();
    //<- ITERADOR FIN -
};

#endif // __KSonda
