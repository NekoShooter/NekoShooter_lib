#ifndef __HNotificador
#define __HNotificador


class HNotificador{
    public:
        HNotificador(){__notificacion = false;}
        HNotificador(bool activar){__notificacion = activar;}

        bool estado();
        const bool &contenido() const {return __notificacion;}

        void operator =(bool activar) {__notificacion = activar;}
        bool operator ==(HNotificador &HN);
        bool operator !=(HNotificador &HN);
        bool operator ||(HNotificador &HN);
        bool operator &&(HNotificador &HN);
        void operator <<(HNotificador &HN){__notificacion = HN.estado();}

        bool operator ==(const bool &condicion);
        bool operator !=(const bool &condicion);
        bool operator ||(const bool &condicion){ return estado() || condicion;}
        bool operator &&(const bool &condicion);

        bool operator !() const{ return !__notificacion;}
        const bool &operator ()() const{ return __notificacion;}

    private:
        bool __notificacion;
    };

#endif // __HNotificador
