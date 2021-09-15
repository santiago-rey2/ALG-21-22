#include <stdio.h>

int sumaSubMax1 (int v[],int n){
    int sumamax = 0,estasuma,j,i;

    for (i = 0; i < n-1; i++){
        estasuma = 0;
        for(j = i;j < n-1; j++){
            estasuma = estasuma + v[j];

            if(estasuma > sumamax){
                sumamax = estasuma;
                
            }
        }
    }



}