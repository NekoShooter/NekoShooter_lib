#include "AnskyEsenciales.h"
#include "AnskyShorts.h"
#include <QImage>

void AgregarPixel(QImage *img, QImage *capa,cuInt &nuevocolor, cuInt &Rmax, cuInt &Rmin, cuInt &x, cuInt &y, QList<QPoint> &lista, bool &condicion){

    if(img->pixelColor(x,y).rgba() >= Rmin && img->pixelColor(x,y).rgba() <= Rmax){
        if(capa->pixelColor(x,y).rgba() != nuevocolor && condicion)
             lista.append(QPoint(x,y));
        condicion = false;}

    else {
        capa->setPixel(x,y,nuevocolor);
        condicion = true;}
}


/**************************************************************************************************************/



bool ColoreadoLineal(QImage *img, QImage * capa, cuInt &nuevocolor, cuInt &Rmax, cuInt &Rmin, const QPoint &punto_de_partida, QList<QPoint> &lista, bool mod_inverso, bool limitar){
    char siguiente_espacio =  1;            //derecha
    if(mod_inverso) siguiente_espacio = -1; //izquierda

    bool agregar_pixel_sup = true,
         agregar_pixel_inf = true;

    QPoint p = punto_de_partida;
    capa->setPixel(p,nuevocolor);

    while(true){
        AgregarPixel(img,capa,nuevocolor,Rmax,Rmin,p.x(),p.y() - 1,lista,agregar_pixel_sup); //arriba
        AgregarPixel(img,capa,nuevocolor,Rmax,Rmin,p.x(),p.y() + 1,lista,agregar_pixel_inf); //abajo

        p.rx() = p.rx() + siguiente_espacio;

        if(limitar && (p.rx() < 0 || p.rx() > img->width())) return false;

        if(img->pixelColor(p).rgba() >= Rmin && img->pixelColor(p).rgba() <= Rmax){
            capa->setPixel(p,nuevocolor);}

        else{
            capa->setPixel(p,nuevocolor);
            return true;}}}



/**************************************************************************************************************/


