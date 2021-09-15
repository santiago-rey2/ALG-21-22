#include <stdio.h>

int sumaSubMax1 (int v[],int n){
    int sumamax = 0,estasuma,j,i;

    for (i = 0; i < n; i++){
        estasuma = 0;
        for(j = i;j < n; j++){
            estasuma += v[j];

            if(estasuma > sumamax){
                sumamax = estasuma;
            }
        }
    }

    return sumamax;

}

int sumaSubMax2 ( int v[],int n){
    int estasuma = 0, sumamax = 0,j;

    for(j = 0 ; j < n ; j++){
        estasuma += v[j];

        if(estasuma > sumamax){
            sumamax = estasuma;
        }else if(estasuma < 0){
            estasuma = 0;
        }
    }

    return sumamax;

}

void listarvector(int v[],int n){
    int i;
    for (i = 0;i <= n;i++){
        if(i == 0){
            printf("[ %2d, ",v[i]);
        }else if(i < n){
            printf("%2d, ",v[i]);
        }else{
            printf("%2d] ",v[i]);
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

void aleatorio(int v [], int n) {
int i, m=2*n+1;
for (i=0; i < n; i++)
v[i] = (rand() % m) - n;
/* se generan números pseudoaleatorio entre -n y +n */
}

void test1(){
    int v[4],i;
    for(i=0; i < 6;i++){
        inicializarvector(v,4,i);
        listarvector(v,4);
        printf("  subM1 %d   subM2 %d  \n",sumaSubMax1(v,5),sumaSubMax2(v,5));
    }

}

void test2(){
    int v[8],i,k;
    k = 10;

    printf("                    subM1  subM2 \n");

    for(i=0; i < k ; i++){

        aleatorio(v,8);
        listarvector(v,8);
        printf("                      %3d    %3d \n");

    }
    
}

int main(){
    inicializar_semilla();
    test1();
    test2();
}