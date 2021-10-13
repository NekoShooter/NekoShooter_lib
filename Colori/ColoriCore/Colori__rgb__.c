#include "Colori__rgb__.h"
#include "ColoriMath.h"
#include <stdlib.h>
//#include <stdio.h>


c_rgb *nuevo_rgb(short tam){
    if (tam < 0) return Nulo;
    c_rgb * nuevo = (c_rgb *) malloc(sizeof(c_rgb)* tam);
    return  nuevo;}

void liberar(c_rgb *rgb_aEliminar){
    if(rgb_aEliminar == Nulo) return;
    free(rgb_aEliminar);}


c_rgb *complemento(const c_rgb *original ,uChar estilo){
    if(!original||(estilo != RGB_Style && estilo != RYB_Style)) return Nulo;
    if(estilo == RGB_Style) return inverso(original);

    c_rgb * inver = Nulo;
    c_rgb * temp = Nulo;
    c_rgb *compl = Nulo;

    switch (original->rgb[_F_]) {
        case C_VERDE: case C_PISTACHO:
            return tercio(original,DERECHA);

       case C_ROJO:
            return  tercio(original,IZQUIERDA);

        case C_MORADO: case C_PURPURA:
            temp = tercio(original,DERECHA);
            inver = tercio(original,IZQUIERDA);
            compl = nuevo_rgb(1);

            uChar MP_max, Am_max,
                  MP_min, Am_min,
                  MP_med, Am_med;

            rgbSort(original,&MP_max, &MP_med, &MP_min);
            rgbSort(inver,&Am_max, &Am_med, &Am_min);
            if(MP_max < 128){

                if(((inver->rgb[Am_med] / 2) + original->rgb[MP_max]) > 0xff)
                     compl->rgb[_R_] = 0xff;
                else compl->rgb[_R_] = (inver->rgb[Am_med] / 2) + original->rgb[MP_max];
                if(( inver->rgb[Am_max] +(original->rgb[MP_med] / 2)) > 0xff)
                     compl->rgb[_G_] = 0xff;
                else compl->rgb[_G_] = inver->rgb[Am_max] +(original->rgb[MP_med] / 2);

                compl->rgb[_B_] = (inver->rgb[Am_min] + original->rgb[MP_min]) / 2;}

            else{

                for(uChar i= 0; i < 3; ++i){
                    if(i == _B_)
                        compl->rgb[i] = (temp->rgb[i] + inver->rgb[i]) / CONST_ARTE;
                    else{

                        if(temp->rgb[i] < inver->rgb[i])
                            inver->rgb[i] = inver->rgb[i] / CONST_ARTE;
                        else temp->rgb[i] = temp->rgb[i] / CONST_ARTE;

                        if(temp->rgb[i] + inver->rgb[i] > 0xff)
                            compl->rgb[i] = 0xff;
                        else
                            compl->rgb[i] = temp->rgb[i] + inver->rgb[i];}}}
            liberar(temp);
            liberar(inver);
            compl->rgb[_F_] = C_AMARILLO;
            return compl; // fin case C_MORADO, C_PURPURA

        default:
            inver = inverso(original);
            if(original->id < inver->id)
                temp = tercio(inver,IZQUIERDA);

            else
                temp = tercio(inver,DERECHA);
            break;} // fin switch


    if (  original->rgb[_F_] != C_ROJO && original->rgb[_F_] != C_MORADO
       && original->rgb[_F_] != C_PURPURA){
        compl = suma_de_color(original,temp,CENTRO);
        convertir_a_inverso(compl);}
    else if(original->rgb[_F_] != C_MORADO && original->rgb[_F_] != C_PURPURA)
        compl = suma_de_color(temp,inver,CENTRO);

    liberar(temp);
    liberar(inver);
    return compl;}



c_rgb *adyasente(const c_rgb *original, coloridx posicion,uChar estilo){
    if(!original||(estilo != RGB_Style && estilo != RYB_Style)) return Nulo;

    c_rgb *temp = Nulo;
    c_rgb *temp2 = Nulo;
    c_rgb *ColorAdy = Nulo;

    switch(posicion){
        case adyasenteDER:
            switch (original->rgb[_F_] + estilo){
                case C_AZUL:
                    return inverso(original);
                case C_VERDE: case C_PISTACHO:
                    temp = sexto(original,DERECHA);
                    temp2 = tercio(original,DERECHA);
                    ColorAdy = suma_de_color(temp,temp2,CENTRO);
                    break;
                case C_AMARILLO:
                    return sexto(original,DERECHA);
                default:
                    return tercio(original,DERECHA);}
            break;

        case adyasenteIZQ:
            switch (original->rgb[_F_] + estilo) {
                case C_ROJO:
                    return sexto(original,IZQUIERDA);
                case C_VERDE: case C_PISTACHO:
                    temp = tercio(original,IZQUIERDA);
                    temp2 = inverso(original);
                    ColorAdy = suma_de_color(temp,temp2,CENTRO);
                    break;
                case C_AMARILLO:
                    return inverso(original);
                default:
                    return tercio(original,IZQUIERDA);}
            break;

        default:
            return Nulo;}
    liberar(temp2);
    liberar(temp);
    return ColorAdy;}




