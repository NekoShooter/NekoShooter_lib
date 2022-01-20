#include "anskytrazo.h"
#include "AnskyEsenciales.h"
#include "kartacoor.h"

#include <QPainter>
#include <QImage>


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



QImage *Colorear(QImage *imagen, const QPoint &coordenada, cuInt id_nuevo_color, const bool &capa_independiente){
    if(!imagen || imagen->isNull()) return nullptr;

    QRgb Color_del_pixel = imagen->pixelColor(coordenada).rgba();

    if(id_nuevo_color == Color_del_pixel) return nullptr;

    QImage *capa = nullptr;
    QImage img_tem = *imagen;

    if(capa_independiente){
        capa = new QImage(imagen->size(),QImage::Format_ARGB32_Premultiplied);
        capa->fill(QColor(0,0,0,0).rgba());}

    QList<QPoint> coor_pendientes;
    coor_pendientes.append(coordenada);

    bool Ok_d,
         Ok_i;

    while(!coor_pendientes.isEmpty()){
        const QPoint p = coor_pendientes.back();
                         coor_pendientes.pop_back();
        Ok_d = ColoreadoLineal(img_tem,Color_del_pixel,p,coor_pendientes,id_nuevo_color,false,capa);
        Ok_i = ColoreadoLineal(img_tem,Color_del_pixel,p,coor_pendientes,id_nuevo_color,true,capa);

        if(!Ok_d || !Ok_i){
            if(capa) delete capa;
            return nullptr;}};

    if(!capa) *imagen = img_tem;
    return capa;}
