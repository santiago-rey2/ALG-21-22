#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <stdbool.h>

#define UMBRAL 100
#define intercambiar(x,y) {int aux=x; x=y; y=aux;} //Usamos una macro para instanciar la realización del cambio 

//===============Ordenación Insercion===================

void OrdenacionInsercion(int * v,int n){
    int i,x,j;

    for(i = 1 ; i < n ; i++){
        x= v[i];
        j = i-1;
        while(j >= 0 && v[j] > x){
            v[j+1]=v[j];
            j=j-1;
        }
        v[j+1] = x;
    }
}
//===============Ordenación Quick Sort===================

//--------------- Mediana de 3 --------------------------
void mediana3(int *v,int izq,int der){
    int k;
    k = (izq + der) / 2;
    if(v[k]>v[der]) intercambiar(v[k],v[der]);
    if(v[k]>v[izq]) intercambiar(v[k],v[izq]);
    if(v[izq]>v[der]) intercambiar(v[izq],v[der]);
    
}

//----------------- Aux de Quick Sort -------------------

void OrdenarAux(int *v,int izq,int der){
    int pivote,i,j;
    if(izq+UMBRAL<= der){
        mediana3(v,izq,der);
        pivote = v[izq];
        i = izq;
        j = der;
        do{
            do{i++;}while(v[i]< pivote);
            do{j--;}while(v[j]> pivote);
            intercambiar(v[i],v[j]);
            
        }while(j > i);
        
        intercambiar(v[i],v[j]);
        intercambiar(v[izq],v[j]);
        OrdenarAux(v,izq,j-1);
        OrdenarAux(v,j+1,der);
    }
}

//------------- Función Quick Sort ----------------------

void OrdenacionQuickSort(int *v,int n){
    OrdenarAux(v,0,n-1);
    if(UMBRAL > 1){
        OrdenacionInsercion(v,n);
    }
}

//============= Inicializar Semilla =====================

void inicializar_semilla() {
    srand(time(NULL));
/* se establece la semilla de una nueva serie de enteros pseudo-aleatorios */
}

//============ Inicialización Aleatoria =================

void aleatorio(int *v, int n) {
    int i, m = 2 * n + 1;

    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
/* se generan números pseudoaleatorio entre -n y +n */
}

//============ Inicialización Ascendente ================

void ascendente(int *v, int n) {
    int i;
    for (i = 0; i < n; i++) {
        v[i] = i + 1;
    }
}

//============= Inicialización Descendente ==============

void descendente(int *v, int n) {
    int i;
    for (i = 0; i < n; i++) {
        v[i] = n - i;
    }
}

//============ Listar Vectores ==========================

void listarvector(int v[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        if (i == 0) {
            printf("[ %2d, ", v[i]);
        } else if (i < n - 1) {
            printf("%2d, ", v[i]);
        } else {
            printf("%2d] \n", v[i]);
        }
    }
}


//=================== Comprobar Ornden Vector ===============

/*
La funcion comprobar orden tendrá como entrada un vector y su tamaño
y nos devolvera 0 en caso de que el vector no esté ordenado y 1 en caso
de estar ordenado.Comprobamos el orden mirando que el anterior sea inferior 
al siguiente.
*/

int comprobarOrden(int v[], int n) {
    int i = 1, result;
    for (i = 1; i < n; i++) {
        if (v[i - 1] <= v[i]) {
            result = 1;
        } else {
            result = 0;
            break;
        }
    }
    return result;
}

//============= Test Inserción ==================

void testInsercion() {
    int n = 10,*v;
    
    v = malloc(n*sizeof(int));

    printf("\n\n Inicializacion Descendente \n\n");
    descendente(v, n);
    listarvector(v, n);
    printf("\n Ordenado : %d \n", comprobarOrden(v, n));
    OrdenacionInsercion(v, n);
    printf("\n\n Ordenacion por Insercion \n\n");
    listarvector(v, n);
    printf("\n Ordenado : %d \n", comprobarOrden(v, n));
    printf("\n\n Inicializacion Aleatoria \n\n");
    aleatorio(v, n);
    listarvector(v, n);
    printf("\n Ordenado : %d \n", comprobarOrden(v, n));
    OrdenacionInsercion(v, n);
    printf("\n\n Ordenacion por Insercion \n\n");
    listarvector(v, n);
    printf("\n Ordenado : %d \n", comprobarOrden(v, n));
}

