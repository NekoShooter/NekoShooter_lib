#include "ColoriMath.h"

short dividir_tono(short Tono, short *Claro, short *Oscuro,double Nivel_Brillo, double Nivel_Oscuro){
    if(Tono < NEGRO || Claro == Nulo || Oscuro == Nulo|| Nivel_Brillo < 0x0 || Nivel_Oscuro < 0x0)
        return  COLORI_ERROR;
    //unidad del 1% del color
    #define Unidad 2.55
    double ProporcionTonoClaro = (255.0 - (double)Tono)/Unidad;
    *Claro = (((double)Tono) + ((ProporcionTonoClaro * Nivel_Brillo)*Unidad))+.5;

    if(*Claro > 0xff) *Claro = 0xff;

    double ProporcionTonoOscuro =  (((double)Tono) / Unidad);
    *Oscuro = (((double)Tono) - (ProporcionTonoOscuro *Nivel_Oscuro)*Unidad)+.5;

    if(*Oscuro < 0x0) *Oscuro = 0x0;
    return COLORI_OK;}


/*******************************************/



short brillo_y_sombra(const c_rgb *Color, c_rgb *Brillo,c_rgb *Sombra,double Nivel_Brillo, double Nivel_Oscuro){
    if(Color == Nulo) return COLORI_ERROR;

    short B_rgb , S_rgb;
    unsigned char i;

    for(i = 0; i < 3; ++i){
        if(dividir_tono(Color->rgb[i], &B_rgb, &S_rgb,Nivel_Brillo,Nivel_Oscuro) != COLORI_ERROR){
            if(Brillo) Brillo->rgb[i] = B_rgb;
            if(Sombra) Sombra->rgb[i] = S_rgb;}
        else {
            if(Brillo) Brillo->id = BLANCO;
            if(Sombra) Sombra->id = NEGRO;
            return  COLORI_ERROR;}}
    return  COLORI_OK;}



/******************************************/



c_rgb *suma_de_color(const c_rgb * origen,const c_rgb * destino,short desplazamiento){

    if(origen == Nulo || destino == Nulo || desplazamiento < 0) return Nulo;

     c_rgb * ColorC = nuevo_rgb(1);

    unsigned char ra,ga,ba,
                  rb,gb,bb;
    switch (desplazamiento) {
        case DERECHA:   ra = _B_; ga = _R_; ba = _G_;
                        rb = _G_; gb = _B_; bb = _R_; break;

        case IZQUIERDA: ra = _G_; ga = _B_; ba = _R_;
                        rb = _B_; gb = _R_; bb = _G_; break;

        case CENTRO:    ra = _R_; ga = _G_; ba = _B_;
                        rb = _R_; gb = _G_; bb = _B_; break;

        default:        liberar(ColorC);
                        return Nulo;}

    ColorC->rgb[_R_] = (origen->rgb[ra] + destino->rgb[rb])/ CONST_ARTE;
    ColorC->rgb[_G_] = (origen->rgb[ga] + destino->rgb[gb])/ CONST_ARTE;
    ColorC->rgb[_B_] = (origen->rgb[ba] + destino->rgb[bb])/ CONST_ARTE;

    if(desplazamiento != CENTRO)
        convertir_a_inverso(ColorC);
    return ColorC;}


/*******************************************/

c_rgb *inverso(const c_rgb *original){
    if(!original) return Nulo;
    c_rgb *inv = nuevo_rgb(1);
    inv->id = original->id;
    convertir_a_inverso(inv);
    return inv;}

/**/

void convertir_a_inverso(c_rgb *original){
    if(!original) return;
    c_rgb inv = {BLANCO - original->id};
    *original = nivelacion_luminica(original,&inv);}

/**/

c_rgb nivelacion_luminica(const c_rgb *ColorOriginal,const c_rgb *ColorBase){
    unsigned char MAX_A, MAX_B, i;

    MAX_A = ColorOriginal->rgb[_R_];
    MAX_B = ColorBase ->rgb[_R_];

    for(i = 0; i < 3; ++i){
        if(MAX_A < ColorOriginal->rgb[i]) MAX_A = ColorOriginal->rgb[i];
        if(MAX_B < ColorBase ->rgb[i])    MAX_B = ColorBase ->rgb[i];}

    return nivel_de_luminicencia(*ColorBase, MAX_A - MAX_B);}


