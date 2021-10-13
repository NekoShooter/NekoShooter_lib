/*CONST COLORI : constantes definidas para el uso en la libreria
               general Colori*/
#ifndef __COLORICONST__
#define __COLORICONST__
#define COLOR_MAX 0xffffffff
#define MAX_ID 0x17000000000
#define BLANCO 0xffffff
#define NEGRO 0
#define RGB_Style 0x17
#define RYB_Style 0x0


#define CONST_ARTE 2.0

#define CENTRO 0
#define DERECHA 1
#define IZQUIERDA 2
#define ROTAR 3

#define COLORI_ERROR -1
#define COLORI_OK 1


enum coloriFamilia{
     C_NONE = 0x0,     C_NEUTRO   =0x14, C_NEGRO     =0x15, C_BLANCO  = 0x16,

     C_AZUL     = 0x1, C_JADE     = 0x7, C_NARANJA   = 0xc, C_MAGENTA = 0x11,
     C_INDIGO   = 0x2, C_VERDE    = 0x8, C_OCRE      = 0xd, C_MORADO  = 0x12,
     C_TURQUESA = 0x3, C_PISTACHO = 0x9, C_ROJO      = 0xe, C_PURPURA = 0x13,
     C_CYAN     = 0x5, C_OLIVO    = 0xa, C_ROSA      = 0xf,
     C_AQUA     = 0x6, C_AMARILLO = 0xb, C_ESCARLATA = 0x10};
/*
enum coloriFamilia{
     C_NONE = 0x0,      C_NEGRO    = 0x8,  C_BLANCO  = 0xF,

     C_VIOLETA  = 0x11, C_JADE     = 0x12, C_OCRE    = 0x24, C_MORADO = 0x41,
     C_AZUL     = 0x1 , C_VERDE    = 0x2,  C_NARANJA = 0x22, C_MAGENTA =0x5,
     C_TURQUESA = 0x21, C_OLIVO    = 0x42, C_ROJO    = 0x4,  C_NEUTRO = 0x7,
     C_CYAN     = 0x3,  C_AMARILLO = 0x6,  C_ROSA    = 0x14, C_ESCARLATA = 0x66,
     C_INDIGO   = 0x77, C_PURPURA  = 0x88, C_AQUA    = 0x99, C_PISTACHO = 0xaa};*/


enum coloridx {base         = 0x0,   opuesto      = 0x6, todo = 0xc,
               ter_bcDER    = 0x1,   ter_oaIZQ    = 0x7,
               contiguoDER  = 0x2,   adyasenteIZQ = 0x8,
               ter_caDER    = 0x3,   ter_acIZQ    = 0x9,
               adyasenteDER = 0x4,   contiguoIZQ  = 0xa,
               ter_aoDER    = 0x5,   ter_cbIZQ    = 0xb};



typedef enum coloridx coloridx;
typedef enum coloriFamilia coloriFamilia;

#endif // __COLORICONST__
