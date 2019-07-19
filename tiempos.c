/**
 *
 * Descripcion: Implementacion de funciones de tiempo
 *
 * Fichero: tiempos.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */

#include "tiempos.h"
#include "permutaciones.h"
#include "ordenacion.h"
#include "busqueda.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "limits.h"

/***************************************************/
/* Funcion:tiempo_medio_ordenacion Fecha:13/10/2017*/
/* Autores:                                        */
/*          Adrian Rubio                           */
/*                                                 */
/* Funcion que calcula el tiempo                   */
/* medio de ordenacion                             */
/*                                                 */
/* Entrada:                                        */
/* int n_perms: Numero de permutaciones            */
/* int N: Numero de elementos de cada              */
/* permutacion                                     */
/* PTIEMPO: puntero a ptiempo                      */
/* Salida:                                         */
/* short: OK si todo va bien                       */
/* ERR en caso contrario                           */
/***************************************************/
short tiempo_medio_ordenacion(pfunc_ordena metodo, 
                              int n_perms,
                              int N, 
                              PTIEMPO ptiempo)
{
  int i;
  int **perms;
  clock_t t1,t2;
  int ob, ob_max = 0, ob_min = INT_MAX;
  double  ob_medio = 0, tiempo_medio;
  
  if(!n_perms || !N || ptiempo == NULL){
    return ERR;
  }
  
  perms = genera_permutaciones(n_perms, N);
  
  if(perms == NULL){
    return ERR;
  }
  
  t1 = clock();
  if(t1 == -1){
    for(i=0; i<n_perms; i++){
      free(perms[i]);
    }
    free(perms);
    return ERR;
  }
  
  for(i=0; i<n_perms; i++){
    ob = metodo(perms[i], 0, N-1);
    if(ob  == ERR){
      for(i=0; i<n_perms; i++){
        free(perms[i]);
      }
      free(perms);
      return ERR;
    }
    
    if(ob > ob_max){
      ob_max = ob;
    }
    if(ob < ob_min){
      ob_min = ob;
    }
    ob_medio += ob;
    
    if(perms[i] == NULL){
       for(i=0; i<n_perms; i++){
          free(perms[i]);
       }
       free(perms);
       return ERR;
    }
  }

  t2 = clock();
  if(t2 == -1){
    for(i=0; i<n_perms; i++){
      free(perms[i]);
    }
    free(perms);
    return ERR;
  }
  
  ob_medio = ob_medio/n_perms;
  
  tiempo_medio = (t2-t1)/n_perms;
  
  ptiempo->N = N;
  ptiempo->n_elems = n_perms;
  ptiempo->tiempo = tiempo_medio;
  ptiempo->medio_ob = ob_medio;
  ptiempo->max_ob = ob_max;
  ptiempo->min_ob = ob_min;
  
  for(i=0; i<n_perms; i++){
      free(perms[i]);
  }
  free(perms);
  return OK;

}

/***************************************************/
/* Funcion: genera_tiempos_ordenacion              */
/* Fecha:13/10/2017                                */
/* Autores:                                        */
/*          Adrian Rubio                           */
/*                                                 */
/* Funcion que genera tiempos de ordenacion        */
/* entre un num_max y un num_min con incr          */
/*                                                 */
/* Entrada:                                        */
/* int n_perms: Numero de permutaciones            */
/* int num_min: Numero minimo                      */
/* int num_max: Numero maximo                      */
/* int incr: Numero de incremento                  */
/* char* fichero: fichero                          */
/* pfunc_ordena metodo: funcion de ordenacion      */
/* Salida:                                         */
/* short: OK si toda va bien                       */
/* ERR en caso contrario                           */
/***************************************************/
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero, 
                                int num_min, int num_max, 
                                int incr, int n_perms)
{
  
  int i, num, n;
  PTIEMPO ptiempo;
  
  if(!num_max || !num_min || !incr || !n_perms || fichero == NULL){
    return ERR;
  }
  
  num = ((num_max - num_min)/incr) + 1.;
  ptiempo = (PTIEMPO) calloc (num, sizeof(TIEMPO));
  
  if(!ptiempo){
    return ERR;
  }
  for(i=0, n=0; i<num; i++){
   
    if(tiempo_medio_ordenacion(metodo, n_perms, num_min + n , &ptiempo[i]) == ERR){
      free(ptiempo);
      return ERR;
    }
     n += incr;
  }
  if(guarda_tabla_tiempos(fichero, ptiempo, num) == ERR){
    free(ptiempo);
    return ERR;
  }
  free(ptiempo);
  return OK;
}

/***************************************************/
/* Funcion: guarda_tabla_tiempos                   */
/* Fecha:13/10/2017                                */
/* Autores:                                        */
/*          Adrian Rubio                           */
/*                                                 */
/* Funcion que guarda en un fichero                */
/* los tiempos de ordenacion en una tabla          */
/*                                                 */
/* Entrada:                                        */
/* int n_tiempos: Numero de tiempos                */
/* PTIEMPO tiempo: puntero                         */
/* char* fichero: fichero                          */
/* Salida:                                         */
/* short: OK si toda va bien                       */
/* ERR en caso contrario                           */
/***************************************************/
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int n_tiempos)
{
  
  FILE * fp;
  int i;
  
  if(fichero == NULL || tiempo == NULL || !n_tiempos){
    return ERR;
  }
  
  fp = fopen( fichero, "w");
  if(fp == NULL){
    return ERR;
  }
  
  for(i=0; i<n_tiempos; i++){
    if(fprintf(fp, "%d\t\t %.2f\t\t %.2f\t\t %d\t\t %d\n", tiempo[i].N, tiempo[i].tiempo, tiempo[i].medio_ob, tiempo[i].min_ob, tiempo[i].max_ob) < 0){
      fclose(fp);
      return ERR;  
    }
  }
  
  fclose(fp);
  
  return OK;
  
  
}


