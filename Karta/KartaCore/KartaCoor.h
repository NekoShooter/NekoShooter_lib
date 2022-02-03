#ifndef __KartaCoor
#define __KartaCoor

#include "__KARTACONST__.h"
#include "__GITICONST__.h"

class QWidget;
class QPointF;
class QPoint;
class QMatrix;
class QSize;

/***********************************************************************************************/
#define _H_ 0
#define _V_ 1

union k_index{
    uInt data;
    uShort indice[2];};

/***********************************************************************************************/


QPointF coordenadasCirculares(const QPointF &CENTRO, cFloat &RADIO, cFloat &NumDeSecciones, cFloat &index, Karta::Sentido sentido = Karta::Radial);
QPointF rotarCoordenada(const QPointF &ancla, const QPointF &coor, cDouble &ang, const bool &anti_radial = false);
QPointF rotarCoordenada(const QPoint &ancla,const QPoint &coor,cDouble &ang, const bool &anti_radial = false);
QPointF rotarCoordenada(cDouble &ancla_x, cDouble &ancla_y, cDouble &coor_x, cDouble &coor_y, cDouble &ang, const bool &anti_radial = false);
QPointF ReCalcularCoordenada(const QPoint &coordenada, const QMatrix &matriz);
QPointF ReCentro(const QSize &timg, const QSize &twid, const QMatrix &m);
/***********************************************************************************************/

QMatrix Rotacion(const QPointF &ancla, const QPointF &partida, const QPointF &destino);

#endif // __KartaCoor
