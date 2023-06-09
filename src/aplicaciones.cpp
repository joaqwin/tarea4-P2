#include "../include/aplicaciones.h"
#include "../include/colaDePrioridadPersona.h"

void listarEnOrden(TTablaPersonas t, char** nombres, nat n){
    TColaDePrioridadPersona cola = crearCP(n);
    for(nat i = 0; i<n; i++){
        if(perteneceATTablaPersonas(t, nombres[i])){
            TPersona copia = copiarTPersona(obtenerPersonaDeTTablaPersonas(t, nombres[i]));
            insertarEnCP(copia, cola);
        }
    }
    while(!estaVaciaCP(cola)){
        imprimirTPersona(prioritaria(cola));
        eliminarPrioritaria(cola);
    }
    liberarCP(cola);
}