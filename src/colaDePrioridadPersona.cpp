#include "../include/colaDePrioridadPersona.h"
#include "../include/utils.h"
#include "../include/evento.h"

struct rep_colaDePrioridadPersona {
  TPersona* array;
  TFecha* esta;
  nat tope;
  nat max;
  bool invertido;
};

TColaDePrioridadPersona crearCP(nat N) {
  TColaDePrioridadPersona nuevo = new rep_colaDePrioridadPersona;
  nuevo->tope = 0;
  nuevo->max = N;
  nuevo->invertido = false;
  nuevo->array = new TPersona[N+1];
  for(nat i = 1; i<=N; i++){
    nuevo->array[i] = NULL;
  }
  nuevo->esta = new TFecha[N+1];
  for(nat j = 1; j<= N; j++){
    nuevo->esta[j] = NULL;
  }
  return nuevo;
}

void invertirPrioridad(TColaDePrioridadPersona &cp) {
  for(nat i = 1; i < cp->tope; i++){
    TPersona min = cp->array[1];
    cp->array[1] = cp->array[cp->tope - i + 1];
    cp->array[cp->tope - i + 1] = min;
    //filtrado_descendente_recursivo(cp->array, 1);
  }
}

void liberarCP(TColaDePrioridadPersona &cp) {
  for(nat i = 1; i<=cp->tope; i++){
    liberarTPersona(cp->array[i]);
  }
  delete[] cp->esta;
  delete[] cp->array;
  delete cp;
  cp = NULL;
}

TFecha obtenerFechaPrioridad(TPersona persona){
  return fechaTEvento(primerEventoDeTPersona(persona));
}

void filtrado_ascendente(nat pos, TColaDePrioridadPersona &cp){
  TPersona swap = cp->array[pos];
  while((pos > 1) && (compararTFechas(obtenerFechaPrioridad(cp->array[pos / 2]), obtenerFechaPrioridad(swap))) == 1){
    cp->array[pos] = cp->array[pos/2];
    pos = pos/2;
  }
  cp->array[pos] = swap;
}

void insertarEnCP(TPersona persona, TColaDePrioridadPersona &cp) {
  if(cp->tope != cp->max){
    cp->tope++;
    cp->array[cp->tope] = persona;
    cp->esta[idTPersona(persona)] = obtenerFechaPrioridad(persona);
    if((cp->tope != 1) && (compararTFechas(obtenerFechaPrioridad(cp->array[cp->tope/2]),obtenerFechaPrioridad(persona)) == 1)){
      filtrado_ascendente(cp->tope, cp);
    }
  }
}

bool estaVaciaCP(TColaDePrioridadPersona cp) {
  return cp->tope == 0;
}

TPersona prioritaria(TColaDePrioridadPersona cp) {
  return cp->array[1];
}

void filtrado_descendente(nat pos, TColaDePrioridadPersona &cp){
  TPersona swap = cp->array[pos];
  while(2*pos <= cp->tope){
    nat hijo = 2*pos;
    if((hijo + 1 <= cp->tope) && cp->array[hijo+1] < cp->array[hijo]){
      hijo = hijo + 1;
    }
    if(compararTFechas(obtenerFechaPrioridad(cp->array[hijo]), obtenerFechaPrioridad(swap)) == -1){
      cp->array[pos] = cp->array[hijo];
      pos = hijo;
    }else{
      break;
    }
  }
  cp->array[pos] = swap;
}

void filtrado_descendente_recursivo(nat pos, TColaDePrioridadPersona &cp){
  if(pos*2 <= cp->tope){
    nat hijo = 2*pos;
    if((hijo + 1 <= cp->tope) && (compararTFechas(obtenerFechaPrioridad(cp->array[hijo + 1]), obtenerFechaPrioridad(cp->array[hijo])) == -1)){
      hijo++;
    }
    if(compararTFechas(obtenerFechaPrioridad(cp->array[hijo]), obtenerFechaPrioridad(cp->array[pos])) == -1){
      TPersona swap = cp->array[pos];
      cp->array[pos] = cp->array[hijo];
      cp->array[hijo] = swap;
      filtrado_descendente_recursivo(hijo, cp);
    }
  }
}

void eliminarPrioritaria(TColaDePrioridadPersona &cp) {
  if(cp->tope > 0){
    cp->esta[idTPersona(cp->array[1])] = NULL;
    liberarTPersona(cp->array[1]);
    cp->array[1] = cp->array[cp->tope];
    cp->tope--;
    if(cp->tope > 0){
      //filtrado_descendente(1, cp);
      filtrado_descendente_recursivo(1, cp);
    }
  }
}

bool estaEnCP(nat id, TColaDePrioridadPersona cp) {
  if(id < 1 || id > cp->max){
    return false;
  }
  return cp->esta[id] != NULL;
}

TFecha prioridad(nat id, TColaDePrioridadPersona cp){
  return cp->esta[id];
}