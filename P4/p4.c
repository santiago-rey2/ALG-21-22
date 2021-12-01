#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define TAM_MAX 1600
#define INFINITO INT_MAX

typedef int **matriz;

typedef struct{
    int x, y, peso;
} arista;

typedef arista tipo_elemento;

typedef struct{
    int cabeza, final, tamano;
    tipo_elemento vector[TAM_MAX];
} cola;

void inicializar_semilla() {
    srand(time(NULL));
/* se establece la semilla de una nueva serie de enteros pseudo-aleatorios */
}


void crear_cola(cola * c){
    c->tamano = 0;
    c->cabeza = 0;
    c->final = -1; //Antes ponia c->final = TAM_MAX
}

int cola_vacia(cola c){
    return c.tamano == 0;
}

void incrementar(int *x){
    if(++(*x) == TAM_MAX){ //Elimine el Else porque asi se incrementa, lo comprueba y siendo verdadero o falso ya queda incrementado
        *x = 0; // Creo que es cero. Cuando llega al final de la cola, vuelve a la PRIMERA posicion
    }
}

void insertar(tipo_elemento v, cola * c){
    if(c->tamano == TAM_MAX){
        printf("Error: cola llena\n");
    }else{
        c->tamano += 1;
        incrementar(&(c->final));
        c->vector[c->final] = v;
    }
}

tipo_elemento quitar_primero(cola *c){
    tipo_elemento x;

    if(cola_vacia(*c)){
        printf("Error: cola vacia");
        exit(EXIT_FAILURE);
    }else{
        c->tamano = c->tamano-1;
        x = c->vector[c->cabeza];
        incrementar(&(c->cabeza));
        return x;
    }
}

tipo_elemento primero(cola c){
    if(cola_vacia(c)){
        printf("Error: Cola vacia");
        exit(EXIT_FAILURE);
    }else{
        return c.vector[c.cabeza];
    }
}

void mostrar_cola(cola c){
    int aux = 0, pesot = 0;
    tipo_elemento aux2;

    printf("Aristas: ");
    while(aux < c.tamano){
        aux2 = c.vector[aux];
        printf("(%d,%d),",aux2.x,aux2.y);
        pesot += aux2.peso; 
        aux++;
    }
    printf("\n Peso: %d \n",pesot);
}

matriz crear_matriz(int n){
    int i;
    matriz aux;
    
    if ((aux = malloc(n * sizeof(int *))) == NULL)
        return NULL;
    for (i = 0; i < n; i++)
        if ((aux[i] = malloc(n * sizeof(int))) == NULL)
            return NULL;
    return aux;
}
void inicializar_matriz(matriz m, int n){
    /* Crea un grafo completo no dirigido con valores aleatorios entre 1 y n */
    int i, j;
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
            m[i][j] = rand() % n + 1;
    for (i = 0; i < n; i++)
        for (j = 0; j <= i; j++)
            if (i == j)
                m[i][j] = 0;
            else
                m[i][j] = m[j][i];
}

void liberar_matriz(matriz m, int n){
    int i;
    for (i = 0; i < n; i++)
        free(m[i]);
    free(m);
}

void prim(matriz m, int nodos, cola *aristas){
    /* calcular el árbol de recubrimiento mínimo devolviendo
las aristas del arbol en la cola ’aristas’ */
    int min, i, j, k = 0;
    arista a;
    int *masProximo = (int *) malloc(nodos * sizeof(int));
    int *distanciaMinima = (int *)malloc(nodos * sizeof(int));
    crear_cola(aristas);
    distanciaMinima[0] = -1;
    for (i = 1; i < nodos; i++)
    {
        masProximo[i] = 0;
        distanciaMinima[i] = m[i][0];
    }
    i=0;
    do{
        min = INFINITO;
        for ( j = 1; j < nodos; j++) // j era igual a 2
        {
            if(0 <= distanciaMinima[j] && distanciaMinima[j] < min){
                min = distanciaMinima[j];
                k = j;
            }
        }
        a.x = masProximo[k];
        a.y = k;
        a.peso = min;
        insertar(a,aristas);
        distanciaMinima[k] = -1;
        for ( j = 1; j < nodos; j++) // j era igual a 2
        {
            if(m[j][k] < distanciaMinima[j]){
                distanciaMinima[j]= m[j][k];
                masProximo[j]= k;
            }
        }
        i++;
    }while(i < nodos-1);
    free(masProximo);
    free(distanciaMinima);
}
void showMatriz (matriz m, int n) {
    int i, j;
    
    for(i = 0; i < n; i++) 
        for(j = 0; j < n; j++) {
            printf("%d  ",m[i][j]);
            if(j == n-1) 
                printf("\n");
        }
}

void inicializar_matriz_test(matriz m, int n,int *ve,int l){
    /* Crea un grafo completo no dirigido con valores aleatorios entre 1 y n */
    int i, j,k=0;
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
            if(k <= l){
                m[i][j] = ve[k];
                k++;
            }
                        
    for (i = 0; i < n; i++)
        for (j = 0; j <= i; j++)
            if (i == j)
                m[i][j] = 0;
            else
                m[i][j] = m[j][i];
}

void test1 (){
    cola c;
    matriz figura2 = crear_matriz(5);
    //inicializar_matriz(figura2, 5);
    ini_m(figura2,5);
    showMatriz(figura2, 5);
    prim(figura2,5,&c);
    mostrar_cola(c);
}

void test2(){
    cola c;
    matriz m;
    m = crear_matriz(5);
    int v[10];
    v[0]=1;
    v[1]=8;
    v[2]=4;
    v[3]=7;
    v[4]=2;
    v[5]=6;
    v[6]=5;
    v[7]=9;
    v[8]=5;
    v[9]=3;  
    inicializar_matriz_test(m,5,v,9);
    showMatriz(m, 5);
    prim(m,5,&c);
    mostrar_cola(c);

}

int main(){

    inicializar_semilla();
    test2();   
}
