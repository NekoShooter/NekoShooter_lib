#ifndef KARTACOOR_H
#define KARTACOOR_H


#include <QPointF>
#include <QRectF>
#include "kartavar.h"
#include "__KARTACONST__.h"
#include "../Giti/GitiCore/__GITICONST__.h"

QPointF coordenadasCirculares(const QPointF &CENTRO, cFloat &RADIO, cFloat &NumDeSecciones, cFloat &index, Karta::Sentido sentido = Karta::Radial);



/***********************************************************************************************/
QRect posicionarCeldas(KCelda &C, KFormato &F, KScroll &S, KCursor &P, const Karta::Modo &modo = Karta::Relativo);

QRect posicionarCeldas(KCelda &C, KScroll &S,  KCursor &P, const Karta::Modo &modo = Karta::Relativo);
QRect posicionarCeldas(KCelda &C, KFormato &F, KScroll &S, const Karta::Modo &modo = Karta::Relativo);
QRect posicionarCeldas(KCelda &C, KFormato &F, KCursor &P, const Karta::Modo &modo = Karta::Relativo);
QRect posicionarCeldas(KCelda &C, KScroll &S,  const Karta::Modo &modo = Karta::Relativo);
QRect posicionarCeldas(KCelda &C, KCursor &P,  const Karta::Modo &modo = Karta::Relativo);
QRect posicionarCeldas(KCelda &C, KFormato &F, const Karta::Modo &modo = Karta::Relativo);
QRect posicionarCeldas(KCelda &C, const Karta::Modo &modo = Karta::Relativo);
/***********************************************************************************************/
#endif // KARTACOOR_H
