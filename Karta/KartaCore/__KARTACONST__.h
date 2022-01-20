#ifndef __KARTACONST___H
#define __KARTACONST___H

#define KARTA_ERROR -1
#define ANGULO_VALIDO(ang) (ang > 0 && 360 > ang)
#define ANGULO_ERRONEO(ang)(ang < 0 || ang > 360)


namespace Karta {
typedef enum Sentido {Horario, Anti_horario, Radial } Sentido;
typedef enum Modo { Absoluto, Relativo ,Global, Exclusivo}Modo;
typedef enum orientacion{Horizontal, Vertical, Libre}orientacion;

}
#endif // __KARTACONST___H
