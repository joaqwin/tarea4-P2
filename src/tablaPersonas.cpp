#include "../include/tablaPersonas.h"

struct rep_tablaPersonas {
    TPersonasLDE* tabla;
    int cantidad;
    int max;
};

nat funcionDeDispersion(const char nombre[100]){
    nat res = 0;
    int i = 0;
    while(i< 100 && nombre[i] != '\0'){
        res += int(nombre[i]);
        i++;
    }
    return res;
}

TTablaPersonas crearTTablaPersonas(int max){
    TTablaPersonas nuevo = new rep_tablaPersonas;
    nuevo->tabla = new TPersonasLDE[max];
    nuevo->cantidad = 0;
    nuevo->max = max;
    for(int i=0; i<max; i++){
        nuevo->tabla[i] = NULL;
    }
    return nuevo;
}

void insertarPersonaEnTabla(TTablaPersonas &tabla, TPersona persona){
    nat pos = funcionDeDispersion(nombreTPersona(persona)) % tabla->max;
    if(tabla->tabla[pos] == NULL){
        tabla->tabla[pos] = crearTPersonasLDE();
    }
    insertarInicioDeTPersonasLDE(tabla->tabla[pos], persona);
    tabla->cantidad++;
}


void eliminarPersonaDeTTablaPersonas(TTablaPersonas &tabla, const char nombre[100]){
    nat pos = funcionDeDispersion(nombre) % tabla->max;
    if(tabla->tabla[pos] != NULL){
        eliminarPersonaConNombreTPersonasLDE(tabla->tabla[pos], nombre);
    }
}

bool perteneceATTablaPersonas(TTablaPersonas tabla, const char nombre[100]){
    nat pos = funcionDeDispersion(nombre) % tabla->max;
    bool res = false;
    if(tabla->tabla[pos] != NULL){
        res = estaPersonaConNombreEnTPersonasLDE(tabla->tabla[pos], nombre);
    }
    return res;
}

TPersona obtenerPersonaDeTTablaPersonas(TTablaPersonas tabla, const char nombre[100]){
    nat pos = funcionDeDispersion(nombre) % tabla->max;
    TPersona res = NULL;
    if(tabla->tabla[pos] != NULL){
        res = obtenerPersonaConNombreTPersonasLDE(tabla->tabla[pos], nombre);
    }
    return res;
}


void liberarTTablaPersonas(TTablaPersonas &tabla){
    tabla->cantidad = 0;
    for(int i = 0; i<tabla->max; i++){
        if(tabla->tabla[i] != NULL){
            liberarTPersonasLDE(tabla->tabla[i]);
            tabla->tabla[i] = NULL;
        }
    }
    delete[] tabla->tabla;
    delete tabla;
    tabla = NULL;
}


void imprimirTTablaPersonas(TTablaPersonas tabla){
    for(int i=0; i<tabla->max; i++){
        if(tabla->tabla[i] != NULL){
            imprimirTPersonasLDE(tabla->tabla[i]);
        }
    }
}