c_rgb *contiguo(const c_rgb *original, coloridx posicion, uChar estilo){

    if(!original||(estilo != RGB_Style && estilo != RYB_Style)) return Nulo;
    c_rgb *temp = Nulo;
    c_rgb *temp2 = Nulo;
    c_rgb *ColorCon = Nulo;

    switch (posicion) {
        case contiguoDER:
            switch (original->rgb[_F_] + estilo) {
                case C_ROJO:
                    temp = sexto(original,DERECHA);
                    temp2 = tercio(original,DERECHA);
                    ColorCon = suma_de_color(temp,temp2,CENTRO);
                    break;
                case C_AZUL:
                    return tercio(original,DERECHA);

                case C_AMARILLO:
                    temp = sexto(original,DERECHA);
                    ColorCon = suma_de_color(original,temp,CENTRO);
                    break;
                default:
                    return sexto(original,DERECHA);}
            break;
        case contiguoIZQ:
            switch (original->rgb[_F_] + estilo) {
                case C_ROJO:
                    temp = sexto(original,IZQUIERDA);
                    ColorCon = suma_de_color(temp,original,CENTRO);
                    break;

                case C_VERDE: case C_PISTACHO:
                    return tercio(original,IZQUIERDA);

                case C_OCRE: case C_NARANJA:
                    ColorCon = complemento(original,estilo);
                    convertir_a_inverso(ColorCon);
                    return ColorCon;

                default:
                    return sexto(original,IZQUIERDA);}
            break;
        default:
            return Nulo;}


    liberar(temp);
    liberar(temp2);
    return ColorCon;}



c_rgb *circulo_cromatico(const c_rgb *rgb_original, coloridx seccion, uChar estilo){
    if(!rgb_original ||(estilo != RGB_Style && estilo != RYB_Style)) return Nulo;
    c_rgb *origen     = Nulo;
    c_rgb *destino    = Nulo;
    c_rgb *nuevoColor = Nulo;

    switch (seccion) {
        case ter_bcDER:
            destino = contiguo(rgb_original,contiguoDER ,estilo);
            nuevoColor = suma_de_color(rgb_original,destino,CENTRO);
            break;
        case contiguoDER:
            return contiguo(rgb_original,contiguoDER,estilo);
        case ter_caDER:
            origen = contiguo(rgb_original,contiguoDER,estilo);
            destino = adyasente(rgb_original,adyasenteDER,estilo);
            nuevoColor = suma_de_color(origen,destino,CENTRO);
            break;
        case adyasenteDER:
            return adyasente(rgb_original,adyasenteDER,estilo);
        case ter_aoDER:
            origen = adyasente(rgb_original,adyasenteDER,estilo);
            destino = complemento(rgb_original,estilo);
            nuevoColor = suma_de_color(origen,destino,CENTRO);
            break;
        case opuesto:
            return complemento(rgb_original,estilo);
        case ter_oaIZQ:
            origen = complemento(rgb_original,estilo);
            destino = adyasente(rgb_original,adyasenteIZQ,estilo);
            nuevoColor = suma_de_color(origen,destino,CENTRO);
            break;
        case adyasenteIZQ:
            return adyasente(rgb_original,adyasenteIZQ,estilo);
        case ter_acIZQ:
            origen = adyasente(rgb_original,adyasenteIZQ,estilo);
            destino = contiguo(rgb_original,contiguoIZQ,estilo);
            nuevoColor = suma_de_color(origen, destino,CENTRO);
            break;
        case contiguoIZQ:
            return contiguo(rgb_original,contiguoIZQ,estilo);
        case ter_cbIZQ:
            origen = contiguo(rgb_original,contiguoIZQ,estilo);
            nuevoColor = suma_de_color(origen, rgb_original,CENTRO);
            break;
        default: return Nulo;}

    liberar(origen);
    liberar(destino);
    return  nuevoColor;}




c_rgb *mezclar_colores(const c_rgb *ColorA, const c_rgb *ColorB){
    if(!ColorA || !ColorB) return Nulo;

    if(ColorA->rgb[_F_] == C_NONE || ColorB->rgb[_F_] == C_NONE)
        return suma_de_color(ColorA,ColorB,CENTRO);
    c_rgb * resultado = Nulo;
    c_rgb * temp = Nulo;
    c_rgb * temp2 = Nulo;
    uChar a = ColorA->rgb[_F_];
    uChar b = ColorB->rgb[_F_];

    if((a == C_AMARILLO && b <= C_TURQUESA)||(a <= C_TURQUESA && b == C_AMARILLO)){

        temp = tercio(a==C_AMARILLO? ColorA : ColorB,DERECHA);
        temp2 = sexto(b<=C_TURQUESA? ColorB : ColorA,IZQUIERDA);
        resultado = suma_de_color(temp,temp2,CENTRO);
        convertir_a_inverso(resultado);}

    else if (((a<= C_OCRE && b <= C_TURQUESA) ||(a<= C_TURQUESA&& b <= C_OCRE))
           && (a > C_AMARILLO || b > C_AMARILLO)) {
        temp = sexto(b<=C_TURQUESA? ColorB : ColorA,IZQUIERDA);
        resultado = suma_de_color(a<=C_OCRE? ColorB : ColorA,temp,CENTRO);}
    else
        resultado = suma_de_color(ColorA,ColorB,CENTRO);

    resultado->rgb[_A_] = (ColorA->rgb[_A_] + ColorB->rgb[_A_]) /2;


    liberar(temp);
    liberar(temp2);
    buscar_familia(resultado);
    return resultado;}

