#ifndef __KTimon
#define __KTimon
#include "__GITICONST__.h"

class QMatrix;
class QSize;
class QWidget;
class QPoint;
class QPointF;
class QImage;
class QRect;
class QMouseEvent;


class KTimon
{
public:
    KTimon(){__Inicializar();}
    ~KTimon();

    KTimon(const QSize &tamBase, const QSize &tam);
    KTimon(const QSize &tamBase, const QSize &tam, const QPoint &posicion);
    KTimon(const QSize &tamBase, const QRect &rect);
    KTimon(const QSize &tamBase,const QImage &img);
    KTimon(const QSize &tamBase,const QImage &img, const QPoint &posicion);
    KTimon(QMatrix *&matrix,const QSize &tamBase, const QSize &tam);
    KTimon(QMatrix *&matrix,const QSize &tamBase, const QSize &tam, const QPoint &posicion);
    KTimon(QMatrix *&matrix,const QSize &tamBase, const QRect &rect);
    KTimon(QMatrix *&matrix,const QSize &tamBase, const QImage &img);
    KTimon(QMatrix *&matrix,const QSize &tamBase, const QImage &img, const QPoint &posicion);

    void CambiarParametros(QMatrix *&matrix,const QSize &tamBase, const QSize &tam, const QPoint &posicion);
    void CambiarParametros(QMatrix *&matrix,const QSize &tamBase, const QImage &img, const QPoint &posicion);
    void CambiarParametros(QMatrix *&matrix,const QSize &tamBase, const QRect &rect);

    void Zoom(cDouble &zoom);
    void Rotar(cDouble & grados);
    void Navegar(cDouble &moverEnX, cDouble &moverEnY, cDouble & zoom, cDouble & grados);

    void MoverEnX(cDouble &moverEnX);
    void MoverEnY(cDouble &moverEnY);
    void Mover(cDouble &moverEnX,cDouble &moverEnY);

    void Actualizar();

    void ReIniciar();
    void ReIniciarRotacion();
    void ReIniciarNevegacion();
    void ReIniciarZoom();

    void CambiarPosicion(const QPoint &posicion);
    void CambiarPosicion(const QPointF &posicion);
    void CambiarTam(const QSize &tam);
    void CambiarTamBase(const QSize &tam);
    void CambiarQMatrix(const QMatrix &matrix);
    void AdoptarQMatrix(QMatrix *&matrix);


    void mousePressEvent(QMouseEvent *event, const bool &rotacionActiva = false);
    void mouseMoveEventZoom(QMouseEvent *event, cDouble &distanciaFocal = .01);
    void mouseMoveEventRotar(QMouseEvent *event);
    void mouseMoveEventMover(QMouseEvent *event);

    inline void AnclarZoom()      {__zoomAncla   = __zoom;}
    inline void AnclarRotacion()  {__gradosAncla = __grados;
                                   __angInicial  = 0;}
    inline void AnclarMovimiento(){__movXAncla   = __movX;
                                   __movYAncla   = __movY;}
    void Anclar();

    inline cDouble &DameZoom() const {return __zoom;}
    inline cDouble &DameMovX() const {return __movX;}
    inline cDouble &DameMovY() const {return __movY;}
    inline cDouble &DameAngulosDeRotacion() const {return __grados;}
    inline const QSize *DameTam() const {return  __tam;}
    inline QMatrix * pDameQMatrix() {return __qmatrix;}
    inline const QMatrix *DameQMatrix() const {return __qmatrix;}
    inline bool EsQMatrixPropio() const {return  !__qmatrix_autogenerada;}

private:
    bool      __estaVacio;

    QMatrix * __qmatrix,
            * __qmatrix_autogenerada,
            * __qmatrixTemp;

    QSize   * __tam,
            * __tamBase;

    QPointF * __posicion;
    QPoint  * __puntoAncla;

    double   __movX,   __movXAncla,
             __movY,   __movYAncla,
             __zoom,   __zoomAncla,
             __grados, __gradosAncla, __angInicial;

    void __Inicializar();
    void __NuevoQMatrix();
    void __BorrarQMatrix();
};

#endif // __KTimon
