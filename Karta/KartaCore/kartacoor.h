#ifndef KARTACOOR_H
#define KARTACOOR_H


#include <Qt>
#include "kartavar.h"
#include "__KARTACONST__.h"
#include "__GITICONST__.h"
#include <QSize>
#include <QPoint>

class QMouseEvent;
class QWidget;
class QRect;
class QPointF;

/***********************************************************************************************/
#define _H_ 0
#define _V_ 1

union k_index{
    qint32 data;
    qint16 indice[2];};

/***********************************************************************************************/
QPointF coordenadasCirculares(const QPointF &CENTRO, cFloat &RADIO, cFloat &NumDeSecciones, cFloat &index, Karta::Sentido sentido = Karta::Radial);

/***********************************************************************************************/

class kcelda{
    public:
        kcelda(const QWidget *WIDGET);
        kcelda(const QSize &tamanyo, const Karta::Modo &Modo = Karta::Relativo);
        kcelda(const QSize &tamanyo, const QWidget *WIDGET);
        kcelda(const QSize &tamanyo, const QWidget *WIDGET, const Karta::Modo &Modo);

        QRect qrect(cuShort &idx_h = 0, cuShort &idx_v = 0);
        ~kcelda();

        void mouseMoveEvent(QMouseEvent *event);
        const k_index &mousePressEvent(QMouseEvent *event);
        const k_index &mousePos(QMouseEvent *event);

        bool esValido() const;
        void cambiarTam(const QSize &tamanyo);
        void recargar(const QSize &tamanyo,const QWidget *WIDGET = nullptr,const Karta::Modo &Modo = Karta::Relativo);
        void restringirMov(const Karta::orientacion &mov);

        inline void Widget(const QWidget *WIDGET){widget = WIDGET;}
        inline void agregarMargenDer(cuShort &derecho){margenH_der = derecho;}
        inline void agregarMargenIzq(cuShort &izquierda){margenH_izq = izquierda;}
        inline void agregarMargenSup(cuShort &superior){margenV_sup = superior;}
        inline void agregarMargenInf(cuShort &inferior){margenV_inf = inferior;}
        inline void agragarMargenH(cuShort &izquierdo, cuShort &derecho){margenH_der = derecho; margenH_izq = izquierdo;}
        inline void agregarMargenV(cuShort &superior, cuShort &inferior){margenV_sup = superior; margenV_inf = inferior;}

        inline const QPoint &Coor() const {return coor;}
        inline void Scroll(const int &ScrollH,const int &ScrollV){scroll_h = ScrollH; scroll_v = ScrollV;}
        void limpiar();
        void BorrarRecuadro();
        void Recuadro(const QSize &recuadro_interno, const Qt::Alignment &Alineacion = Qt::AlignCenter);
        void moverRecuadro(cuShort &mover_h = 0, cuShort &mover_v = 0){moverEnH = mover_h; moverEnV = mover_v;};

    private:
        void __cargarDatos();

        QSize *Tam = nullptr;
        QSize frame;
        uShort margenH_der, margenV_sup, moverEnH,
               margenH_izq, margenV_inf, moverEnV;

        int scroll_h;
        int scroll_v;

        Qt::Alignment alineacion = Qt::AlignCenter;
        Karta::Modo modo = Karta::Relativo;

        QPoint coor;
        QPoint *cursor_desplazado = nullptr;
        QPoint *cursor_click = nullptr;

        const QWidget *widget =nullptr;
        k_index indices;
        bool mov_h, mov_v;

    };
#endif // KARTACOOR_H
