#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

int max(int max1,int max2){
    
    if(max1 > max2){
        return max1;
    }else if(max2 > max1){
        return max2;
    }else{
        return max1;
    }   
}


int sumasubmaxaux(int v[],int izq,int der){

    int centro,sumDer,sumIzq,sumBordeDer,sumBordeIzq,sumAux,i,j;

    if(izq == der){
        if(v[izq] > 0){
            return v[izq];
        }else{
            return 0;
        }
    }else{
        centro = (izq + der) / 2;
        sumDer = sumasubmaxaux(v,centro + 1,der);
        sumIzq = sumasubmaxaux(v,izq,centro);
        sumBordeDer = 0;
        sumAux = 0;

        for(i = centro + 1;i <= der; i++){
            sumAux = sumAux + v[i];
            if(sumAux > sumBordeDer){
                sumBordeDer = sumAux;
            }
        }

        sumBordeIzq = 0;
        sumAux = 0;
        for(j = centro;j >= izq;j-- ){
            sumAux = sumAux + v[j];
            if(sumAux > sumBordeIzq){
                sumBordeIzq = sumAux;
            }
        }

        return max(max(sumIzq,sumDer),sumBordeDer + sumBordeIzq);
    }

    return 1;

}

int sumaSubMax3(int v[], int n) {
    return sumasubmaxaux(v,0,n-1);
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

void inicializarvector(int v[],int n,int i){
    if(i == 0){
        v[0]=-9;v[1]=2;v[2]=-5;v[3]=-4;v[4]=6;
    }else if(i == 1){
        v[0]=4;v[1]=0;v[2]=9;v[3]=2;v[4]=5;
    }else if(i == 2){
        v[0]=-2;v[1]=-1;v[2]=-9;v[3]=-7;v[4]=-1;
    }else if(i == 3){
        v[0]=9;v[1]=-2;v[2]=1;v[3]=-7;v[4]=-1;
    }else if(i == 4){
        v[0]=15;v[1]=-2;v[2]=-5;v[3]=-4;v[4]=16;
    }else if(i == 5){
        v[0]=7;v[1]=-5;v[2]=6;v[3]=7;v[4]=-7;
    }
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

void test() {
    int n = 5, v[n], i;
    
    printf("                      subM3 \n");
    for (i = 0; i < 6; i++) {
        inicializarvector(v, n, i);
        listarvector(v, n);
        printf(" %3d   \n", sumaSubMax3(v, n));
    }
}


double microsegundos() { /* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}


void TimeSubMax() {
    int n = 500, v[32000], i, k = 1000;
    double ta, tb, t, c1, c2, c3;

    printf("     n       t(n)      t(n)/n  t(n)/n^1.16  t(n)/n^1.3\n");
    while (n <= 32000) {
        aleatorio(v, n);
        c1 = pow(n, 1);
        c2 = pow(n, 1.16);
        c3 = pow(n, 1.3);
        ta = microsegundos();
        sumaSubMax3(v, n);
        tb = microsegundos();
        t = tb - ta;
        if ((t) < 500) {
            ta = microsegundos();
            for (i = 0; i < k; i++) {
                sumaSubMax3(v, n);
            }
            tb = microsegundos();
            t = (tb - ta) / k;
            printf("* %5d  %15f    %8f   %8f   %8f\n",n,t,t/c1,t/c2,t/c3);
        } else {
            printf("  %5d  %15f    %8f   %8f   %8f\n",n,t,t/c1,t/c2,t/c3);
        }
        n = n * 2;
    }
}


int main() {
    int i;
    inicializar_semilla();
    test();
    i = 0;
    while(i < 5){
        printf("\nTiempos SumaSubMax3: \n");
        TimeSubMax();
        i++;
    }
}
