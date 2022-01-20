#include "AnskyEsenciales.h"
#include <QImage>

void AgregarPixel(const QImage &img, cuInt &id_color_del_pixel, cuInt &x, cuInt &y, QList<QPoint> &lista, bool &condicion){
    if(id_color_del_pixel == img.pixelColor(x,y).rgba()){
        if(condicion)
            if(!lista.contains(QPoint(x,y)))
                lista.append(QPoint(x,y));
        condicion = false;}

    else condicion = true;}



/**************************************************************************************************************/



bool ColoreadoLineal(QImage &img, cuInt &id_color_del_pixel, const QPoint &punto_de_partida, QList<QPoint> &lista, cuInt &id_nuevo_color, bool mod_inverso, QImage * capa){
    char siguiente_espacio =  1;            //derecha
    if(mod_inverso) siguiente_espacio = -1; //izquierda

    bool agregar_pixel_sup = true,
         agregar_pixel_inf = true;

    QColor nuevo_color(qRed(id_nuevo_color),qGreen(id_nuevo_color),qBlue(id_nuevo_color),qAlpha(id_nuevo_color));

    QPoint p = punto_de_partida;
    img.setPixelColor(p,nuevo_color);
    if(capa) capa->setPixelColor(p,nuevo_color);

    while(true){
        AgregarPixel(img,id_color_del_pixel,p.x(),p.y() - 1,lista,agregar_pixel_sup); //arriba
        AgregarPixel(img,id_color_del_pixel,p.x(),p.y() + 1,lista,agregar_pixel_inf); //abajo

        p.rx() = p.rx() + siguiente_espacio;

        if(p.rx() < 0 || p.rx() > img.width()) return false;

        if(img.pixelColor(p).rgba() == id_color_del_pixel){
            img.setPixelColor(p,nuevo_color);
            if(capa) capa->setPixelColor(p,nuevo_color);}
        else return true;}}
