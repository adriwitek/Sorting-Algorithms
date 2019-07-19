/**
 *
 * Descripcion: Implementacion de funciones de ordenacion 
 *
 * Fichero: ordenacion.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */


#include "ordenacion.h"
#include "stdlib.h"
#include "stdio.h"
#include <string.h>

/***************************************************/
/* Funcion: BubbleSort    Fecha:    01/10/2017     */
/*                                                 */
/*                                                 */
/* Funcion que ordena una tabla de numeros         */
/* que toma como entrada la tabla y el indice del  */
/* principio y fin deseados                        */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: Tabla a ordenar                     */
/* int ip: indice del primer elemento              */
/* int iu: indice del segundo elemento             */
/* Salida:                                         */
/* int ob: numer de veces que se ha ejecutado la   */
/* operacion basica                                */
/*                                                 */
/*                                                 */
/* ERR en caso de error                            */
/***************************************************/
int BubbleSort(int* tabla, int ip, int iu)
{
    int i, j, aux, ob;
    
    ob = 0;
    
    if(tabla == NULL){
        return ERR;
    }
   
   
    for(i=iu; i>ip; i--){
        for(j=ip; j<i; j++){
            ob ++;
            if(tabla[j]>tabla[j+1]){
                aux = tabla[j];
                tabla[j] = tabla[j+1];
                tabla[j+1] = aux;
            }
        }
    }
    
    
    return ob;

}



/***************************************************/
/* Funcion: MergeSort    Fecha:    03/11/2017      */
/*                                                 */
/*                                                 */
/* Funcion que ordena una tabla de numeros         */
/* que toma como entrada la tabla y el indice del  */
/* principio y fin deseados                        */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: Tabla a ordenar                     */
/* int ip: indice del primer elemento              */
/* int iu: indice del segundo elemento             */
/* Salida:                                         */
/* int ob: numer de veces que se ha ejecutado la   */
/* operacion basica                                */
/*                                                 */
/*                                                 */
/* ERR en caso de error                            */
/***************************************************/

int mergesort(int* tabla, int ip, int iu){
    
    int mitad,ob = 0,return_value=0;
    
    if(tabla == NULL || ip > iu || ip<0 ){
        return ERR;
    }
    
    if(ip ==iu){
        return 0;
    }
    else{
    
    mitad = (ip + iu)/2;
    return_value = mergesort(tabla,ip,mitad);
    if(return_value == ERR){
        return ERR;
    }
    ob += return_value;
    
    return_value = mergesort(tabla,mitad+1,iu);
    if(return_value == ERR){
        return ERR;
    }
    ob += return_value;
   
    return_value = merge(tabla,ip,iu,mitad);
    if(return_value == ERR){
        return ERR;
    }
    
    return ob + return_value;
    }
}


/***************************************************/
/* Funcion: Merge    Fecha:    03/11/2017          */
/*                                                 */
/*                                                 */
/* Funcion que une dos subtablas ordenadas         */
/* y las ordena elemento a elemento                */
/*      en una tabla final                         */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: Tabla a ordenar                     */
/* int ip: indice del primer elemento subtabla1    */
/* int iu: indice del ultimo elemento  tabla       */
/* int imedio: indice principio subtabla2          */
/* Salida:                                         */
/* int ob: numer de veces que se ha ejecutado la   */
/* operacion basica                                */
/*                                                 */
/*                                                 */
/* ERR en caso de error                            */
/***************************************************/
int merge(int* tabla, int ip, int iu, int imedio){
    
    int tamanio = 0,ob=0;
    int i,j,k;
    int * tabla_aux;
    
    
    if(tabla == NULL || ip > iu){
        return ERR;
    }
    
    tamanio = iu-ip + 1;
    
    if(tamanio <=0){
        return ERR;
    }
    else if(tamanio == 1){
        /*Solo queda un elemento,devolver ob*/
        return 0;
    }
    
    /*Creamos la Tabla'*/
    tabla_aux = (int*)malloc(tamanio*sizeof(int));
    if (tabla_aux == NULL){
        return ERR;
    }
    
    
    for(i=ip,j=imedio+1,k=0 ; i<=imedio && j<=iu;k++){
        if(tabla[i] < tabla [j]){
            tabla_aux[k] = tabla[i]; i++;
        }else{
            tabla_aux[k] = tabla[j]; j++;
        }
        ob++;
    }
    /*Parte de la derecha de la tabla restante*/
    if(i > imedio){
        for(;j<=iu;j++,k++){
            tabla_aux[k] = tabla[j];
        }
    }
    /*Parte de la izq de la tabla restante*/
    if(j > iu){
        for(;i<=imedio;i++,k++){
            tabla_aux[k] = tabla[i];
        }
    }
    
    if(memcpy(tabla+ip,tabla_aux,tamanio*sizeof(int)) == NULL){
        free(tabla_aux);
        return ERR;
    }
    
    free(tabla_aux);
    return ob;
}



