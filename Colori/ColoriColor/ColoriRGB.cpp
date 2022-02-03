#include "ColoriRGB.h"
#include "ColoriBasic.h"
#include "__COLORICONST__.h"
#include "ColoriMath.h"

Colori_rgb::Colori_rgb(){ inicializar();}

Colori_rgb::~Colori_rgb(){ if(RGB) delete RGB; if(hex) delete[] hex;}

void Colori_rgb::inicializar(){
    RGB = nullptr;
    hex = nullptr;
    identificar = false;}

void Colori_rgb::limpiar(){
    delete RGB;
    RGB = nullptr;
    if(hex) delete[] hex;
    hex = nullptr;}

void Colori_rgb::asignarMemoria(){
    RGB = new c_rgb;
    RGB->rgb[_A_] = 0xff;
    RGB->info = C_NONE;}

void Colori_rgb::asignarFamilia(bool asignar){
    identificar = asignar;
    if(identificar && !esNull() && RGB->rgb[_F_] == C_NONE) buscar_familia(RGB);}


Colori_rgb::Colori_rgb(const unsigned long long &Info){
    inicializar();
    if(Info > COLOR_MAX) cambiarInfo(Info);
    else cambiarID(Info);}

Colori_rgb::Colori_rgb(const unsigned short &r, const unsigned short &g, const unsigned short &b, const unsigned short &a){
    inicializar();
    cambiarID_A((a<<24) | rgb_a_int(r,g,b));}

Colori_rgb::Colori_rgb(const c_rgb &_RGB){
    inicializar();
    cambiarInfo(_RGB.info);}

void Colori_rgb::cambiarRGBA(const unsigned short &r, const unsigned short &g, const unsigned short &b, const unsigned short &a){
    cambiarID_A((a << 24) | rgb_a_int(r,g,b));}

void Colori_rgb::cambiarRGB(const unsigned short &r,const unsigned short &g,const unsigned short &b){
    cambiarID(rgb_a_int(r,g,b));}

void Colori_rgb::cambiarC_rgb(const c_rgb &_rgb){
    cambiarInfo(_rgb.info);}


void Colori_rgb::cambiarID(const unsigned int &ID_Color){
    if(esNull()) asignarMemoria();
    if(ID_Color > BLANCO) return;
    if(RGB->id == ID_Color) return;
    RGB->id = ID_Color;
    if(identificar)buscar_familia(RGB);
    cambioRealizado(true);}

void Colori_rgb::cambiarID_A(const unsigned int &ID_A_Color){
    if(esNull()) asignarMemoria();
    if(ID_A_Color > COLOR_MAX) return;
    if(RGB->id == ((ID_A_Color << 8) >> 8)){
        if(RGB->rgb[_A_] == (ID_A_Color >> 24)) return;
           RGB->rgb[_A_] =  (ID_A_Color >> 24); return;}
    RGB->id_a = ID_A_Color;
    if(identificar)buscar_familia(RGB);
    cambioRealizado(true);}

void Colori_rgb::cambiarInfo(const unsigned long long &Info){
    if(Info >= MAX_ID) return;
    if(esNull()) asignarMemoria();
    if(RGB->info == Info) return;
    RGB->info = Info;
    if(identificar) buscar_familia(RGB);
    cambioRealizado(true);}

void Colori_rgb::cambiarR(const unsigned short &r){
    __cambio(_R_,r);}

void Colori_rgb::cambiarG(const unsigned short &g){
    __cambio(_G_,g);}

void Colori_rgb::cambiarB(const unsigned short &b){
    __cambio(_B_,b);}

void Colori_rgb::cambiarA(const unsigned short &a){
    __cambio(_A_,a);}

void Colori_rgb::__cambio(const unsigned char &rgb, const unsigned short &valor){
    if(valor > 0xff) return;
    if(esNull()) asignarMemoria();
    if(RGB->rgb[rgb] == valor) return;
    RGB->rgb[rgb] = valor;
    if(identificar)buscar_familia(RGB);
    cambioRealizado(true);}

const char* Colori_rgb::html_a(){
    if(esNull()) return "#00000000";
    hex = new char[10];
    int_a_hex(RGB->id_a,hex,10);
    return hex;}


const char* Colori_rgb::html(){
    if(esNull()) return "#000000";
    limpiarhex();
    hex = new char[8];
    int_a_hex(RGB->id,hex,8);
    return hex;}

const char* Colori_rgb::css(){
    if(esNull()) return "#000";
    limpiarhex();
    hex = new char[4];
    int_a_css(RGB->id,hex);
    return hex;}

void Colori_rgb::limpiarhex(){
    if(hex != nullptr){
        delete[] hex;
        hex = nullptr;}}

bool Colori_rgb::cambioRealizado(bool hecho){
    bool cambio = cambioAinfo;
    cambioAinfo = hecho;
    return cambio;}

const char* Colori_rgb::tipo() const{
    if(esNull()) return "None";
    switch (RGB->rgb[_F_]) {
        case C_NEGRO:    return "Negro";
        case C_BLANCO:   return "Blanco";
        case C_NEUTRO:   return "Gris";
        case C_PURPURA:  return "Purpura";
        case C_AZUL:     return "Azul";
        case C_INDIGO:   return "Azul Indigo";
        case C_TURQUESA: return "Turquesa";
        case C_CYAN:     return "Cyan";
        case C_AQUA:     return "Aqua";
        case C_JADE:     return "Jade";
        case C_VERDE:    return "Verde";
        case C_OLIVO:    return "Verde Olivo";
        case C_PISTACHO: return "Verde Pistacho";
        case C_OCRE:     return "Ocre";
        case C_AMARILLO: return "Amarillo";
        case C_NARANJA:  return "Naranja";
        case C_ROJO:     return "Rojo";
        case C_ROSA:     return "Rosa";
        case C_ESCARLATA:return "Escarlata";
        case C_MORADO:   return "Morado";
        case C_MAGENTA:  return "Magenta";
        default:         return "None";}}
