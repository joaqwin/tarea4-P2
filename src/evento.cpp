#include "../include/evento.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////

struct rep_evento {
    int id;
    TFecha fecha;
    char descripcion[MAX_DESCRIPCION];
};

TEvento crearTEvento(int id, const char descripcion[MAX_DESCRIPCION], TFecha fecha) {
    TEvento nuevoEvento = NULL;
    nuevoEvento = new rep_evento;
    nuevoEvento->id = id;
    strcpy(nuevoEvento->descripcion, descripcion);
    nuevoEvento->fecha = fecha;

    return nuevoEvento;
}

void imprimirTEvento(TEvento evento) {
    printf("Evento %d: %s\n",evento->id,evento->descripcion);
    printf("Fecha: ");
    imprimirTFecha(evento->fecha);
}

void liberarTEvento(TEvento &evento) {
    liberarTFecha(evento->fecha);
    delete evento;
    evento = NULL;
}

int idTEvento(TEvento evento) {
    int res = 0;
    res = evento->id;
    return res;
}

TFecha fechaTEvento(TEvento evento) {
    TFecha fecha = NULL;
    fecha = evento->fecha;
    return fecha;
}

void posponerTEvento(TEvento &evento, int dias) {
    aumentarTFecha(evento->fecha, dias);
}

/////////////////////////////////
////// FIN CÓDIGO TAREA 1 //////
/////////////////////////////////

/*-----------------------------*/

///////////////////////////
////// FUNCION NUEVA //////
///////////////////////////

// Retorna una copia del evento
TEvento copiarTEvento(TEvento evento) {
    TEvento copiaEvento = NULL;
    copiaEvento = new rep_evento;
    copiaEvento->id = evento->id;
    strcpy(copiaEvento->descripcion, evento->descripcion);
    TFecha copiaFecha = copiarTFecha(evento->fecha);
    copiaEvento->fecha = copiaFecha;
    return copiaEvento; 
}

/////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
/////////////////////////////////
