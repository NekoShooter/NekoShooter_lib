#ifndef KARTAVAR_H
#define KARTAVAR_H


#include <Qt>
#include "../../Giti/GitiCore/__GITICONST__.h"
#define _H_ 0
#define _V_ 1


class QSize;
class QRect;


/***********************************************************************************************/
union k_punto{
    qint16 indice[2];
    qint32 data;};

/***********************************************************************************************/
class KCelda{
    public:
        KCelda(const QSize &tamanyo, cuShort &IndiceX = 0, cuShort &IndiceY = 0);
        KCelda(const QSize &tamanyo, const k_punto &posicion);
        ~KCelda();
        bool esValido() const;
        void cambiarTam(const QSize &tamanyo);
        inline void index_H(cuShort &IndiceX = 0){pos.indice[_H_] = IndiceX;};
        inline void index_V(cuShort &IndiceY = 0){pos.indice[_V_] = IndiceY;};
        k_punto pos;
        QSize *Tam = nullptr;};

/***********************************************************************************************/

class KFormato{
    public:
        KFormato(cuShort &MargenX = 0, cuShort &MargenY = 0, cShort &MoverEnX = 0,cShort  &MoverEnY = 0,
                 const Qt::Alignment &Alineacion = Qt::AlignCenter);
        bool esValido()const;
        void rectificar(const KCelda &C);
        inline void cambiarMargenH(cuShort &MargenX){margenX = MargenX;};
        inline void cambiarMargenV(cuShort &MargenY){margenY = MargenY;};
        inline void moverHorizontal(cShort &MoverEnX){moverEnX = MoverEnX;};
        inline void moverVertical(cShort &MoverEnY){moverEnY = MoverEnY;};
        inline void cambiarAlineacion(const Qt::Alignment &Alineacion){alineacion = Alineacion;};

        unsigned short margenX,  margenY;
        short  moverEnX, moverEnY;
        Qt::Alignment alineacion;};

/***********************************************************************************************/

class KScroll{
    public:
        KScroll(cShort &Scroll = 0, const Qt::Orientation &Orientacion = Qt::Horizontal, cuShort &LimiteMin = 0, cuShort &LimiteMax = 0);
        bool esValido()const;
        inline void cambiarScroll_v(cShort &Scroll_V){scroll_v = Scroll_V;};
        inline void cambiarScroll_h(cShort &Scroll_H){scroll_h = Scroll_H;};
        inline void cambiarLimites_h(cuShort &LimiteMin, cuShort &LimiteMax){limiteMin_h = LimiteMin; limiteMax_h = LimiteMax;};
        inline void cambiarLimites_v(cuShort &LimiteMin, cuShort &LimiteMax){limiteMin_v = LimiteMin; limiteMax_v = LimiteMax;};
        void rectificar();
        short  scroll_h, scroll_v;
        uShort limiteMin_h, limiteMax_h;
        uShort limiteMin_v, limiteMax_v;};

/**********************************************************************************************/
class KCursor{
    public:
        KCursor(const double &moviento_enX = 0,const double &moviento_enY = 0)
            : cursorX(moviento_enX), cursorY(moviento_enY){};
        inline void cambiarMovCursor(const double &moviento_enX,const double &moviento_enY){ cursorX = moviento_enX, cursorY = moviento_enY;};
        inline void cambiaMovX(const double &moviento_enX){cursorX = moviento_enX;};
        inline void cambiaMovY(const double &moviento_enY){cursorY = moviento_enY;};
        double cursorX, cursorY;};

/***********************************************************************************************/

#endif // KARTAVAR_H
