#include <stdio.h>

int sumaSubMax1 (int v[],int n){
    int sumamax = 0,estasuma,j,i;

    for (i = 0; i < n-1; i++){
        estasuma = 0;
        for(j = i;j < n-1; j++){
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

    for(j = 0 ; j < n-1 ; j++){
        estasuma += v[j];

        if(estasuma > sumamax){
            sumamax = estasuma;
        }else if(estasuma < 0){
            estasuma = 0;
        }
    }

    return sumamax;

}

void test1(){
    
}

int main(){

}