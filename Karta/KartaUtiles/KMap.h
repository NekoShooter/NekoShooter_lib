#ifndef KMAP_H
#define KMAP_H
#include "__GITICONST__.h"
#include "HRango.h"
#include <QImage>
class QPoint;
//class QSize;
//class QImage;
struct kbool{ bool on: 1; }__attribute__((packed));

class KMap
    {
    public:
        KMap(){__inicializar();}
        ~KMap(){Limpiar();}
        KMap(const QSize &tam);
        KMap(const QRect &rect);
        KMap(cShort &x, cShort &y, cuShort &w, cuShort &h);
        KMap(const QPoint &coordenada, const QSize & tam);

        void ReDimencionar(cShort &x, cShort &y, cuShort &w, cuShort &h);
        void Unir(const KMap &map);
        KMap Union(const KMap &map);
        void Intersectar(const KMap &map);
        KMap Interseccion(const KMap &map);

        void Optimizar();
        void Limpiar();



        void Marcar(cShort &x, cShort &y);
        void Marcar(const QPoint &coordenada);

        void DesMarcar(cShort &x, cShort &y);
        void DesMarcar(const QPoint &p);

        bool Marcado(cShort &x, cShort &y);
        bool Marcado(const QPoint &p);

        cShort & x()const {return __xPos;}
        cShort & y()const {return __yPos;}
        QPoint Pos() const;

        QSize Tam();
        QRect Rect();

        QSize TamTotal();
        QRect RectTotal();

        inline void Transladar(cShort &x, cShort &y){__xPos += x; __xPos += y;}
        inline void CambiarPos(cShort &x, cShort &y){ __xPos = x; __yPos = y;}
        inline cuShort &NumMarcas() const {return __numMarcas;}
        inline bool estaVacio() const{ return !__numMarcas;}
        inline bool esNulo() const{return !__map;}

        uShort begin();
        inline cuShort &end() const {return __numMarcas;}
        QPoint iterator();


        short xBegin() const{return __x.min();}
        short xEnd()   const{return __x.max();}
        short yBegin() const{return __y.min();}
        short yEnd()   const{return __y.max();}
        QPoint Coor(cShort &indexX, cShort &indexY)const{return  QPoint(indexX + __xPos, indexY + __yPos);}

        const kbool * const* maya() const{return __map;}


    private:
        kbool **__map;
        HRango <short> __x,__y;
        uShort __numMarcas;
        short __xPos, __yPos;
        short __w, __h;
        kbool **__mapa(cuInt &largo, cuInt &alto);

        void __borraMap();
        void __inicializar();
        short __copiar(kbool ** nuevo, cShort &x, cShort &y, cuShort &w, cuShort &h);

        // Zona Iteradora
        int * iter_x, * iter_y, * iter_contador;
        bool iter_iniciado;
        void __iter_borrado();
};

#endif // KMAP_H
