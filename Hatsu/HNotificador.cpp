#include "HNotificador.h"

bool HNotificador::estado(){
    bool tm = __notificacion;
    __notificacion = false;
    return tm;}

bool HNotificador::operator ==(HNotificador &HN){
    if(__notificacion == HN.contenido()){
        return estado() == HN.estado();}
    return false;}

bool HNotificador::operator !=(HNotificador &HN){
    if(__notificacion != HN.contenido())
        return estado() != HN.estado();
    return false;}

bool HNotificador::operator ||(HNotificador &HN){
    if(__notificacion || HN.contenido()){
        HN = __notificacion = false;
        return true;}
    return false;}

bool HNotificador::operator &&(HNotificador &HN){
    if(__notificacion && HN.contenido())
        return estado() && HN.estado();
    return false;}

bool HNotificador::operator ==(const bool &condicion){
    if(__notificacion == condicion)
        return estado() == condicion;
    return false;}


bool HNotificador::operator !=(const bool &condicion){
    if(__notificacion != condicion)
        return estado() != condicion;
    return false;}

bool HNotificador::operator &&(const bool &condicion){
    if(__notificacion && condicion)
        return estado() && condicion;
    return false;}
