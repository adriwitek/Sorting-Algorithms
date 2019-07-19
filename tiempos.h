/**
 *
 * Descripcion: Funciones de cabecera para ordenacion 
 *
 * Fichero: tiempos.h
 * Autor: Adrian Rubio
 * Version: 2.0
 * Fecha: 17-10-2016
 *
 */

#ifndef TIEMPOS_H
#define TIEMPOS_H

/* constantes */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

#include "busqueda.h"
#include "ordenacion.h"

/* definiciones de tipos */
typedef struct tiempo {
  int N;           /* tamanio los elementos */
  int n_elems;     /* numero de elementos a promediar */
  double tiempo;   /* tiempo promedio */
  double medio_ob; /* numero promedio de veces que se ejecuta la OB */
  int min_ob;      /* minimo de ejecuciones de la OB */
  int max_ob;      /* maximo de ejecuciones de la OB */
} TIEMPO, *PTIEMPO;


/* Funciones */
short tiempo_medio_ordenacion(pfunc_ordena metodo, int n_perms,int N, PTIEMPO ptiempo);
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero, int num_min, int num_max, int incr, int n_perms);
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int n_tiempos);
/**********V2***********/
short genera_tiempos_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador, 
                                char orden, char* fichero, 
                                int num_min, int num_max, 
                                int incr, int n_veces);

short tiempo_medio_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador,
                              char orden,
                              int N, 
                              int n_veces,
                              PTIEMPO ptiempo);




#endif
