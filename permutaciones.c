/**
 *
 * Descripcion: Implementacion de funciones de generacion de permutaciones
 *
 * Fichero: permutaciones.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */


#include "permutaciones.h"
#include "stdlib.h"
#include "stdio.h"

/***************************************************/
/* Funcion: aleat_num  Fecha:13/10/2017            */
/* Autores:                                        */
/*            Adrian Rubio                         */
/*                                                 */
/* Rutina que genera un numero aleatorio           */
/* entre dos numeros dados                         */
/*                                                 */
/* Entrada:                                        */
/* int inf: limite inferior                        */
/* int sup: limite superior                        */
/* Salida:  numero aleatorio                       */
/* int: numero aleatorio                           */
/***************************************************/
int aleat_num(int inf, int sup)
{
  int num_ale1;

  num_ale1 = ((rand()/(RAND_MAX + 1.) ) * (sup - inf + 1)) + inf;

  return num_ale1;
  
}

/***************************************************/
/* Funcion: genera_perm  Fecha:13/10/2017          */
/* Autores:                                        */
/*           Adrian Rubio                          */
/*                                                 */
/* Rutina que genera una permutacion               */
/* aleatoria                                       */
/*                                                 */
/* Entrada:                                        */
/* int n: Numero de elementos de la                */
/* permutacion                                     */
/* Salida:                                         */
/* int *: puntero a un array de enteros            */
/* que contiene a la permutacion                   */
/* o NULL en caso de error                         */
/***************************************************/
int* genera_perm(int N){
  
  int i, aux, num_ale;
  
  int * perm;
  
  if(!N){
    return NULL;
  }
  
  perm = (int *) calloc (N, sizeof(int));
  
  if(perm == NULL){
    return NULL;
  }
  
  
  for(i=0; i < N; i++){
    perm[i] = i+1;
  }
  
  
  
  for(i = 0; i < N; i++){
    
    aux = perm[i];
    num_ale = aleat_num(i, (N-1));
    perm[i] = perm[num_ale];
    perm[num_ale] = aux;
  }
  
  return perm;

}

/***************************************************/
/* Funcion: genera_permutaciones Fecha:13/10/2017  */
/* Autores:                                        */
/*          Adrian Rubio                           */
/*                                                 */
/* Funcion que genera n_perms permutaciones        */
/* aleatorias de tamanio elementos                 */
/*                                                 */
/* Entrada:                                        */
/* int n_perms: Numero de permutaciones            */
/* int N: Numero de elementos de cada              */
/* permutacion                                     */
/* Salida:                                         */
/* int**: Array de punteros a enteros              */
/* que apuntan a cada una de las                   */
/* permutaciones                                   */
/* NULL en caso de error                           */
/***************************************************/
int** genera_permutaciones(int n_perms, int N)
{
  
  int i,j;
  int ** g_perm;
  
  if(!N || !n_perms){
    return NULL;
  }
  
 
  g_perm = (int **) calloc (n_perms, sizeof(int*));
  
  if(g_perm == NULL){
    return NULL;
  }

  
  for(i=0 ; i<n_perms ; i++){
    
    g_perm[i] = genera_perm(N);
    /*CdE*/
    if(g_perm[i] == NULL){
      for(j=0; j<i; j++){
        free(g_perm[j]);
      }
      free(g_perm);
      return NULL;
    }
    
  }
  
  return g_perm;

}
