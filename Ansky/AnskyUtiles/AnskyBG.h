#ifndef ANSKYBG_H
#define ANSKYBG_H

#include "__GITICONST__.h"
class QImage;
class QPoint;
class QString;

QImage *CargarImagen(const QString & direccion);

QImage *Colorear(QImage *&imagen, const QPoint &coordenada, cuInt id_nuevo_color, const bool &capa_independiente = false);
QImage *Colorear2(QImage *&imagen, const QPoint &coor, cuInt color, cuChar &umbral = 0, const bool &capa_independiente = false);


#endif // ANSKYBG_H
