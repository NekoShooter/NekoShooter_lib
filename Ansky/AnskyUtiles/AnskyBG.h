#ifndef __AnskyBG
#define __AnskyBG

#include "__GITICONST__.h"
class QImage;
class QPoint;
class QString;
class QMatrix;

QImage *CargarImagen(const QString & direccion);

void Pegado(QImage *&base, const QImage *imagen, const int &x = 0, const int &y = 0);

QImage *VaritaMagica(QImage *&imagen,cuInt nuevoColor, cuInt color, cuChar &umbral = 0);
QImage *Coloreado(QImage *&imagen, const QPoint &coor, cuInt color, cuChar &umbral = 0, const bool &capa_independiente = false, const bool &limitar = false);
QImage *Coloreado(QImage *&imagen, const QPoint &coor, const QMatrix &matriz, cuInt color, cuChar &umbral = 0, const bool &capa_independiente = false, const bool &limitar = false);

QImage *testKSonda(QImage *&imagen, const QPoint &coor, cuInt color, cuChar &umbral = 0, const bool &capa_independiente = false, const bool &limitar = false);

#endif // __AnskyBG