/**/


c_rgb nivel_de_luminicencia(c_rgb Color,short intencidad){
    unsigned char i = 0;

    for(;i < 3; ++i){

        if (Color.rgb[i] + intencidad < 0)
            Color.rgb[i] = 0;
        else if (Color.rgb[i] + intencidad > 0xff)
            Color.rgb[i] = 0xff;
        else
            Color.rgb[i] = Color.rgb[i] + intencidad;}

    return Color;}


/********************************************/



void mover_rgb(c_rgb *crgb, uChar tipo_de_movimiento){
    if(!crgb) return;
    uChar R = crgb->rgb[_R_];

    switch(tipo_de_movimiento){
        case DERECHA:
            crgb->rgb[_R_] = crgb->rgb[_G_];
            crgb->rgb[_G_] = crgb->rgb[_B_];
            crgb->rgb[_B_] = R;
            break;
        case IZQUIERDA:
            crgb->rgb[_R_] = crgb->rgb[_B_];
            crgb->rgb[_B_] = crgb->rgb[_G_];
            crgb->rgb[_G_] = R;
            break;
        case ROTAR:
            crgb->rgb[_R_] = crgb->rgb[_B_];
            crgb->rgb[_B_] = R;
            break;
    default:
        return;}}


/**/


c_rgb *tercio(const c_rgb *original,uChar orientacion){
    if(!original) return Nulo;

    c_rgb *nuevoColor = nuevo_rgb(1);
    nuevoColor->id = original->id;

    switch(orientacion){
        case DERECHA:
            mover_rgb(nuevoColor,DERECHA);
            return nuevoColor;
        case IZQUIERDA:
            mover_rgb(nuevoColor,IZQUIERDA);
            return nuevoColor;
        default:
            liberar(nuevoColor);
            return Nulo; }}

/**/

c_rgb *sexto(const c_rgb *original,uChar orientacion){
    if(!original) return Nulo;
    c_rgb * nuevoColor;

    switch (orientacion) {
        case DERECHA:
            nuevoColor = tercio(original,IZQUIERDA);
            break;
        case IZQUIERDA:
            nuevoColor = tercio(original,DERECHA);
            break;
        default: return Nulo;}

    convertir_a_inverso(nuevoColor);
    return nuevoColor;}


/***********************************************/


void buscar_familia(c_rgb * _rgb_){
    if(_rgb_ == Nulo) return;

    if(_rgb_->id == BLANCO){
        _rgb_->rgb[_F_] = C_BLANCO;
        return;}

    else if(_rgb_->id == NEGRO){
        _rgb_->rgb[_F_] = C_NEGRO;
        return;}

    uChar idx_max,
          idx_min,
          idx_med;

    _rgb_->rgb[_F_] = rgbSort(_rgb_,&idx_max, &idx_med, &idx_min);

    if(_rgb_->rgb[_F_] == C_NEUTRO) return;
    if(_rgb_->rgb[idx_med] == _rgb_->rgb[idx_min]) return;
    if(purezaRGB(_rgb_)) return;

    coloriFamilia desendiente_menor,
                  desendiente_medio,
                  desendiente_mayor;

    switch (idx_max) {
        case _R_:
            if(idx_med == _G_){
                desendiente_menor = C_OCRE;
                desendiente_medio = C_NARANJA;
                desendiente_mayor = C_AMARILLO;}
            else{//  _B_
                desendiente_menor = C_ESCARLATA;
                desendiente_medio = C_ROSA;
                desendiente_mayor = C_MAGENTA;}
            break;

        case _G_:
            if(idx_med == _B_){
                desendiente_menor = C_AQUA;
                desendiente_medio = C_JADE;
                desendiente_mayor = C_CYAN;}
            else{//  _R_
                desendiente_menor = C_OLIVO;
                desendiente_medio = C_PISTACHO;
                desendiente_mayor = C_AMARILLO;}
            break;

        case _B_:
            if(idx_med == _R_){
                desendiente_menor = C_MORADO;
                desendiente_medio = C_PURPURA;
                desendiente_mayor = C_MAGENTA;}
            else{//  _G_
                desendiente_menor = C_INDIGO;
                desendiente_medio = C_TURQUESA;
                desendiente_mayor = C_CYAN;}
            break;

    default:break;}



    uChar LIM_MAX, LIM_MIN;
    definir_limite_ascendente(_rgb_->rgb[idx_med],&LIM_MIN,&LIM_MAX);
    /*** mod ** limite desendete ********/
    if(LIM_MAX >= _rgb_->rgb[idx_min] && LIM_MIN < _rgb_->rgb[idx_min]){
        definir_limite_ascendente(_rgb_->rgb[idx_max],&LIM_MIN,&LIM_MAX);
        /*** mod ** limite desendete ********/

        if(LIM_MAX >= _rgb_->rgb[idx_med] && LIM_MIN < _rgb_->rgb[idx_med]){
            _rgb_->rgb[_F_] = desendiente_menor;
            return;}}

     definir_limite_ascendente(_rgb_->rgb[idx_max],&LIM_MIN,&LIM_MAX);

     if(LIM_MAX >= _rgb_->rgb[idx_med] && LIM_MIN < _rgb_->rgb[idx_med])
         _rgb_->rgb[_F_] = desendiente_medio;
     else if(LIM_MAX < _rgb_->rgb[idx_med])
         _rgb_->rgb[_F_] = desendiente_mayor;}