/***************************************************/
/* Funcion: QuickSort    Fecha:    03/11/2017      */
/*                                                 */
/*                                                 */
/* Funcion que ordena una tabla de numeros         */
/* que toma como entrada la tabla y el indice del  */
/* principio y fin deseados                        */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: Tabla a ordenar                     */
/* int ip: indice del primer elemento              */
/* int iu: indice del segundo elemento             */
/* Salida:                                         */
/* int ob: numer de veces que se ha ejecutado la   */
/* operacion basica                                */
/*                                                 */
/*                                                 */
/* ERR en caso de error                            */
/***************************************************/


int quicksort(int *tabla, int ip, int iu){
    
    int ob = 0, return_value = 0;
    int pos;
    
    if(tabla == NULL || ip<0 || ip>iu){
        return ERR;
    }
 
    if(ip == iu){
        return ob;
    }
    else{
        
        return_value = partir(tabla, ip, iu, &pos);
        if(return_value == ERR){
            return ERR;
        }
        ob += return_value;
        /*Parte izq del pivote*/
        if(ip<(pos-1)){
            return_value = quicksort(tabla, ip, pos-1);
            if(return_value == ERR){
                return ERR;
             }
             ob += return_value;
        }
        /*Parte derecha del pivote*/
        if((pos+1)< iu){
            return_value = quicksort(tabla, pos+1, iu);
            if(return_value == ERR){
                return ERR;
             }
             ob += return_value;
        }
    }
    return ob;
}

/***************************************************/
/* Funcion: Partir   Fecha:    03/11/2017          */
/*                                                 */
/*                                                 */
/* Funcion que a partir de un pivote               */
/*     coloca los elementos menores a su izq. en   */
/*      la tabla,y a su derecha los mayoeres       */
/*      "ordena" parcialmente la tabla             */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: Tabla a ordenar                     */
/* int ip: indice del primer elemento              */
/* int iu: indice del segundo elemento             */
/* int* pos: indice del pivote                     */
/* Salida:                                         */
/* int ob: numer de veces que se ha ejecutado la   */
/* operacion basica                                */
/*                                                 */
/*                                                 */
/* ERR en caso de error                            */
/***************************************************/

int partir( int *tabla, int ip, int iu, int *pos){
    
    int k, aux, m, i, ob = 0, return_value = 0;
    
    if(tabla == NULL || ip<0 || ip>iu){
        return ERR;
    }
    
    return_value = medio(tabla, ip, iu, pos);
    if(return_value == ERR){
        return ERR;
    }
    
    m = (*pos);
    
    k = tabla[m];
    /*swap*/
    aux = tabla[ip];
    tabla[ip] = tabla[m];
    tabla[m] = aux;
    /**/
    m = ip;
    
    for(i=ip+1; i<=iu; i++){
        ob ++;
        if(tabla[i]<k){
            m++;
            /*swap*//*entre posicion i y m*/
            aux = tabla[i];
            tabla[i] = tabla[m];
            tabla[m] = aux;
        }
    }
    
     /*swap*/
    aux = tabla[ip];
    tabla[ip] = tabla[m];
    tabla[m] = aux;
    (*pos) = m;
    
    return ob;
}

/***************************************************/
/* Funcion: medio    Fecha:    03/11/2017          */
/*                                                 */
/*                                                 */
/* Funcion que elije el pivote para la tabla       */
/* en este caso elejimos el primero                */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: Tabla a ordenar                     */
/* int ip: indice del primer elemento              */
/* int iu: indice del segundo elemento             */
/* int *pos: indice del pivote                     */
/* Salida:                                         */
/* retorna 0                                       */
/*                                                 */
/*                                                 */
/* ERR en caso de error                            */
/***************************************************/

int medio(int *tabla, int ip, int iu, int *pos){
    
    if(tabla == NULL || ip<0 || ip>iu){
        return ERR;
    }
    
    (*pos) = ip;
    
    return 0;
    
}


/*-------------------------------QUICKSORT_AVG-----------------------------------------------------------------------------------*/

