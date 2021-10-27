#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <stdbool.h>

#define VMAX 256000
#define UMBRAL 1

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

void intercambiar(int *v,int k,int j){
    int aux = v[k];
    v[k]=v[j];
    v[j] = aux;
}

void mediana3(int *v,int izq,int der){
    int k;
    k = (izq + der) / 2;
    if(v[k]>v[der]){
        intercambiar(v,k,der);
    }
    if(v[k]>v[izq]){
        intercambiar(v,k,izq);
    }
    if(v[izq]>v[der]){
        intercambiar(v,izq,der);
    }
}

void OrdenarAux(int *v,int izq,int der){
    int pivote,i,j;
    if(izq+UMBRAL<= der){
        mediana3(v,izq,der);
        pivote = v[izq];
        i = izq;
        j = der;
        do{
            do{i = i+1;}while(v[i]>= pivote);
            do{j = j-1;}while(v[j]<= pivote);
            intercambiar(v,i,j);
        }while(j <= i);
        intercambiar(v,i,j);
        intercambiar(v,izq,j);
        OrdenarAux(v,izq,j-1);
        OrdenarAux(v,j+1,der);
    }
}

void OrdenacionQuickSort(int *v,int n){
    OrdenarAux(v,0,n);
    if(UMBRAL > 1){
        OrdenacionInsercion(v,n);
    }
}



void inicializar_semilla() {
    srand(time(NULL));
/* se establece la semilla de una nueva serie de enteros pseudo-aleatorios */
}

void aleatorio(int *v, int n) {
    int i, m = 2 * n + 1;

    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
/* se generan números pseudoaleatorio entre -n y +n */
}

void ascendente(int *v, int n) {
    int i;
    for (i = 0; i < n; i++) {
        v[i] = i + 1;
    }
}

void descendente(int *v, int n) {
    int i;
    for (i = 0; i < n; i++) {
        v[i] = n - i;
    }
}

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
}
void testQuickSort() {
    int n = 10,*v;
    
    v = malloc(n*sizeof(int));

    printf("\n\n Inicializacion Descendente \n\n");
    descendente(v, n);
    listarvector(v, n);
    printf("\n Ordenado : %d \n", comprobarOrden(v, n));
    OrdenacionQuickSort(v, n);
    printf("\n\n Ordenacion por Insercion \n\n");
    listarvector(v, n);
    printf("\n Ordenado : %d \n", comprobarOrden(v, n));
}

double microsegundos() { /* obtiene la hora del sistema en microsegundos */
    struct timeval t;

    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}



int main() {
    inicializar_semilla();
    //testInsercion();
    testQuickSort();

}
