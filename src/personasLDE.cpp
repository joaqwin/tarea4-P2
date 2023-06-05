#include "../include/personasLDE.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////

struct nodoPersona {
    TPersona persona;
    nodoPersona *sig;
    nodoPersona *ant;
};


struct rep_personasLDE {
    nodoPersona *ini;
    nodoPersona *fin;
    nat cantidad;
};


typedef struct nodoPersona *nodo;



TPersonasLDE crearTPersonasLDE(){
    TPersonasLDE LDEpersona = new rep_personasLDE;
    LDEpersona->ini = NULL;
    LDEpersona->fin = NULL;
    LDEpersona->cantidad = 0;
    return LDEpersona;
}

void insertarTPersonasLDE(TPersonasLDE &personas, TPersona persona, nat pos){
    nodo personaAux = new nodoPersona;
    personaAux->persona = persona;
    if(personas->ini ==NULL){
        personas->ini = personaAux;
        personas->fin = personaAux;
        personaAux->sig = NULL;
        personaAux->ant = NULL;
        personas->cantidad++;        
    }else if(pos == 1){
        personaAux->sig = personas->ini;
        personaAux->ant = NULL;
        personas->ini->ant = personaAux;
        personas->ini = personaAux;
        personas->cantidad++;
    }else if(pos > personas->cantidad){
        personaAux->sig = NULL;
        personaAux->ant = personas->fin;
        personas->fin->sig = personaAux;
        personas->fin = personaAux;
        personas->cantidad++;
    }else{
        nodo iter = personas->ini;
        for (nat i = 1; i<pos-1; i++){
            iter = iter->sig;
        }
        personaAux->sig = iter->sig;
        personaAux->ant = iter;
        iter->sig->ant = personaAux;
        iter->sig = personaAux;
        personas->cantidad++;
    }
}

void liberarTPersonasLDE(TPersonasLDE &personasLDE){
    if(personasLDE->ini != NULL){
        nodo iter = personasLDE->ini;
        while(iter != NULL){
            nodo aux = iter;
            iter = iter->sig;
            liberarTPersona(aux->persona);
            delete aux;
            aux = NULL;
            personasLDE->cantidad--;
        }
        personasLDE->ini = NULL;
        personasLDE->fin = NULL;
    }
    delete personasLDE;
    personasLDE = NULL;
}

void imprimirTPersonasLDE(TPersonasLDE personas){
    nodo iter = personas->ini;
    while(iter != NULL){
        imprimirTPersona(iter->persona);
        iter = iter->sig;
    }
}

nat cantidadTPersonasLDE(TPersonasLDE personas){
    return personas->cantidad;
}

void eliminarInicioTPersonasLDE(TPersonasLDE &personas){
    if(personas->ini != NULL){
        if(personas->ini == personas->fin){
            liberarTPersona(personas->ini->persona);
            delete personas->ini;
            personas->ini = NULL;
            personas->fin = NULL;
            personas->cantidad--;   
        }else{
            personas->ini = personas->ini->sig;
            liberarTPersona(personas->ini->ant->persona);
            delete personas->ini->ant;
            personas->ini->ant = NULL;
            personas->cantidad--;
        }
    }
}

void eliminarFinalTPersonasLDE(TPersonasLDE &personas){
    if(personas->ini != NULL){
        if(personas->ini == personas->fin){
            liberarTPersona(personas->ini->persona);
            delete personas->ini;
            personas->ini = NULL;
            personas->fin = NULL;
            personas->cantidad--;
        }else{
            personas->fin = personas->fin->ant;
            liberarTPersona(personas->fin->sig->persona);
            delete personas->fin->sig;
            personas->fin->sig = NULL;
            personas->cantidad--;
        }
    }
}

bool estaEnTPersonasLDE(TPersonasLDE personas, nat id){
    nodo iter = personas->ini;
    while((iter != NULL) && (idTPersona(iter->persona) != id)){
        iter = iter->sig;
    }
    return (iter != NULL);
}

TPersona obtenerDeTPersonasLDE(TPersonasLDE personas, nat id){
    nodo iter = personas->ini;
    while((iter != NULL) && (idTPersona(iter->persona) != id)){
        iter = iter->sig;
    }
    return (iter->persona);
}

TPersonasLDE concatenarTPersonasLDE(TPersonasLDE personas1, TPersonasLDE personas2){
    if((personas1->ini == NULL) && (personas2->ini == NULL)){
        return NULL;
    }else if((personas1->ini != NULL) && (personas2->ini == NULL)){
        delete personas2;
        return personas1;
    }else if((personas2->ini != NULL) && (personas1->ini == NULL)){
        delete personas1;
        return personas2;
    }else{
        personas1->fin->sig = personas2->ini;
        personas2->ini->ant = personas1->fin;
        personas1->fin = personas2->fin;
        personas1->cantidad = personas1->cantidad + personas2->cantidad;
        personas2->cantidad = personas1->cantidad + personas2->cantidad;
        delete personas2;
        return personas1;
    }
}

///////////////////////////////////
////// FIN CÓDIGO TAREA 2 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void insertarInicioDeTPersonasLDE(TPersonasLDE &personas, TPersona persona){
    nodo nuevo = new nodoPersona;
    nuevo->persona = persona;
    nuevo->sig = personas->ini;
    nuevo->ant = NULL;
    personas->cantidad++;
    if(personas->ini == NULL){
        personas->ini = nuevo;
        personas->fin = nuevo;
    }else{
        personas->ini->ant = nuevo;
        personas->ini = nuevo;
    }
}

void insertarFinalDeTPersonasLDE(TPersonasLDE &personas, TPersona persona){    
    nodo nuevo = new nodoPersona;
    nuevo->persona = persona;
    nuevo->ant = personas->fin;
    nuevo->sig = NULL;
    personas->cantidad++;
    if(personas->ini == NULL){
        personas->ini = nuevo;
        personas->fin = nuevo;
    }else{
        personas->fin->sig = nuevo;
        personas->fin = nuevo;
    }
}

TPersona obtenerInicioDeTPersonasLDE(TPersonasLDE personas){
    return personas->ini->persona;
}

TPersona obtenerFinalDeTPersonasLDE(TPersonasLDE personas){
    return personas->fin->persona;
}


///////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void eliminarPersonaConNombreTPersonasLDE(TPersonasLDE &personas, const char nombre[100]){
    nodo iter = personas->ini;
    while((iter != NULL) && (strcmp(nombre, nombreTPersona(iter->persona)) != 0 )){
        iter = iter->sig;
    }
    if(iter->ant == NULL){
        eliminarInicioTPersonasLDE(personas);
    }else if(iter->sig == NULL){
        eliminarFinalTPersonasLDE(personas);
    }else{
        liberarTPersona(iter->persona);
        iter->ant->sig = iter->sig;
        iter->sig->ant = iter->ant;
        personas->cantidad--;
        delete iter;
        iter = NULL;
    }
}

bool estaPersonaConNombreEnTPersonasLDE(TPersonasLDE personas, const char nombre[100]){
    nodo iter = personas->ini;
    while((iter != NULL) && (strcmp(nombre, nombreTPersona(iter->persona)) != 0 )){
        iter = iter->sig;
    }
    return iter != NULL;
}

TPersona obtenerPersonaConNombreTPersonasLDE(TPersonasLDE personas, const char nombre[100]){
    nodo iter = personas->ini;
    while((iter != NULL) && (strcmp(nombre, nombreTPersona(iter->persona)) != 0 )){
        iter = iter->sig;
    }
    return iter->persona;
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

