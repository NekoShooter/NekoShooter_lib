#include "AnskyBG.h"
#include "AnskyEsenciales.h"
#include <QImage>
#include <QImageReader>
#include "ColoriUtiles.h"
#include "AnskyShorts.h"
#include "KSonda.h"
#include <QPainter>
#include <QMatrix>
#include "KartaCoor.h"

QImage *CargarImagen(const QString &direccion){
    if(direccion.isEmpty()) return nullptr;

    QImageReader lector(direccion);
    QImage *Imagen = new QImage(lector.size(),QImage::Format_ARGB32_Premultiplied);
    Imagen->fill(QColor(0,0,0,0));

    if(Imagen->isNull()){  delete Imagen; return nullptr;  }
    else lector.read(Imagen);

    return Imagen;}
/************************************************************************************/


void Pegado(QImage *&base, const QImage *imagen, const int &x, const int &y){
    if(!base || !imagen) return;
    if(base->isNull() || imagen->isNull()) return;

    QImage *lienzo = base;
    QRect rect = base->rect().united(QRect(QPoint(x,y),imagen->size()));

    lienzo = nuevoQImage(rect.size());
    if(!lienzo) return;

    QPainter painter(lienzo);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0,0, *base);
    painter.drawImage(x,y, *imagen);
    painter.end();

    delete base;
    base = lienzo;}
/************************************************************************************/


QImage *Coloreado(QImage *&imagen, const QPoint &coor, const QMatrix &matriz, cuInt color, cuChar &umbral, const bool &capa_independiente, const bool &limitar){
    return Coloreado(imagen,ReCalcularCoordenada(coor,matriz).toPoint(),color,umbral,capa_independiente,limitar);}


QImage *Coloreado(QImage *&imagen, const QPoint &coor, cuInt color, cuChar &umbral, const bool &capa_independiente, const bool &limitar){
    if(!imagen || imagen->isNull()) return nullptr;
    if(limitar && imagen->pixelColor(coor).rgba() == color) return nullptr;
    if(coor.x() > imagen->width() || coor.y() > imagen->height()) return nullptr;
    if(coor.x() < 0 || coor.y() < 0) return nullptr;

    uInt _max = 0, _min = 0;
    RangoDeSimilaridad(imagen->pixelColor(coor).rgba(),&_max,&_min,umbral);

    QImage *capa = imagen;

    if(capa_independiente) capa = nuevoQImage(imagen->size());

    QList<QPoint> cola;
    cola.append(coor);

    bool Ok_d,
         Ok_i;

    while(!cola.isEmpty()){
        const QPoint p = cola.back();
                         cola.pop_back();
        Ok_d = ColoreadoLineal(imagen,capa,color,_max,_min,p,cola,false,limitar);
        Ok_i = ColoreadoLineal(imagen,capa,color,_max,_min,p,cola,true,limitar);

        if(!Ok_d || !Ok_i){
            if(capa_independiente) delete capa;
            return nullptr;}};

    if(capa_independiente) return capa;
    return nullptr;}
/*******************************************************************************/


QImage *testKSonda(QImage *&imagen, const QPoint &coor, cuInt color, cuChar &umbral, const bool &capa_independiente, const bool &limitar){
    if(!imagen || imagen->isNull()) return nullptr;
    KSonda e(*imagen, coor,umbral,limitar);
    if(!e.esValido())return  nullptr;
    QImage *img = imagen;
    QImage *capa = nullptr;

    if(capa_independiente){
        capa = nuevoQImage(imagen->size());
        img = capa;}
    for(uInt i = e.begin(); i < e.end(); ++i)
        img->setPixel(e.iterator(),color);

    return capa;

}
