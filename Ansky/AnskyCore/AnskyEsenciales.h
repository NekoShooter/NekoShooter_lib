#ifndef __AnskyEsenciales
#define __AnskyEsenciales
#include <QList>
#include "__GITICONST__.h"

void AgregarPixel(QImage *img, QImage *capa, cuInt &nuevocolor, cuInt &Rmax, cuInt &Rmin, cuInt &x, cuInt &y, QList<QPoint> &lista, bool &condicion);
bool ColoreadoLineal(QImage *img, QImage * capa, cuInt &nuevocolor, cuInt &Rmax, cuInt &Rmin, const QPoint &punto_de_partida, QList<QPoint> &lista, bool mod_inverso = false, bool limitar = false);

#endif // __AnskyEsenciales
