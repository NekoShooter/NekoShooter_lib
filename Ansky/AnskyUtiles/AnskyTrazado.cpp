#include "AnskyTrazado.h"
#include "kartacoor.h"

#include <QPainter>


void UnirPuntos(QPainter &painter, const QList<QPointF> &lista_de_coor, const QPointF &ancla , cDouble &angulo , const bool &anti_radial){
    if(lista_de_coor.isEmpty()) return;

    if(ANGULO_VALIDO(angulo)){
        QList<QPointF> lista_de_puntos;
        for(auto i = lista_de_coor.begin(); i != lista_de_coor.end(); i++)
            lista_de_puntos.append(rotarCoordenada(ancla,*i,angulo,anti_radial));
        for(auto punto = lista_de_puntos.begin();(punto + 1) != lista_de_puntos.end(); punto++)
            painter.drawLine(*punto,*(punto + 1));
        painter.drawLine(*lista_de_puntos.begin(),*(--lista_de_puntos.end()));
        return;}

   for(auto i = lista_de_coor.begin();i + 1 != lista_de_coor.end(); i++)
        painter.drawLine(*i,*(i + 1));
    painter.drawLine(*lista_de_coor.begin(), *(--lista_de_coor.end()));}



/********************************************************************************/




