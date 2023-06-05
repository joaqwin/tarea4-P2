#include "../include/agendaLS.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////

struct rep_agendaLS {
    TEvento evento;
    TAgendaLS sig;
};

TAgendaLS crearAgendaLS() {
    TAgendaLS nuevaAgenda = NULL;
    return nuevaAgenda;
}

void agregarEnAgendaLS(TAgendaLS &agenda, TEvento evento) {
    /*TAgendaLS nodo = new rep_agendaLS;
    nodo->evento = evento;
    nodo->sig = NULL;
    if(agenda == NULL){
        agenda = nodo;
    }else{
        TAgendaLS iter = agenda;
        while((iter->sig != NULL) && (compararTFechas(fechaTEvento(iter->evento), fechaTEvento(evento)) == 1)){
            iter = iter->sig;
        }
        if(iter->sig == NULL){
            iter->sig = nodo;
        }else{
            nodo->sig = iter->sig;
            iter->sig = nodo;
        } 
    }*/
    TAgendaLS nuevo = new rep_agendaLS;
    nuevo->evento = evento;
    if(agenda == NULL || !(compararTFechas(fechaTEvento(agenda->evento), fechaTEvento(evento)) == -1)){
        nuevo->sig = agenda;
        agenda = nuevo;
    }else{
        TAgendaLS iter = agenda;
        int contador = 0;
        while((iter->sig != NULL) && (compararTFechas(fechaTEvento(iter->sig->evento), fechaTEvento(evento)) == -1)){
            iter = iter->sig;
            contador++;
        }
        if(iter->sig == NULL){
            if (contador == 0){
                if(compararTFechas(fechaTEvento(evento), fechaTEvento(iter->evento)) == 1){
                    nuevo->sig = iter->sig;
                    iter->sig = nuevo;
                }else{
                    nuevo->sig = iter;
                    agenda = nuevo;
                }
            }else{
                nuevo->sig = iter->sig;
                iter->sig = nuevo;
            }
        }else{
            nuevo->sig = iter->sig;
            iter->sig = nuevo;
        }
    }
}


void imprimirAgendaLS(TAgendaLS agenda) {
    TAgendaLS p = agenda;
    while(p != NULL){
        imprimirTEvento(p->evento);
        p = p->sig;
    }
}

void liberarAgendaLS(TAgendaLS &agenda) {
    if (agenda != NULL){
        while(agenda != NULL){
            TAgendaLS aux = agenda;
            agenda = agenda->sig;
            liberarTEvento(aux->evento);
            delete aux;
            aux = NULL;
        }
        agenda = NULL;
        //liberarTEvento(iter->evento);
        //delete iter;
        //iter = NULL;
    }
}

bool esVaciaAgendaLS(TAgendaLS agenda){
    return (agenda == NULL);
}

TAgendaLS copiarAgendaLS(TAgendaLS agenda){
    TAgendaLS copia = NULL;
    if(esVaciaAgendaLS(agenda)){
        return copia;
    }else{
        copia = new rep_agendaLS;
        copia->evento = copiarTEvento(agenda->evento);
        copia->sig = NULL;
        TAgendaLS ult = copia;
        agenda = agenda->sig;
        while(agenda != NULL){
            TAgendaLS aux = new rep_agendaLS;
            aux->evento = copiarTEvento(agenda->evento);
            ult->sig = aux;
            ult = ult->sig;
            agenda = agenda->sig;
        }
        ult->sig = NULL;
    }
    return copia;
}


bool estaEnAgendaLS(TAgendaLS agenda, int id) {
    bool res = false;
    if(!esVaciaAgendaLS(agenda)){
        TAgendaLS iter = agenda;
        while((iter != NULL) && (idTEvento(iter->evento) != id)){
            iter = iter->sig;
        }
        res = (iter != NULL);
    }
    return res;
}

TEvento obtenerDeAgendaLS(TAgendaLS agenda, int id) {
    TEvento res = NULL;
    if(estaEnAgendaLS(agenda, id)){
        TAgendaLS iter = agenda;
        while((idTEvento(iter->evento) != id)){
            iter = iter->sig;
        }
        res = iter->evento;
    }
    return res;
}

void posponerEnAgendaLS(TAgendaLS &agenda, int id, nat n) {
    if(!esVaciaAgendaLS(agenda)){
        if(agenda->sig == NULL){
            TEvento obtener = obtenerDeAgendaLS(agenda, id);
            posponerTEvento(obtener, n);
        }else{
            TAgendaLS iter = agenda;
            TAgendaLS aux;
            TAgendaLS aux2;
            bool flag = false;
            if((idTEvento(iter->evento) == id)){
                aux = iter;
                flag = true;
            }else{
                while((idTEvento(iter->sig->evento) != id)){
                    iter = iter->sig;
                }
                aux = iter->sig;
                aux2 = iter;
                iter = iter->sig;
            }
            //TAgendaLS aux = iter->sig;
            //TAgendaLS aux2 = iter;
            posponerTEvento(aux->evento, n);
            if((aux->sig != NULL) && (compararTFechas(fechaTEvento(aux->sig->evento), fechaTEvento(aux->evento)) == -1)){
                if(flag){
                    agenda = aux->sig;
                }else{
                    aux2->sig = aux->sig;
                }
                while(iter->sig != NULL && (compararTFechas(fechaTEvento(iter->sig->evento), fechaTEvento(aux->evento)) == -1)){
                    iter = iter->sig;
                } 
                aux->sig = iter->sig;
                iter->sig = aux;
            }
        }
    }
}

void imprimirEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
    TAgendaLS p = agenda;
    while(p != NULL){
        if(compararTFechas(fechaTEvento(p->evento), fecha) == 0){
            imprimirTEvento(p->evento);
        }
        p = p->sig;
    }
}

bool hayEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
    bool res = false;
    TAgendaLS p = agenda;
    while((p != NULL) && compararTFechas(fechaTEvento(p->evento), fecha) != 0){
        p = p->sig;
    }
    res = (p != NULL);
    return res;
}

void removerDeAgendaLS(TAgendaLS &agenda, int id) {
    if(agenda->sig == NULL){
        liberarTEvento(agenda->evento);
        delete agenda;
        agenda = NULL;
    }else{
        TAgendaLS iter = agenda;
        if((idTEvento(iter->evento) == id)){
            liberarTEvento(iter->evento);
            agenda = iter->sig;
            delete iter;
            iter = NULL;
        }else{
            while( (idTEvento(iter->sig->evento) != id) ){
                iter = iter->sig;
            }
            TAgendaLS aux = iter->sig;
            iter->sig = aux->sig;
            liberarTEvento(aux->evento);
            delete aux;
            aux = NULL;
        }
    }
}

///////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

TEvento primerEventoAgendaLS(TAgendaLS agenda){
    return agenda->evento;
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////