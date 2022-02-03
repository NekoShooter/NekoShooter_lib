#ifndef __KArea
#define __KArea

class QSize;
class QPoint;
class QRect;

class KArea
{
public:
    KArea(){}
    KArea(const QSize &tam);

    void Agregar(const QPoint &punto);
    void AgregarPx(const short &x);
    void AgregarPy(const short &y);

    void Reiniciar(const QSize &tam);

    QRect rect()   const;
    QSize size()   const;
    QPoint point() const;

    inline bool EsValido() const {return !(__infX >= __supX || __infY >= __supY);}

    inline const short &xi() const {return __infX;}
    inline const short &xs() const {return __supX;}
    inline const short &yi() const {return __infY;}
    inline const short &ys() const {return __supX;}



private:
    short __infX = 0, __supX = 0,
          __infY = 0, __supY = 0;

    bool  __estaVacio = true;};

#endif // __KArea