/****************************************/

coloriFamilia rgbSort(const c_rgb * Crgb,uChar* idx_max, uChar *idx_med, uChar * idx_min){
    uChar max = 0, idx;
    uChar min = 0xff;
    coloriFamilia familia_dominante[3];
    familia_dominante[_R_] = C_ROJO;
    familia_dominante[_G_] = C_VERDE;
    familia_dominante[_B_] = C_AZUL;

    for(idx = 0; idx < 3; ++idx){

        if (max < Crgb->rgb[idx]){
            max = Crgb->rgb[idx];
            *idx_max = idx;}

        if (min > Crgb->rgb[idx]){
            min = Crgb->rgb[idx];
            *idx_min = idx;}}

    if(Crgb->rgb[*idx_max] == Crgb->rgb[*idx_min]){
        *idx_max = _R_;
        *idx_med = _G_;
        *idx_min = _B_;
        return C_NEUTRO;}

    else
        *idx_med = 3 - (*idx_max + *idx_min);

    return  familia_dominante[*idx_max];}

/*********************************************/


void definir_limite_ascendente(uShort refencia, uChar *limite_min, uChar *limite_max){
    uChar der4bits, izq4bits;

    der4bits = aBytes(&refencia,4);
    izq4bits = refencia;

    if (izq4bits != 0){

        if(izq4bits == 1){
            *limite_max = ((izq4bits - 1) << 4) | (der4bits - 1);
            *limite_min = der4bits / 2;}
        else if (2 < izq4bits && der4bits > 1){
            *limite_max = ((izq4bits - 2) << 4) | der4bits;
            *limite_min = (((izq4bits - 2) / 2) << 4) | der4bits;}
        else {           /******mod*******/
            *limite_max = (izq4bits  << 4) | der4bits;
            *limite_min = der4bits;}}


    else if (der4bits > 1){
        *limite_max = der4bits - 1;
        *limite_min = *limite_max / 2;}

    else *limite_max = *limite_min  = 0;}


/*********************************************/

void definir_limite_desendente(uShort refencia, uChar *limite_min, uChar *limite_max){
    uChar porcentaje_min,  der4bits,
          porcentaje_max,  izq4bits;

    der4bits = aBytes(&refencia,4);
    izq4bits = refencia;

    porcentaje_max = ((izq4bits * 100)/ 0xf) *33;
    porcentaje_min = ((der4bits * 100)/ 0xf) *33;

    *limite_min = der4bits - (porcentaje_min * 2);
    *limite_max = der4bits | ((izq4bits - porcentaje_max) << 4);}
                /* der4bits */

coloriFamilia purezaRGB(const c_rgb *original){
    if(!original) return C_NONE;
    uChar idx_max, familia,
          idx_min,
          idx_med;

    familia = rgbSort(original,&idx_max, &idx_med, &idx_min);
    float porcentaje = original->rgb[idx_max]/100;
    if(original->rgb[idx_med] <= porcentaje * 30 && original->rgb[idx_min] <= porcentaje * 30)
        return familia;
    return C_NONE;}
