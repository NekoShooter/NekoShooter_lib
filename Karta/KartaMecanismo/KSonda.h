#ifndef __KSonda
#define __KSonda
#include "__GITICONST__.h"
#include <QList>

union c_rgb;

struct kbool{ bool on: 1; }__attribute__((packed));

class KSonda
{
public:
    KSonda(){__inicializar();}
    ~KSonda(){Borrar();}

    KSonda(cuInt &Largo, cuInt &Alto);
    KSonda(const QSize &tam);
    KSonda(const QImage &img, const QPoint &coordenada, cuChar &umbral = 0, bool limitar = false);

    void CambiarDimencion(cuInt &Largo, cuInt &Alto);
    void CambiarDimencion(const QSize &tam);

    void Reiniciar(cuInt &Largo, cuInt &Alto);
    void Reiniciar(const QSize &tam);
    void Reiniciar(const QImage &img, const QPoint &coordenada, cuChar &umbral = 0, bool limitar = false);

    void Marcar_v(cuInt &x, cuInt &y);
    void Marcar(cuInt &x, cuInt &y);
    void Marcar(const QPoint &coordenada);

    void Desmarcar(cuInt &x, cuInt &y);
    void Desmarcar(const QPoint &coordenada);

    bool EstaMarcado(cuInt &x, cuInt &y) const;
    bool EstaMarcado(const QPoint &coordenada)const;

    void Explorar(const QImage &imagen, const QPoint &coordenada, cuChar &umbral = 0, bool Limitar = false);
    void Explorar(const QImage &imagen, cuInt &id_color, cuChar &umbral = 0, bool alfa = false);
    void Explorar(const QImage &imagen);
    void Limpiar();
    void Borrar();

    QSize size(){return QSize(__largo,__alto);}


    inline kbool **pSonda(){ return __map;}

    inline cuShort &alto()const {return __alto;}
    inline cuShort &largo()const {return __largo;}

    inline bool esNull()const {return !__map;}
    inline bool estaVacio()const{return !__num_marcas;}
    inline bool esValido()const{return __es_valido;}

    uShort begin();
    inline cuInt &end() const {return __num_marcas;}
    inline cuShort &xBegin() const {return __XInf;}
    inline cuShort &yBegin() const {return __YInf;}
    inline uShort xEnd() const {return __XSup + 1;}
    inline uShort yEnd() const {return __YSup + 1;}

    QPoint iterator();



private:
    kbool ** __map = nullptr;
    bool __es_valido;
    uShort __largo, __alto;
    uInt __num_marcas;
    uShort __XSup, __XInf, __YSup, __YInf;


    void __inicializar();
    kbool** __generarMapa(cuInt &Largo, cuInt &Alto);
    void __borrar_matriz();


    //-  ESCANEO ->
    c_rgb *max, *min;
    const QImage *img;
    QList<QPoint> *lista;

    void __explorar(const QImage *imagen, const QPoint &coordenada, cuChar &umbral = 0, bool Limitar = false);
    bool __escaneoLinal(QPoint p, const bool &limitar, bool mod_inverso = false);
    void __hayarSiguienteCoordenada(cuInt &x, cuInt &y, bool &condicion);
    //<- ESCANEO FIN -


    //-  ITERADOR ->
    uInt * iter_x, *iter_y, *iter_contador;
    bool iter_init;
    void __iter_borrar();
    //<- ITERADOR FIN -
};

#endif // __KSonda
