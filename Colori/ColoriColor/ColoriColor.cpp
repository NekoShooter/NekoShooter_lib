#include "ColoriColor.h"
#include "GitiBits.h"
#include "ColoriBasic.h"
#include "__COLORICONST__.h"
#include "ColoriMath.h"


ColoriColor::ColoriColor():Colori_rgb(){asignarFamilia(true);}
ColoriColor::ColoriColor(const Colori_rgb &_rgb): Colori_rgb(_rgb.info()){asignarFamilia(true);}
ColoriColor::ColoriColor(const unsigned long long &id_o_info):Colori_rgb(id_o_info){asignarFamilia(true);}
ColoriColor::ColoriColor(const c_rgb &_RGB):Colori_rgb(_RGB){asignarFamilia(true);}
ColoriColor::ColoriColor(const unsigned short &r,const unsigned short &g,const unsigned short &b,const unsigned short &a)
    :Colori_rgb(r,g,b,a){asignarFamilia(true);}
ColoriColor::~ColoriColor(){
    if(local) delete local;
    if(tmp) delete tmp;
    if(respaldo) delete respaldo;
    if(circulo) delete []circulo;}



ColoriColor::ColoriColor(const std::string &hex){
    asignarFamilia(true);
    cambiarHexa(hex);}



void ColoriColor::cambiarHexa(std::string hex){
    unsigned long long res_id = this->info();
    unsigned int id;
    long id_a = 0xff;


    if (hex.size() <= 4 && hex.size() > 2)
        id = css_a_int(hex.c_str());

    else if (hex.size() <= 7 && hex.size() > 5)
        id = hex_a_int(hex.c_str());

    else if (hex.size() <= 9 && hex.size() > 7){
        char _alfa[3];
        _alfa[2]= '\0';
        _alfa[1]= hex[hex.size() - 1];
        _alfa[0]= hex[hex.size() - 2];
        id_a = hexAint(_alfa);
        if(id_a == COLORI_ERROR) return;
        hex.resize(hex.length() - 2);
        id = hexAint(hex.c_str());}
    else return;
    if(id > BLANCO) return;
    Colori_rgb::cambiarID_A(id | (id_a << 24));
    if(res_id != this->info()) aligerar();}



void ColoriColor::aligerar(bool limpiar_completamente){
    excepciones excepcion = NINGUNO;
    if(!limpiar_completamente) excepcion = salvar_a;
    limpiarhex();
    if(local){if(!(excepcion & LOCAL)){delete local;}}
    if(respaldo) {if(!(excepcion & RESPALDO)){delete respaldo;}}
    if(circulo) {if(!(excepcion & CIRCULO)){delete [] circulo;}}
    if(!(excepcion & LOCAL)){local = nullptr;}
    if(!(excepcion & RESPALDO)){respaldo = nullptr;}
    if(!(excepcion & CIRCULO)){circulo = nullptr;}
    liberartmp();}



void ColoriColor::restablecer(){
    if(respaldo) cambiarInfo(respaldo->info());
    salvar_a = NINGUNO;
    aligerar();}

void ColoriColor::liberartmp(){
    if(tmp) delete tmp;
    tmp = nullptr;}

const ColoriColor * ColoriColor::CirculoCromatico(unsigned short parte_de_circulo, coloriMOD estilo, coloriMOD Modo){
    if(esNull() || parte_de_circulo > todo || estilo > MOD_RGB|| Modo < MOD_UNITARIO) return nullptr;
    if(parte_de_circulo == base) return this;
    if(cambioRealizado()|| modo_de_composicion != estilo)aligerar(false);

    if(parte_de_circulo != todo && Modo == MOD_UNITARIO){
        liberartmp();
        tmp = new ColoriColor;
        c_rgb *crgb_temp = nullptr;
        crgb_temp = circulo_cromatico(this->crgb(),(coloridx)parte_de_circulo ,(uChar)estilo);
        *tmp = *crgb_temp;
        liberar(crgb_temp);
        return tmp;}
    if(!circulo){
        modo_de_composicion = estilo;
        circulo = new ColoriColor[11];
        c_rgb *crgb_temp = nullptr;
        for(short i = 0; i < 11; ++i){
            crgb_temp = circulo_cromatico(this->crgb(),(coloridx)(i+1),(uChar)estilo);
            circulo[i].cambiarC_rgb(*crgb_temp);
            liberar(crgb_temp);}}
    if(parte_de_circulo == todo) return circulo;
    return &circulo[parte_de_circulo - 1];}


void ColoriColor::cambiarBrillo(double nivel_de_brillo){
    if(nivel_de_brillo > 1 || -1 > nivel_de_brillo || nivel_de_brillo == 0) return;
    if(!respaldo) respaldo = new ColoriColor(this->info());
    c_rgb *res = nuevo_rgb(1);
    if(nivel_de_brillo > 0)
        brillo_y_sombra(this->crgb(),res,nullptr,nivel_de_brillo,0);
    else
        brillo_y_sombra(this->crgb(),nullptr,res,0,(nivel_de_brillo * -1));
    cambiarC_rgb(*res);
    liberar(res);}



void ColoriColor::operator = (const c_rgb &_rgb){
    cambiarC_rgb(_rgb);
    if(cambioRealizado()) {salvar_a = NINGUNO; aligerar(false);}}


void ColoriColor::operator = (const unsigned long long &info){
    if(info <= BLANCO) cambiarID(info);
    else if (info <= COLOR_MAX) cambiarID_A(info);
    else cambiarInfo(info);
    if(cambioRealizado()){salvar_a = NINGUNO; aligerar(false);}}


ColoriColor& ColoriColor::operator+(const ColoriColor &ColorA){
    if(this->id() == ColorA.id()) return *this;
    if(local && data == ColorA.id())
        return *local;
    if(!local) local = new ColoriColor;
    c_rgb *res = mezclar_colores(this->crgb(),ColorA.crgb());
    *local = *res;
    liberar(res);
    data = local->info();
    return *local;}

ColoriColor& ColoriColor::operator ++(){
    if(!respaldo) respaldo = new ColoriColor(this->info());
    cambiarBrillo(.10);
    if(cambioRealizado()){salvar_a = RESPALDO; aligerar(false);};
    return *this;}

ColoriColor& ColoriColor::operator --(){
    if(!respaldo) respaldo = new ColoriColor(this->info());
    cambiarBrillo(-.10);
    if(cambioRealizado()){salvar_a = RESPALDO; aligerar(false);};
    return *this;}
