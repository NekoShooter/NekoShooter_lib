/* COLORI COLOR: una variable contenedora */

#ifndef __ColoriColor
#define __ColoriColor
#include "ColoriRGB.h"
#include <iostream>

class ColoriColor : public Colori_rgb{
    public:
        ColoriColor();
        ColoriColor(const c_rgb &_rgb);
        ColoriColor(const Colori_rgb &_rgb);
        ColoriColor(const unsigned long long &id_o_info);
        ColoriColor(const unsigned short &r,const unsigned short &g,const unsigned short &b,const unsigned short &a = 0xff);
        ColoriColor(const std::string &hex);
        virtual ~ColoriColor();

        enum coloriMOD{MOD_RYB = RYB_Style, MOD_RGB = RGB_Style, MOD_UNITARIO = 0x18,MOD_FULL = 0x19};


        void cambiarHexa(std::string hex);
        void aligerar(bool limpiar_completamente = true);
        void restablecer();
        void cambiarBrillo(double nivel_de_brillo);
        const ColoriColor * CirculoCromatico(unsigned short parte_de_circulo, coloriMOD estilo = MOD_RYB, coloriMOD Modo = MOD_FULL);


    private:
        enum excepciones{NINGUNO =0x1,LOCAL = 0x2, RESPALDO = 0x4, CIRCULO = 0x8};
        void liberartmp();

        excepciones salvar_a = NINGUNO;
        coloriMOD modo_de_composicion = MOD_RYB;
        ColoriColor *circulo = nullptr;
        ColoriColor *respaldo = nullptr;
        ColoriColor *local = nullptr;
        ColoriColor *tmp = nullptr;
        uInt data = COLOR_MAX;



    public:
        ColoriColor& operator +(const ColoriColor &ColorB);
        void operator = (const std::string &hex){cambiarHexa(hex);}
        void operator = (const c_rgb &_rgb);
        void operator = (const unsigned long long &info);

        bool operator ==(const Colori_rgb &_rgb)const{return info() == _rgb.info();};
        bool operator !=(const Colori_rgb &_rgb)const{return info() != _rgb.info();};

        bool operator ==(const c_rgb &_rgb)const {return info() == _rgb.info;};
        bool operator !=(const c_rgb &_rgb)const {return info() != _rgb.info;};

        bool operator ==(const ColoriColor &ColorB) const {return info() == ColorB.info();};
        bool operator !=(const ColoriColor &ColorB)const {return info() != ColorB.info();};

        bool operator ==(const unsigned long long &Info)const{return info() == Info;};
        bool operator !=(const unsigned long long &Info)const{return info() != Info;};

        ColoriColor& operator ++();
        ColoriColor& operator --();
};

#endif // __ColoriColor
