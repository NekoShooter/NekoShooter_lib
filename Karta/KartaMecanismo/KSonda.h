#ifndef KSONDA_H
#define KSONDA_H
#include "__GITICONST__.h"
#include <QList>

/*
class QSize;
class QPoint;
class QImage;
*/
union c_rgb;

class KSonda
{
public:
    KSonda(){__inicializar();}
    ~KSonda(){Borrar();}

    KSonda(cuInt &Largo, cuInt &Alto);
    KSonda(const QSize &tam);
    KSonda(const QImage &img, const QPoint &coordenada, cuChar &umbral = 0);

    void CambiarDimencion(cuInt &Largo, cuInt &Alto);
    void CambiarDimencion(const QSize &tam);

    void Reiniciar(cuInt &Largo, cuInt &Alto);
    void Reiniciar(const QSize &tam);
    void Reiniciar(const QImage &img, const QPoint &coordenada, cuChar &umbral = 0);

    void Marcar(cuInt &x, cuInt &y);
    void Marcar(const QPoint &coordenada);

    void Desmarcar(cuInt &x, cuInt &y);
    void Desmarcar(const QPoint &coordenada);

    bool EstaMarcado(cuInt &x, cuInt &y) const;
    bool EstaMarcado(const QPoint &coordenada)const;


    void Explorar(const QImage &img, const QPoint &coordenada, cuChar &umbral = 0);
    void Limpiar();
    void Borrar();
    QSize size(){return QSize(__largo,__alto);}


    inline bool **rSonda(){ return __map;}

    inline cuShort &alto()const {return __alto;}
    inline cuShort &largo()const {return __largo;}

    inline bool esNull()const {return !__map;}
    inline bool estaVacio()const{return !__num_marcas;}
    inline bool esValido()const{return __es_valido;}



private:
    bool ** __map = nullptr;
    bool __es_valido;
    uShort __largo, __alto;
    uInt __num_marcas;
    uShort __XSup, __XInf, __YSup, __YInf;


    void __inicializar();
    bool** __generarMapa(cuInt &Largo, cuInt &Alto);


    //-->
    c_rgb *max, *min;
    const QImage *img;
    QList<QPoint> *lista;

    bool __escaneoLinal(bool mod_inverso = false);
    void __hayarSiguienteCoordenada(cuInt &x, cuInt &y,bool &condicion);
    //<--
};

#endif // KSONDA_H