/***************************************************/
/* Funcion:tiempo_medio_busqueda Fecha:11/12/2017  */
/* Autores:                                        */
/*          Adrian Rubio                           */
/*                                                 */
/* Funcion que calcula el tiempo                   */
/* medio de busqueda                               */
/*                                                 */
/* Entrada:                                        */
/* pfunc_busqueda metodo: metodo de busqueda       */
/* pfunc_generador_claves generador: genera claves */
/* char orden: orden del diccionario               */
/* int N: tamaño                                   */
/* int n_veces: numero de veces a buscar clave     */
/* PTIEMPO ptiempo: puntero a estructura tiempo    */
/* Salida:                                         */
/* short: OK si todo va bien                       */
/* ERR en caso contrario                           */
/***************************************************/
short tiempo_medio_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador, char orden, int N, int n_veces, PTIEMPO ptiempo){

  PDICC pdicc;
  int * tabla_perm;
  int * tabla_claves;
  int pos, i = 0;
  clock_t t1,t2;
  int ob, ob_max = 0, ob_min = INT_MAX;
  double  ob_medio = 0, tiempo_medio;
  
  if(N < 0 || n_veces < 0 || ptiempo == NULL){
    return ERR;
  }
  
  pdicc = ini_diccionario(N, orden);
  if(pdicc == NULL){
    return ERR;
  }
  
  tabla_perm = genera_perm(N);
  if(tabla_perm == NULL){
    libera_diccionario(pdicc);
    return ERR;
  }
  
  if(insercion_masiva_diccionario(pdicc, tabla_perm, N) == ERR){
    free(tabla_perm);
    libera_diccionario(pdicc);
    return ERR;
  }
  
  tabla_claves = (int*)malloc((N*n_veces) * sizeof(int));
  if(tabla_claves == NULL){
    free(tabla_perm);
    libera_diccionario(pdicc);
    return ERR;
  }
  
  generador(tabla_claves, N*n_veces, N);
  
  t1 = clock();
  if(t1 == -1){
    free(tabla_claves);
    free(tabla_perm);
    libera_diccionario(pdicc);
    return ERR;
  }
  
  for(i = 0; i < (n_veces*N); i++){
    
    ob = busca_diccionario(pdicc, tabla_claves[i], &pos, metodo);
    
    if(ob == ERR){
      free(tabla_claves);
      free(tabla_perm);
      libera_diccionario(pdicc);
      return ERR;
    }
    
    if(ob > ob_max){
      ob_max = ob;
    }
    if(ob < ob_min){
      ob_min = ob;
    }
    ob_medio += ob;
    
    if(pos == NO_ENCONTRADO){
      free(tabla_claves);
      free(tabla_perm);
      libera_diccionario(pdicc);
      return ERR;
    }
  }
  
  t2 = clock();
  if(t2 == -1){
    free(tabla_claves);
    free(tabla_perm);
    libera_diccionario(pdicc);
    return ERR;
  }
  
  tiempo_medio = (t2-t1) / (N * n_veces);
  
  ob_medio = ob_medio / (N * n_veces);
  
  ptiempo->N = N;
  ptiempo->n_elems = (N*n_veces);
  ptiempo->tiempo = tiempo_medio;
  ptiempo->medio_ob = ob_medio;
  ptiempo->min_ob = ob_min;
  ptiempo->max_ob = ob_max;
  
  free(tabla_perm);
  free(tabla_claves);
  libera_diccionario(pdicc);
  return OK;
}


/***************************************************/
/* Funcion: genera_tiempos_busqueda                */
/* Fecha:12/12/2017                                */
/* Autores:                                        */
/*          Adrian Rubio                           */
/*                                                 */
/* Funcion que genera tiempos de ordenacion        */
/* entre un num_max y un num_min con incr          */
/*                                                 */
/* Entrada:                                        */
/* pfunc_busqueda metodo: metodo de busqueda       */
/* pfunc_generador_claves generador: generar claves*/
/* char orden: orden del diccionario               */
/* char * fichero: fichero a escribir              */
/* int num_min: Numero minimo                      */
/* int num_max: Numero maximo                      */
/* int incr: Numero de incremento                  */
/* int n_veces: numero de veces a buscar clave     */
/* Salida:                                         */
/* short: OK si toda va bien                       */
/* ERR en caso contrario                           */
/***************************************************/
short genera_tiempos_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador,  char orden, char* fichero, int num_min, int num_max, int incr, int n_veces){
  
  int i, num, n;
  PTIEMPO ptiempo;
  
  if(fichero == NULL || num_min > num_max || num_min < 0 || !incr || n_veces <= 0){
    return ERR;
  }
  
  num = ((num_max - num_min) / incr) + 1.;
  
  ptiempo = (PTIEMPO)calloc(num,sizeof(TIEMPO));
  if(ptiempo == NULL){
    return ERR;
  }

  
  for(i=0, n=0; i<num; i++){
    if(tiempo_medio_busqueda(metodo, generador, orden, (num_min + n), n_veces, &ptiempo[i]) == ERR){
      free(ptiempo);
      return ERR;
    }
    n += incr;
  }
  
  if(guarda_tabla_tiempos(fichero, ptiempo, num) == ERR){
    free(ptiempo);
    return ERR;
  }
  
  free(ptiempo);
  return OK;
}
