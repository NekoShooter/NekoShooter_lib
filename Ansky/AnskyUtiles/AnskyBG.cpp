#include "AnskyBG.h"
#include "AnskyEsenciales.h"
#include "Colori__rgb__.h"
#include "ColoriMath.h"
#include <QImage>
#include <QImageReader>
#include "ColoriUtiles.h"
#include "AnskyShorts.h"
#include "KSonda.h"

QImage *CargarImagen(const QString &direccion){
    if(direccion.isEmpty()) return nullptr;

    QImageReader lector(direccion);
    QImage *Imagen = new QImage(lector.size(),QImage::Format_ARGB32_Premultiplied);
    Imagen->fill(QColor(0,0,0,0));

    if(Imagen->isNull()){  delete Imagen; return nullptr;  }
    else lector.read(Imagen);

    return Imagen;}


/************************************************************************************/



QImage *Colorear(QImage *&imagen, const QPoint &coordenada, cuInt id_nuevo_color, const bool &capa_independiente){
    if(!imagen || imagen->isNull()) return nullptr;

    QRgb Color_del_pixel = imagen->pixelColor(coordenada).rgba();

    if(id_nuevo_color == Color_del_pixel) return nullptr;

    QImage *capa = nullptr;
    QImage *img = imagen;


    if(capa_independiente){
        img = new QImage(*imagen);
        capa = new QImage(imagen->size(),QImage::Format_ARGB32_Premultiplied);
        capa->fill(QColor(0,0,0,0).rgba());}

    QList<QPoint> coor_pendientes;
    coor_pendientes.append(coordenada);

    bool Ok_d,
         Ok_i;

    while(!coor_pendientes.isEmpty()){
        const QPoint p = coor_pendientes.back();
                         coor_pendientes.pop_back();
        Ok_d = ColoreadoLineal(*img,Color_del_pixel,p,coor_pendientes,id_nuevo_color,false,capa);
        Ok_i = ColoreadoLineal(*img,Color_del_pixel,p,coor_pendientes,id_nuevo_color,true,capa);

        if(!Ok_d || !Ok_i){
            if(capa) delete capa;
            capa = nullptr;
            break;}};

    if(capa_independiente && img)delete img;
    return capa;}


/*******************************************************************************/


QImage *Colorear2(QImage *&imagen, const QPoint &coor, cuInt color, cuChar &umbral, const bool &capa_independiente){
    if(!imagen || imagen->isNull()) return nullptr;

    c_rgb max = {imagen->pixelColor(coor).rgba()};
    c_rgb min = {imagen->pixelColor(coor).rgba()};

    autoIncrementarLuminicencia(&max,umbral);
    autoIncrementarLuminicencia(&min,-umbral);

    QImage *capa = nullptr;
    KSonda *mapa = new KSonda(imagen->size());
    if(capa_independiente){ capa = nuevoQImage(imagen->size()); }

    QList<QPoint> cola;
    cola.append(coor);

    bool Ok_d,
         Ok_i;

    while(!cola.isEmpty()){
        const QPoint p = cola.back();
                         cola.pop_back();
        Ok_d = ColoreadoLineal2(*imagen,mapa,max.id_a,min.id_a,p,cola,color,false,capa);
        Ok_i = ColoreadoLineal2(*imagen,mapa,max.id_a,min.id_a,p,cola,color,true,capa);

        if(!Ok_d || !Ok_i){
            if(capa) delete capa;
            capa = nullptr;
            break;}};
    delete mapa;
    return capa;
}
