#include "AnskyShorts.h"
#include <QImage>

QImage *nuevoQImage(const QSize &tam){
    if(tam.isNull()) return nullptr;
    QImage *img = new QImage(tam, QImage::Format_ARGB32_Premultiplied);
    img->fill(QColor(0,0,0,0));
    return img;}


QSize areaTotal(const QRect &a, const QRect &b){
    QSize tam_a(a.width() + a.x(),a.height() + a.y());
    QSize tam_b(b.width() + b.x(),b.height() + b.y());
    return tam_a.expandedTo(tam_b);}
