#ifndef KRUTA_H
#define KRUTA_H

#include <QList>
#include "HRango.h"
#include "HNotificador.h"
#include "HPtr.h"

class QMouseEvent;

class KRuta{
    public:
        using iterator = QList<QPointF>::iterator;

        KRuta();
        ~KRuta(){if(__ruta) delete __ruta;}
        KRuta(QWidget *widget);
        KRuta(const QList<QPointF> &listaDeCoordenadas, QWidget * widget = nullptr);
        KRuta(QList<QPointF> *ListaDeCoordenadas,QWidget * widget = nullptr);

        void AgregarPunto(const QPoint &punto);
        void AgregarPunto(const QPointF &punto);

        void CambiarListaDeCoordenadas(const QList<QPointF> &listaDeCoordenadas);
        void EnlazarListaDeCoordenadas(QList<QPointF> *listaDeCoordenadas);
        void EnlazarMatrix(QMatrix * matrix);

        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent * event);
        void mouseMoveEvent(QMouseEvent * event);

        void ActivarRastreo(bool activar);

        void SimplificarRuta();

        QList<QPointF>::iterator Nodo(const QPoint &coordenada);
        QRect ContornoNodo(QList<QPointF>::iterator nodo);
        QRect ContornoNodoSelecionado();
        QRect ContornoNodoVisible();
        const QRect &Rect();

        inline bool HayNodoVisible() const {return __nodoVisible.i;}
        inline bool HayNodoSeleccionado() const {return __nodoSeleccionado.i;}

        void EliminarNodoSelecionado();

        void Limpiar();
        void Resetear();
        void ReanudarRuta();
        void FinalizarRuta();

        inline QList<QPointF>::iterator NodoSeleccionado()const{ return __nodoSeleccionado;}

        inline const QList<QPointF> *Ruta(){return  __ruta->ptr;}
        inline QList<QPointF> *pRuta(){return __ruta->ptr;}

        inline void CambiarRadioDelNodo(const unsigned short &radio){__radioNodo = radio;}
        inline void EnlazarQWidget(QWidget *widget){__widget = widget;}
        inline void ComunicarConQWidget(QWidget *widget){__widget = widget;}

        inline bool esAutonomo() const {return __ruta->esIndependiente();}
        inline bool esNulo() const {return __ruta->esNulo();}
        inline bool esValido() const {return __ruta->esValido();}

        enum MODO {NULO = 0, GUIA = 0x1, LIBRE = 0x2, EDICION = 0x4,
                   HIBRIDO = GUIA | LIBRE, COMPLETO = HIBRIDO | EDICION};

        void ModoDeRuta(const unsigned short & modo = GUIA){__modo = MODO(modo);}

        iterator begin();
        iterator end();

    protected:
        HPtr<QList<QPointF>> *__ruta;

        HRango<short> __x, __y;
        unsigned short __radioNodo;

        MODO __modo;

        void __inicializar();
        void __destruir();

        void __deslastrarRuta();
        void __lastrarRuta(const QPointF &coordenada);

        void __identificarNodoVisible(const QPoint &coor);
        void __invertedMatrix();
        void __mapMatrix();


    private:
        QList<QPointF>::iterator __lastre;
        QList<QPointF>::iterator __nodoSeleccionado;
        QList<QPointF>::iterator __nodoVisible;

        unsigned short __numeroDelNodo;

        QWidget * __widget;
        QMatrix * __matrix;
        HNotificador __nuevosPuntosAgregados, *__nuevoCambio;
        QRect __rect;

        bool __arrancarGeneradoDeRuta;

        void __marcarRuta(QList<bool> &marcas, const int &inicio, const int &final);
        void __modRuta_modNodo(const QPointF &coordenada);
        void __generarRect();
    };

#endif // KRUTA_H
