#ifndef __AnskyMath
#define __AnskyMath
#include <QList>
#include "__GITICONST__.h"

QList<QPointF> Generar_triangulo(const QRect & rec);
QList<QPointF> Generar_triangulo(const QPointF &posicion,cDouble &base, cDouble &altura);
QList<QPointF> Generar_triangulo(const QPoint &posicion,cDouble &base, cDouble &altura);
QList<QPointF> Generar_triangulo(cDouble &pos_x, cDouble &pos_y, cDouble &base, cDouble &altura);

QList<QPointF> Generar_trianguloRec(const QRect &rec);
QList<QPointF> Generar_trianguloRec(const QPointF &posicion,cDouble &base, cDouble &altura);
QList<QPointF> Generar_trianguloRec(const QPoint &posicion,cDouble &base, cDouble &altura);
QList<QPointF> Generar_trianguloRec(cDouble &pos_x, cDouble &pos_y, cDouble &base, cDouble &altura);

void rotarQPoints(QList<QPoint> *lista, const QPoint &ancla, cDouble &ang);
void rotarQPointFs(QList<QPointF> *lista,const QPointF &ancla, cDouble &ang);
#endif // __AnskyMath