//============= Test Quick Sort =================

void testQuickSort() {
    int n = 10,*v;
    
    v = malloc(n*sizeof(int));

    printf("\n\n Inicializacion Descendente \n\n");
    descendente(v, n);
    listarvector(v, n);
    printf("\n Ordenado : %d \n", comprobarOrden(v, n));
    OrdenacionQuickSort(v, n);
    printf("\n\n Ordenacion por QuickSort \n\n");
    listarvector(v, n);
    printf("\n Ordenado : %d \n", comprobarOrden(v, n));
    printf("\n\n Inicializacion Aleatorio \n\n");
    aleatorio(v, n);
    listarvector(v, n);
    printf("\n Ordenado : %d \n", comprobarOrden(v, n));
    OrdenacionQuickSort(v, n);
    printf("\n\n Ordenacion por QuickSort \n\n");
    listarvector(v, n);
    printf("\n Ordenado : %d \n", comprobarOrden(v, n));
}

//============= Medicion de Tiempos =================

//--------- Medir Microsegundos ---------------------

double microsegundos() { /* obtiene la hora del sistema en microsegundos */
    struct timeval t;

    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void cotas(void(*ordenar)(int*,int),void(*inicializar)(int*,int),int n,
    double* c1,double* c2,double* c3){
    if(ordenar == OrdenacionInsercion && inicializar == descendente){
        *c1 = pow(n, 1.5);*c2 = pow(n, 2);*c3 = pow(n, 2.2);
    }
    if(ordenar == OrdenacionInsercion && inicializar == aleatorio){
        *c1 = pow(n, 1.5);*c2 = pow(n, 2);*c3 = pow(n, 2.2);
    }
    if(ordenar == OrdenacionInsercion && inicializar == ascendente){
        *c1 = pow(n, 0.8);*c2 = pow(n, 1);*c3 = pow(n, 1.2);
    }
    if(ordenar == OrdenacionQuickSort && inicializar == descendente){
        *c1 = pow(n, 1);*c2 = pow(n, 1.2);*c3 = pow(n, 1.4);
    }
    if(ordenar == OrdenacionQuickSort && inicializar == aleatorio){
        *c1 = pow(n, 1);*c2 = pow(n, 1.2);*c3 = pow(n, 1.4);
    }
    if(ordenar == OrdenacionQuickSort && inicializar == ascendente){
        *c1 = pow(n, 1);*c2 = pow(n, 1.2);*c3 = pow(n, 1.4);
    }
}


void medirTiemposGeneral(void(*ordenar)(int*,int),void(*inicializar)(int*,int)){
    int n=1000,k = 1000, i; int*v;
    double ta, tb, t, c1 = 0, c2 = 0 , c3 = 0;
    printf("    n           t(n)        t(n)/sub    t(n)/est  t(n)/sobre\n");
    while (n <= 64000) {
        v = malloc(n*sizeof(int)); 
        inicializar(v, n);
        ta = microsegundos();
        ordenar(v, n);
        tb = microsegundos();
        t = tb - ta;
        if (t < 500) {
            ta = microsegundos();
            for (i = 0; i < k; i++) {
                inicializar(v, n);
                ordenar(v, n);
            }
            tb = microsegundos();
            t = tb - ta;
            ta = microsegundos();
            for (i = 0; i < k; i++) {
                inicializar(v, n);
            }
            tb = microsegundos();
            t = (t - (tb - ta)) / k;
            printf("*");
        } else {
            printf(" ");
        }
        cotas(ordenar,inicializar,n,&c1,&c2,&c3);
        printf("%6d %15f  %11f  %11f  %11f\n", n, t, t/c1, t/c2, t/c3);
        n = n * 2;
        free(v);
    }
}

void tiempos(){
    printf("Tiempos Inserción\n");
    medirTiemposGeneral(OrdenacionInsercion,descendente);
    medirTiemposGeneral(OrdenacionInsercion,aleatorio);
    medirTiemposGeneral(OrdenacionInsercion,ascendente);
    printf("\nTiempos QuickSort\n");
    medirTiemposGeneral(OrdenacionQuickSort,descendente);
    medirTiemposGeneral(OrdenacionQuickSort,aleatorio);
    medirTiemposGeneral(OrdenacionQuickSort,ascendente);
}

int main(){ 
    inicializar_semilla();
    //testInsercion();
    //testQuickSort();
    tiempos();
}