/***************************************************/
/* Funcion: medio_avg    Fecha:    03/11/2017      */
/*                                                 */
/*                                                 */
/* Funcion que elije el pivote para la tabla       */
/* en este caso elejimos el indice de la           */
/* posicion media de la tabla                      */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: Tabla a ordenar                     */
/* int ip: indice del primer elemento              */
/* int iu: indice del segundo elemento             */
/* int *pos: indice del pivote                     */
/* Salida:                                         */
/* retorna 0                                       */
/*                                                 */
/*                                                 */
/* ERR en caso de error                            */
/***************************************************/
int medio_avg(int *tabla, int ip, int iu, int *pos){
    
    if(tabla == NULL || ip<0 || ip>iu){
        return ERR;
    }
    
    (*pos) = (ip+iu)/2;
    
    return 0;
    
}

/***************************************************/
/* Funcion: QuickSort_avg    Fecha:    03/11/2017  */
/*                                                 */
/*                                                 */
/* Funcion que ordena una tabla de numeros         */
/* que toma como entrada la tabla y el indice del  */
/* principio y fin deseados  (lamando a medio avg) */
/* (y en consecuencia partir_avg)                  */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: Tabla a ordenar                     */
/* int ip: indice del primer elemento              */
/* int iu: indice del segundo elemento             */
/* Salida:                                         */
/* int ob: numer de veces que se ha ejecutado la   */
/* operacion basica                                */
/*                                                 */
/*                                                 */
/* ERR en caso de error                            */
/***************************************************/

int quicksort_avg(int *tabla, int ip, int iu){
    
    int ob = 0, return_value = 0;
    int pos;
    
    if(tabla == NULL || ip<0 || ip>iu){
        return ERR;
    }
 
    
    if(ip == iu){
        return ob;
    }
    else{
        
        return_value = partir_avg(tabla, ip, iu, &pos);
        if(return_value == ERR){
            return ERR;
        }
        ob += return_value;
        
        /*Parte izq del pivote*/
        if(ip<(pos-1)){
            return_value = quicksort(tabla, ip, pos-1);
            if(return_value == ERR){
                return ERR;
             }
             ob += return_value;
        }
        /*Parte derecha del pivote*/
        if((pos+1)< iu){
            return_value = quicksort(tabla, pos+1, iu);
            if(return_value == ERR){
                return ERR;
             }
             ob += return_value;
        }
        
    }
    
    return ob;

}

/***************************************************/
/* Funcion: Partir_avg   Fecha:    03/11/2017       */
/*                                                 */
/*                                                 */
/* Funcion que a partir de un pivote               */
/*     coloca los elementos menores a su izq. en   */
/*      la tabla,y a su derecha los mayoeres       */
/*      "ordena" parcialmente la tabla             */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: Tabla a ordenar                     */
/* int ip: indice del primer elemento              */
/* int iu: indice del segundo elemento             */
/* int* pos: indice del pivote                     */
/* Salida:                                         */
/* int ob: numer de veces que se ha ejecutado la   */
/* operacion basica                                */
/*                                                 */
/*                                                 */
/* ERR en caso de error                            */
/***************************************************/

int partir_avg( int *tabla, int ip, int iu, int *pos){
    
    int k, aux, m, i, ob = 0, return_value = 0;
    
    if(tabla == NULL || ip<0 || ip>iu){
        return ERR;
    }
    
    return_value = medio_avg(tabla, ip, iu, pos);
    if(return_value == ERR){
        return ERR;
    }
    
    m = (*pos);
    
    k = tabla[m];
    /*swap*/
    aux = tabla[ip];
    tabla[ip] = tabla[m];
    tabla[m] = aux;
    /**/
    
    m = ip;
    
    for(i=ip+1; i<=iu; i++){
        ob ++;
        if(tabla[i]<k){
            m++;
            /*swap*//*entre posicion i y m*/
            aux = tabla[i];
            tabla[i] = tabla[m];
            tabla[m] = aux;
        }

    }
    
     /*swap*/
    aux = tabla[ip];
    tabla[ip] = tabla[m];
    tabla[m] = aux;
    (*pos) = m;
    
    return ob;
}




/*-------------------------------QUICKSORT_STAT--------------------------------------------------------------*/

