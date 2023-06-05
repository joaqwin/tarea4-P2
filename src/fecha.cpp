#include "../include/fecha.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////
struct rep_fecha {
    nat dia, mes, anio;
};

TFecha crearTFecha(nat dia, nat mes, nat anio) {
    TFecha nuevaFecha = NULL;
    nuevaFecha = new rep_fecha;
    nuevaFecha->dia = dia;
    nuevaFecha->mes = mes;
    nuevaFecha->anio = anio;
    return nuevaFecha;
}

void liberarTFecha(TFecha &fecha) {
    delete fecha;
    fecha = NULL;
}

void imprimirTFecha(TFecha fecha) {
    printf("%d/%d/%d\n", fecha->dia,fecha->mes,fecha->anio);
}

//funcion para ver si un año es bisiesto:
bool esBisiesto(nat anio){
    return (anio % 4 == 0) && ((anio % 100 != 0) || (anio % 400 == 0));
}

// Función para obtener la cantidad de días de un mes en un año dado
nat diasMes(nat mes, nat anio){
    switch (mes){
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
            break;
        case 2: 
            if(esBisiesto(anio)){
                return 29;
            }else{
                return 28;
            }
            break;
        default:
            return 31;
    }   
}

void aumentarTFecha(TFecha &fecha, nat dias) {
    fecha->dia += dias;
    while (fecha->dia > diasMes(fecha->mes, fecha->anio)) {
        fecha->dia -= diasMes(fecha->mes, fecha->anio);
        fecha->mes++;
        if (fecha->mes > 12) {
            fecha->mes = 1;
            fecha->anio++;
        }
    }
}

int compararTFechas(TFecha fecha1, TFecha fecha2) {
    int res = 0;
    if (fecha1->anio == fecha2->anio){
        if (fecha1->mes == fecha2->mes){
            if (fecha1->dia == fecha2->dia){

            }else if (fecha1->dia > fecha2->dia){
                res = 1;
            }else {
                res = -1;
            }
        }else if (fecha1->mes > fecha2->mes){
            res = 1;
        }else {
            res = -1;
        } 
    }else if (fecha1->anio > fecha2->anio){
        res = 1;
    }else {
        res = -1;
    }
    return res;
}

/////////////////////////////////
////// FIN CÓDIGO TAREA 1 //////
/////////////////////////////////

/*-----------------------------*/

///////////////////////////
////// FUNCION NUEVA //////
///////////////////////////

// Retorna una copia de la fecha
TFecha copiarTFecha(TFecha fecha) {
    TFecha copiaFecha = NULL;
    copiaFecha = new rep_fecha;
    copiaFecha->dia = fecha->dia;
    copiaFecha->mes = fecha->mes;
    copiaFecha->anio = fecha->anio; 
    return copiaFecha;
}
/////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
/////////////////////////////////
