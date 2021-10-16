#include "kartavar.h"
#include <QRect>

KCelda::KCelda(const QSize &tamanyo, cuShort &IndiceX, cuShort &IndiceY){
    if(tamanyo.isEmpty()) return;
    Tam = new QSize(tamanyo);
    pos.indice[_H_] = IndiceX;
    pos.indice[_V_] = IndiceY;}

KCelda::KCelda(const QSize &tamanyo, const k_punto &posicion){
    if(tamanyo.isEmpty()) return;
    Tam = new QSize(tamanyo);
    pos = posicion;}

void KCelda::cambiarTam(const QSize &tamanyo){
    if(tamanyo.isEmpty()) return;
    if(Tam) *Tam = tamanyo;
    else Tam = new QSize(tamanyo);}

KCelda::~KCelda(){if(Tam) delete Tam;}

bool KCelda::esValido() const{return !(!Tam|| Tam->isEmpty());};

/***********************************************************************************************/

KFormato::KFormato(cuShort &MargenX, cuShort &MargenY, cShort &MoverEnX,cShort &MoverEnY, const Qt::Alignment &Alineacion){
    margenX     = MargenX;    margenY     = MargenY;
    moverEnX    = MoverEnX;   moverEnY    = MoverEnY;
    alineacion  = Alineacion;}

bool KFormato::esValido()const{ return !(margenX < 0 ||margenY < 0);}

void KFormato::rectificar(const KCelda &C){
    if(!C.esValido()) return;
    if(C.Tam->width() < (margenX * 2)) margenX = 0;
    if(C.Tam->height() < (margenY * 2)) margenY = 0;}

/***********************************************************************************************/

KScroll::KScroll(cShort &Scroll, const Qt::Orientation &Orientacion, cuShort &LimiteMin, cuShort &LimiteMax){
    switch (Orientacion) {
        case Qt::Horizontal:
            scroll_h    = Scroll;    scroll_v    = 0;
            limiteMin_h = LimiteMin; limiteMin_v = 0;
            limiteMax_h = LimiteMax; limiteMax_v = 0;
            break;
        case Qt::Vertical:
            scroll_v    = Scroll;    scroll_h    = 0;
            limiteMin_v = LimiteMin; limiteMin_h = 0;
            limiteMax_v = LimiteMax; limiteMax_h = 0;
            break;}}

bool KScroll::esValido() const{ return !(limiteMax_h < limiteMin_h || limiteMax_v < limiteMin_v);}

void KScroll::rectificar(){
    if(esValido()) return;
    if(limiteMax_h < limiteMin_h)
        limiteMax_h = limiteMin_h = 0;
    if(limiteMax_v < limiteMin_v)
        limiteMax_v = limiteMin_v = 0;}