/***************************************************/
/* Funcion: medio_stat    Fecha:    03/11/2017     */
/*                                                 */
/*                                                 */
/* Funcion que elije el pivote para la tabla       */
/* en este caso elejimos el valor medio            */
/* entre los valores de ip, iu y im                */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: Tabla a ordenar                     */
/* int ip: indice del primer elemento              */
/* int iu: indice del segundo elemento             */
/* int *pos: indice del pivote                     */
/* Salida:                                         */
/* retorna 0                                       */
/*                                                 */
/*                                                 */
/* ERR en caso de error                            */
/***************************************************/
int medio_stat(int* tabla, int ip, int iu, int *pos){
    
    int ob=0,/*return_value,*/im;
    /*int table[3];*/
    if(tabla == NULL || ip<0 || ip>iu){
        return ERR;
    }
    /*
   table[0]= ip;
   table[1]=iu;
   table[2]=(ip+iu)/2;

    return_value = BubbleSort(table,0,2);
    if(return_value == ERR){
        return ERR;
    }
    ob = return_value;
    
    *pos=table[1];
    return ob;
    */
    
    im = (ip+iu)/2;
    if(im<0){
        return ERR;
    }
    
    ob++;
    if(tabla[ip]>tabla[im]){
        ob++;
        if(tabla[ip]>tabla[iu]){
            ob++;
            if(tabla[im]>tabla[iu]){
                (*pos) = im;
            }
            else{
                (*pos) = iu;
            }
        }
        else{
            (*pos) = ip;
        }
    }
    else{
        ob++;
        if(tabla[ip]>tabla[iu]){
            (*pos) = ip;
        }
        else{
            ob++;
            if(tabla[im]>tabla[iu]){
                (*pos) = iu;
            }else{
                (*pos) = im;
            }
        }
    }
    
    return ob;
}
/***************************************************/
/* Funcion: QuickSort_stat   Fecha:    03/11/2017  */
/*                                                 */
/*                                                 */
/* Funcion que ordena una tabla de numeros         */
/* que toma como entrada la tabla y el indice del  */
/* principio y fin deseados  (lamando a medio stat)*/
/* (y en consecuencia partir_stat)              */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: Tabla a ordenar                     */
/* int ip: indice del primer elemento              */
/* int iu: indice del segundo elemento             */
/* Salida:                                         */
/* int ob: numer de veces que se ha ejecutado la   */
/* operacion basica                                */
/*                                                 */
/*                                                 */
/* ERR en caso de error                            */
/***************************************************/

int quicksort_stat(int *tabla, int ip, int iu){
    
    int ob = 0, return_value = 0;
    int pos;
    
    if(tabla == NULL || ip<0 || ip>iu){
        return ERR;
    }
 
    
    if(ip == iu){
        return ob;
    }
    else{
        
        return_value = partir_stat(tabla, ip, iu, &pos);
        if(return_value == ERR){
            return ERR;
        }
        ob += return_value;
        
        /*Parte izq del pivote*/
        if(ip<(pos-1)){
            return_value = quicksort(tabla, ip, pos-1);
            if(return_value == ERR){
                return ERR;
             }
             ob += return_value;
        }
        /*Parte derecha del pivote*/
        if((pos+1)< iu){
            return_value = quicksort(tabla, pos+1, iu);
            if(return_value == ERR){
                return ERR;
             }
             ob += return_value;
        }
        
    }
    
    return ob;

}


/***************************************************/
/* Funcion: Partir_stat   Fecha:    03/11/2017     */
/*                                                 */
/*                                                 */
/* Funcion que a partir de un pivote               */
/*     coloca los elementos menores a su izq. en   */
/*      la tabla,y a su derecha los mayoeres       */
/*      "ordena" parcialmente la tabla             */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: Tabla a ordenar                     */
/* int ip: indice del primer elemento              */
/* int iu: indice del segundo elemento             */
/* int* pos: indice del pivote                     */
/* Salida:                                         */
/* int ob: numer de veces que se ha ejecutado la   */
/* operacion basica                                */
/*                                                 */
/*                                                 */
/* ERR en caso de error                            */
/***************************************************/
int partir_stat( int *tabla, int ip, int iu, int *pos){
    
    int k, aux, m, i, ob = 0, return_value = 0;
    
    if(tabla == NULL || ip<0 || ip>iu){
        return ERR;
    }
    
    return_value = medio_stat(tabla, ip, iu, pos);
    if(return_value == ERR){
        return ERR;
    }
    ob += return_value;/*Ahora acumulamos la ob de medio tambien*/
    
    m = (*pos);
    
    k = tabla[m];
    /*swap*/
    aux = tabla[ip];
    tabla[ip] = tabla[m];
    tabla[m] = aux;
    /**/
    
    m = ip;
    
    for(i=ip+1; i<=iu; i++){
        ob ++;
        if(tabla[i]<k){
            m++;
            /*swap*//*entre posicion i y m*/
            aux = tabla[i];
            tabla[i] = tabla[m];
            tabla[m] = aux;
        }

    }
    
     /*swap*/
    aux = tabla[ip];
    tabla[ip] = tabla[m];
    tabla[m] = aux;
    (*pos) = m;
    
    return ob;
}