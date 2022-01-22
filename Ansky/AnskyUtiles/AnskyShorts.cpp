#include "AnskyShorts.h"
#include <QImage>

QImage *nuevoQImage(const QSize &tam){
    if(tam.isNull()) return nullptr;
    QImage *img = new QImage(tam, QImage::Format_ARGB32_Premultiplied);
    img->fill(QColor(0,0,0,0));
    return img;}
