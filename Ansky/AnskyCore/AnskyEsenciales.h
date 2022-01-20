#ifndef ANSKYESENCIALES_H
#define ANSKYESENCIALES_H
#include <QList>
#include "__GITICONST__.h"


void AgregarPixel(const QImage &img, cuInt &id_color_del_pixel, cuInt &x, cuInt &y, QList<QPoint> &lista, bool &condicion);
bool ColoreadoLineal(QImage &img, cuInt &id_color_del_pixel, const QPoint& punto_de_partida, QList<QPoint> &lista, cuInt &id_nuevo_color, bool mod_inverso = false, QImage * capa = nullptr);

#endif // ANSKYESENCIALES_H
