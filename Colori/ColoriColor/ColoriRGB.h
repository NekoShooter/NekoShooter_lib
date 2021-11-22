#ifndef __ColoriRGB
#define __ColoriRGB

#include "Colori__rgb__.h"

class Colori_rgb
{
    public:
        Colori_rgb();
        Colori_rgb(const unsigned long long &Info);
        Colori_rgb(const unsigned short &r, const unsigned short &g, const unsigned short &b,const unsigned short &a=0xff);
        Colori_rgb(const c_rgb &RGB);
        virtual ~Colori_rgb();

        void cambiarRGBA(const unsigned short &r, const unsigned short &g, const unsigned short &b,const unsigned short &a);
        void cambiarRGB(const unsigned short &r,const unsigned short &g,const unsigned short &b);
        void cambiarID(const unsigned int &ID_Color);
        void cambiarID_A(const unsigned int &ID_A_Color);
        void cambiarInfo(const unsigned long long &Info);
        void cambiarR(const unsigned short &r);
        void cambiarG(const unsigned short &g);
        void cambiarB(const unsigned short &b);
        void cambiarA(const unsigned short &a);
        void cambiarC_rgb(const c_rgb &_rgb);

        inline bool esNull() const {return RGB == nullptr;};

        const char* html_a();
        const char* html();
        const char* css();

        inline unsigned int id()            const {return !esNull() ? RGB->id : 0;};
        inline unsigned int id_a()          const {return !esNull() ? (RGB->id << 8) | RGB->rgb[_A_]: 0;};
        inline unsigned long long info()    const {return !esNull() ? RGB->info : 0;};
        inline unsigned short r()           const {return !esNull() ? RGB->rgb[_R_] : 0;};
        inline unsigned short g()           const {return !esNull() ? RGB->rgb[_G_] : 0;};
        inline unsigned short b()           const {return !esNull() ? RGB->rgb[_B_] : 0;};
        inline unsigned short a()           const {return !esNull() ? RGB->rgb[_A_] : 0;};
        inline unsigned char famila()       const {return !esNull() ? RGB->rgb[_F_] : 0;};
        inline const c_rgb * crgb()         const {return RGB;};

        void asignarFamilia(bool);
        const char* tipo() const;

    protected:
        char *hex;
        void limpiarhex();
        bool cambioRealizado(bool hecho = false);


    private:
        c_rgb * RGB;
        bool cambioAinfo;
        bool identificar;

        void inicializar();
        void limpiar();
        void asignarMemoria();
        void __cambio(const unsigned char &rgb,const unsigned short &valor);


};

#endif //__ColoriRGB
