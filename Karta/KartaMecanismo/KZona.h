#ifndef KZONA_H
#define KZONA_H
#include <QVector>

#include "HRango.h"
#include "HNotificador.h"

class HNotificador;
class QSize;
class QPoint;
class QRect;
class QMouseEvent;
class QWidget;
class QMatrix;

class KZona{
    public:
        enum Borde {EIIzq, EIDer, ESIzq, ESDer,LDer, LIzq, LSup, LInf, RECT,INT,TOTAL,VACIO};

        KZona(){SEGUROACTIVO = true;}
        ~KZona();

        KZona(const QSize &tam){ ReAjustar(tam);}
        KZona(const QRect &rect){ ReAjustar(rect);}
        KZona(const QWidget *& widget);

        void Expandir(const QPoint &punto);
        void ExpandirPx(const short &x);
        void ExpandirPy(const short &y);

        void Expandir(const QPoint& ancla, const QPoint &espacio, const Borde &b);

        void ReAjustar(const QSize &tam);
        void ReAjustar(const QRect &rect);
        void ReAjustar();

        void CambiarMargen(const short &margen);
        void CambiarQMatrix(QMatrix *&matrix);

        void ActualizarBordes();

        Borde IdxLimite(const QPoint &p)const;

        QRect rect(const Borde &p) const;
        QRect rect(const QPoint &p) const;
        QRect rectForm(const KZona::Borde &indx) const;
        QRect rectActivo() const;


        QRect rect()   const;
        QSize size()   const;
        QPoint pointESIzq() const;
        QPoint pointESDer() const;
        QPoint pointEIDer() const;
        QPoint pointEIIzq() const;

        QPoint SupIzq() const;
        QPoint SupDer() const;
        QPoint InfIzq() const;
        QPoint InfDer() const;


        void ActivarRastreo(bool activar);

        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent (QMouseEvent *event);
        void mouseReleaseEvent();



    private:

        short __infX = 0, __supX = 0, __margen = 0,
              __infY = 0, __supY = 0;

        short __px , __py ,
              __sx , __sy ;

        HRango<short> __x, __y;
        HRango<short> __xp, __yp;
        HRango<short> __xc, __yc;
        QRect * __rect = nullptr;

        Borde __rectActivo = Borde::VACIO;

        bool SEGUROACTIVO = false;
        HNotificador __modifcacionHecha = false;

        QVector<QRect> *__vbordes = nullptr;
        QWidget * __widget = nullptr;
        QPoint *__ancla;
        QMatrix * __matrix = nullptr;

        void __ReAjustar();
        void __ReAsignar();


    public:

        inline void CargarWidget(QWidget *widget) {__widget = widget;}

        inline bool EsValido() const {return !((__xp.estaVacio() || __yp.estaVacio())&& !SEGUROACTIVO);}
        //inline bool EsValido() const {return !((__px >= __sx || __py >= __sy)&& !SEGUROACTIVO);}
        inline const short &x () const {return __px;}
        inline const short &xs() const {return __sx;}
        inline const short &y () const {return __py;}
        inline const short &ys() const {return __sy;}

        inline const QVector<QRect> * Bordes()const{return __vbordes;}
        inline const short &Margen() const{return __margen;}

        QRect SupDer(const short &margen) const;
        QRect SupIzq(const short &margen) const;
        QRect InfIzq(const short &margen) const;
        QRect InfDer(const short &margen) const;
        QRect LatDer(const short &margen) const;
        QRect LatIzq(const short &margen) const;
        QRect LatSup(const short &margen) const;
        QRect LatInf(const short &margen) const;
        QRect Interno(const short &margen) const;
        QRect Contorno()const;
        QRect Total(const short &margen)const;
};

#endif // KZONA_H
