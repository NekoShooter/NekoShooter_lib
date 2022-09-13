#ifndef __KArea
#define __KArea
#include <QVector>
#include "HNotificador.h"
#include "HRango.h"
#include <QPoint>

class QSize;
//class QPoint;
class QRect;
class QMouseEvent;
class QWidget;
class QMatrix;

class KArea{
    public:
        enum Borde {EIIzq, EIDer, ESIzq, ESDer,LDer, LIzq, LSup, LInf, CEN, VACIO};

        KArea(){__inicializar();
                SEGUROACTIVO = true;}
        ~KArea();

        KArea(const QSize &tam){
            __inicializar();
            ReAjustar(tam);}
        KArea(const QRect &rect){
            __inicializar();
            ReAjustar(rect);}

        void Expandir(const QPoint &punto);
        void ExpandirPx(const short &x);
        void ExpandirPy(const short &y);

        void Expandir(const QPoint& ancla, const QPoint &espacio, const Borde &b);

        void ReAjustar(const QSize &tam);
        void ReAjustar(const QRect &rect);
        void ReAjustar();

        void CambiarMargen(const short &margen);

        void ActualizarBordes();

        Borde IdxLimite(const QPoint &p)const;
        const Borde &Indice() const {return __rectActivo;}

        QRect rect(const Borde &p) const;
        QRect rect(const QPoint &p) const;
        QRect rectForm(const KArea::Borde &indx) const;
        QRect rectActivo() const;


        QRect  rect(bool matrixActivada = true)   const;
        QSize  size()   const;
        QPoint pointESIzq() const;
        QPoint pointESDer() const;
        QPoint pointEIDer() const;
        QPoint pointEIIzq() const;


        void ActivarRastreo(bool activar);
        void CargarMatrix(QMatrix *&matrix);

        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent (QMouseEvent *event);
        void mouseReleaseEvent();



    private:

        short __infX = 0, __supX = 0, __margen = 0,
              __infY = 0, __supY = 0;

        short __px , __py ,
              __sx , __sy ;

        HRango<int> __x, __y, __xp, __yp, __rx, __ry;

        Borde __rectActivo = Borde::VACIO;

        bool SEGUROACTIVO = false;
        HNotificador __modifcacionHecha = false;
        QMatrix * __matrix = nullptr;

        QVector<QRect> *__vbordes = nullptr;
        QWidget * __widget = nullptr;
        QPoint __ancla;
        bool anclaje = false;

        void __ReAjustar();
        void __ReAsignar();
        void __inicializar();


    public:

        inline void CargarWidget(QWidget *widget) {__widget = widget;}

        inline bool EsValido() const {return !((__px >= __sx || __py >= __sy)&& !SEGUROACTIVO);}
        inline const short &x () const {return __px;}
        inline const short &xs() const {return __sx;}
        inline const short &y () const {return __py;}
        inline const short &ys() const {return __sy;}

        inline const QVector<QRect> * Bordes()const{return __vbordes;}
        inline const short &Margen() const{return __margen;}

        QRect EsqSupDer(const short &margen) const;
        QRect EsqSupIzq(const short &margen) const;
        QRect EsqInfIzq(const short &margen) const;
        QRect EsqInfDer(const short &margen) const;
        QRect LatDer(const short &margen) const;
        QRect LatIzq(const short &margen) const;
        QRect LatSup(const short &margen) const;
        QRect LatInf(const short &margen) const;
        QRect Interno(const short &margen) const;
        QRect Contorno() const;
};


#endif // __KArea