#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <stdbool.h>

void OrdenacionSeleccion(int v[],int n){
    int i,j,minj,minx;
    for(i = 0;i < n-1;i++) {
        minj = i;minx = v[i];
        for(j = i+1; j < n;j++){
            if(v[j] < minx){
                minj = j;minx = v[j];  
            }
        }
        v[minj] = v[i] ; v[i] = minx;
    }
}

void OrdenacionShell(int v[],int n){
    int incremento = n,j,i,tmp;
    bool seguir = false;
    div_t aux;
    do {
        aux = div(incremento,2);
        incremento = aux.quot;
        
        for(i = incremento + 1 ;i < n; i++){
            tmp = v[i];
            j =i;
            seguir = true;

            while(j-incremento >= 0 && seguir){
                if(tmp < v[j-incremento]){
                    v[j] = v[j-incremento];
                    j = j-incremento; 
                }else{
                    seguir = false;
                }
            }
            v[j] = tmp;
        }

    } while (incremento > 0 );
    
}

void inicializar_semilla() {
    srand(time(NULL));
/* se establece la semilla de una nueva serie de enteros pseudo-aleatorios */
}

void aleatorio(int v[], int n) {
    int i, m = 2 * n + 1;
    
    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
/* se generan números pseudoaleatorio entre -n y +n */
}

void ascendente(int v[],int n){
    int i;
    for(i = 0;i < n;i++){
        v[i] = i+1;
    }
}
void descendente(int v[],int n){
    int i;
    for ( i = 0; i < n; i++)
    {
        v[i] = n-i;
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
            printf("%2d] ", v[i]);
        }
    }
}

int comprobarOrden(int v[],int n){
    int i = 1,result;
    for(i=1;i< n;i++){
        if(v[i-1]< v[i]){
            result = 1;
        }else{
            result = 0;
            break;
        }
    }
    return result;
}

void test1(){
    int v[32000],n = 10;
    ascendente(v,n);
    printf("Ascendente \n");
    listarvector(v,n);
    printf("\n Descendente \n");
    descendente(v,n);
    listarvector(v,n);
    printf("\n Aleatorio \n");
    aleatorio(v,n);
    listarvector(v,n);
}

void testSeleccion(){
    int n =10,v[n];
    printf("\n Inicializacion Ascendente\n");
    ascendente(v,n);
    listarvector(v,n);
    OrdenacionSeleccion(v,n);
    printf("\n  Vector Ordenado\n");
    listarvector(v,n);
    printf("\n Inicializacion Descendente \n");
    descendente(v,n);
    listarvector(v,n);
    OrdenacionSeleccion(v,n);
    printf("\n  Vector Ordenado\n");
    listarvector(v,n);
    printf("\n Inicializacion Aleatoria \n");
    aleatorio(v,n);
    listarvector(v,n);
    OrdenacionSeleccion(v,n);
    printf("\n  Vector Ordenado\n");
    listarvector(v,n);
}

void testShell(){
    int n =10,v[n];
    printf("\n Inicializacion Ascendente\n");
    ascendente(v,n);
    listarvector(v,n);
    OrdenacionShell(v,n);
    printf("\n  Vector Ordenado\n");
    listarvector(v,n);
    printf("\n Inicializacion Descendente \n");
    descendente(v,n);
    listarvector(v,n);
    OrdenacionShell(v,n);
    printf("\n  Vector Ordenado\n");
    listarvector(v,n);
    printf("\n Inicializacion Aleatoria \n");
    aleatorio(v,n);
    listarvector(v,n);
    OrdenacionShell(v,n);
    printf("\n  Vector Ordenado\n");
    listarvector(v,n);
}

int main(){
    inicializar_semilla();
    test1();
    testSeleccion();
    testShell();
}