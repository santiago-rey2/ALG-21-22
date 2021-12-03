#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <sys/time.h>

#define TAM_MAX 3200
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
    printf("\nPeso: %d \n",pesot);
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
    for (i = 1; i < nodos; i++){
        masProximo[i] = 0;
        distanciaMinima[i] = m[i][0];
    }
    i=0;
    do{
        min = INFINITO;
        for ( j = 1; j < nodos; j++){
            if(0 <= distanciaMinima[j] && distanciaMinima[j] < min){
                min = distanciaMinima[j];
                k = j;
            }
        }
        a.x = masProximo[k];a.y = k;a.peso = min;
        insertar(a,aristas);
        distanciaMinima[k] = -1;
        for ( j = 1; j < nodos; j++){
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
            printf("%2d  ",m[i][j]);
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
    inicializar_matriz(figura2, 5);
    showMatriz(figura2, 5);
    prim(figura2,5,&c);
    mostrar_cola(c);
}

void vectores(int n,int *l,int * v){
    if(n==0){
        v[0]=1;v[1]=8;v[2]=4;v[3]=7;v[4]=2;
        v[5]=6;v[6]=5;v[7]=9;v[8]=5;v[9]=3;
        *l = 9;
    }
    if(n==1){
        v[0]=1;v[1]=4;v[2]=7;v[3]=2;v[4]=8;v[5]=3;
        *l = 5;
    }
    if(n==2){
        v[0]=7;v[1]=99;v[2]=5;v[3]=99;v[4]=99;
        v[5]=99;v[6]=8;v[7]=9;v[8]=7;v[9]=99;
        v[10]=99;v[11]=99;v[12]=5;v[13]=99;v[14]=99;
        v[15]=15;v[16]=6;v[17]=99;v[18]=8;v[19]=9;
        v[20]=11;
        *l = 20;
    }
}

void test2(){
    cola c;
    matriz m;  
    int * v,l=0,i,n;
    v = malloc(21 * sizeof(int));
    for ( i = 0; i < 3; i++)
    {
        if(i == 0){ m = crear_matriz(5);n=5;}    
        if(i == 1){ m = crear_matriz(4);n=4;}     
        if(i == 2){ m = crear_matriz(7);n=7;}
            
        vectores(i,&l,v);
        inicializar_matriz_test(m,n,v,l); 
        showMatriz(m,n);
        prim(m,n,&c);
        mostrar_cola(c);
    }
    free(v);    
}

double microsegundos() { /* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void TimePrim() {
    int n = 25, i, k = 100;
    cola c;matriz m;
    double ta, tb, t, c1, c2, c3;

    printf("     n           t(n)      t(n)/n^1.9     t(n)/n^2     t(n)/n^2.1\n");
    while (n <= 1600) {
        
        c1 = pow(n, 1.9);c2 = pow(n,2);c3 = pow(n, 2.1);
        m = crear_matriz(n);
        inicializar_matriz(m,n);
        ta = microsegundos();
        prim(m,n,&c);
        tb = microsegundos();
        t = tb - ta;
        if ((t) < 500) {
            ta = microsegundos();
            for (i = 0; i < k; i++) {
                prim(m,n,&c);
            }
            tb = microsegundos();
            t = (tb - ta) / k;
            printf("* %5d  %15f    %8f      %8f      %8f\n", n, t, t / c1, t / c2, t / c3);
        } else {
            printf("  %5d  %15f    %8f      %8f      %8f\n", n, t, t / c1, t / c2, t / c3);
        }
        while(!cola_vacia(c)){  //Vaciamos la cola para la siguiente iteración
            quitar_primero(&c);
        }      
        liberar_matriz(m,n);
        n = n * 2;
    }
}

int main(){
    int i = 0;
    inicializar_semilla();
    //test2();
    //test1();
    while(i< 5){
        TimePrim();
        i++;
    }
       
}
