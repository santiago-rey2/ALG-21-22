// Santiago Rey Garcia y Alexandre Perez Paredes

#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

double microsegundos();
void ord_ins (int v [],int n);
void ord_shell (int v [], int n);
void test_ins();
void test_shell();
void inicializar_semilla();
void aleatorio(int v [], int n);
void ascendente(int v [], int n);
void descendente(int v [], int n);
void imprimirVector(int v[],int n);
void test();
void testAsc();
void testDesc();
double microsegundos();
void testOrdShellAle();
void testOrdShellAsc();
void testOrdShellDesc();
void test_ins_ascendente();
void test_ins_aleatorio();
void test_ins_descendente();

int main(){
	int i;
	inicializar_semilla();
	test();
	testAsc();
	testDesc();
	while(i < 3){
		testOrdShellAle();
		testOrdShellAsc();
		testOrdShellDesc();
		test_ins_aleatorio();
		test_ins_ascendente();
		test_ins_descendente();
		i++;
	}
}
//--------------------------------------------------------------------
double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
//--------------------------------------------------------------------
void ord_ins (int v [],int n){ //funciona correctamente
	int i,j,x;
	for(i=1;i<=n;i++){ // empieza en la posicion 1 que realmente es la 2 en el vector
		x=v[i];
		j=i-1;
		while(j>=0 && v[j]>x){
			v[j+1] = v[j];
			j--;
		}
		v[j+1] = x;
	}
}
//--------------------------------------------------------------------
void ord_shell (int v [], int n){

	int incremento = n, i,j,tmp;
	bool seguir;
	do{
		incremento = incremento/2;
		for(i=incremento;i <= n;i++){
			tmp = v[i];
			j = i;
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
	}while(incremento > 0);
}
//--------------------------------------------------------------------
void test(){
	int v[32000], n = 9;
	aleatorio(v,n);
	printf("\nInicializacion aleatoria \n");
	printf("\nOrdenación por inserción \n");
	imprimirVector(v,n);
	ord_ins(v,n);
	imprimirVector(v,n);
    printf("\nOrdenacion de shell\n");
    aleatorio(v,n);
	imprimirVector(v,n);
    ord_shell(v,n);
	imprimirVector(v,n);
}
//--------------------------------------------------------------------
void testAsc(){
	int v[32000], n = 9;
	aleatorio(v,n);
	printf("\nInicializacion ascendente\n");
	printf("\nOrdenación por inserción \n");
	ascendente(v,n);
	imprimirVector(v,n);
    ord_ins(v,n);
	imprimirVector(v,n);
    printf("\nOrdenación por shell \n");
    ascendente(v,n);
	imprimirVector(v,n);
    ord_shell(v,n);
	imprimirVector(v,n);
}
//--------------------------------------------------------------------
void testDesc(){
	int v[32000], n = 9;
	aleatorio(v,n);
	printf("\nInicializacion descendente\n");
	printf("\nOrdenación por inserción \n");
    descendente(v, n);
	imprimirVector(v,n);
    ord_ins(v,n);
	imprimirVector(v,n);
    printf("\nOrdenación por shell \n");
    descendente(v, n);
	imprimirVector(v,n);
    ord_shell(v,n);
	imprimirVector(v,n);
}
//--------------------------------------------------------------------
void testOrdShellAle(){
	int v[32000];int n= 500;int k;double t;double t1;double t2;double t3;
	double a;double b;double c;char *a1 = "n";char *a2= "t";char *a3 = "t/a";
	char *a4 = "t/b";char *a5 = "t/c";
	printf("Test ordenacion de shell con inicializacion aleatorio\n");
	printf("%12s %15.5s %15.6s %15.6s %15.6s \n",a1,a2,a3,a4,a5);
	while(n <= 32000){
		aleatorio(v,n);
		t1 = microsegundos();
		ord_shell(v,n);
		t2 = microsegundos();
		t = t2 - t1;
		a = n; b = pow(n,1.195); c = pow(n,1.5);
		if(t < 500){
			t1 = microsegundos();
			for(k=0;k<10000;k++){
				aleatorio(v,n);
				ord_shell(v,n);
			}
			t2 = microsegundos();
			t3 = t2 - t1;
			t1 = microsegundos();
			for(k=0;k<10000;k++){
				aleatorio(v,n);
			}
			t2 = microsegundos();
			t = (t3 -(t2-t1))/k;
		}
		printf("%12d %15.5f %15.6f %15.6f %15.9f \n",n, t, t/a, t/b, t/c);
		n = n*2;
	}
}
//--------------------------------------------------------------------
void testOrdShellAsc(){
	int v[32000];int n= 500;int k;double t;double t1;double t2;double t3;
	double a;double b;double c;char *a1 = "n";char *a2= "t";char *a3 = "t/a";
	char *a4 = "t/b";char *a5 = "t/c";
	printf("Test ordenacion de shell con inicializacion ascendente\n");
	printf("%12s %15.5s %15.6s %15.6s %15.6s \n",a1,a2,a3,a4,a5);
	while(n <= 32000){
		ascendente(v,n);
		t1 = microsegundos();
		ord_shell(v,n);
		t2 = microsegundos();
		t = t2 - t1;
		a = n; b = n*(log(n)/log(2)); c = pow(n,1.2);
		if(t < 500){
			t1 = microsegundos();
			for(k=0;k<10000;k++){
				ascendente(v,n);
				ord_shell(v,n);
			}
			t2 = microsegundos();
			t3 = t2 - t1;
			t1 = microsegundos();
			for(k=0;k<10000;k++){
				ascendente(v,n);
			}
			t2 = microsegundos();
			t = (t3 -(t2-t1))/k;
		}
		printf("%12d %15.5f %15.6f %15.6f %15.9f \n",n, t, t/a, t/b, t/c);
		n = n*2;
	}
}
//--------------------------------------------------------------------
void testOrdShellDesc(){
	int v[32000];int n= 500;int k;double t;double t1;double t2;double t3;
	double a;double b;double c;char *a1 = "n";char *a2= "t";char *a3 = "t/a";
	char *a4 = "t/b";char *a5 = "t/c";
	printf("Test ordenacion de shell con inicializacion descendiente\n");
	printf("%12s %15.5s %15.6s %15.6s %15.6s \n",a1,a2,a3,a4,a5);
	while(n <= 32000){
		descendente(v,n);
		t1 = microsegundos();
		ord_shell(v,n);
		t2 = microsegundos();
		t = t2 - t1;
		a = pow(n,0.8); b = n*log(n); c = pow(n,1.2);
		if(t < 500){
			t1 = microsegundos();
			for(k=0;k<10000;k++){
				descendente(v,n);
				ord_shell(v,n);
			}
			t2 = microsegundos();
			t3 = t2 - t1;
			t1 = microsegundos();
			for(k=0;k<10000;k++){
				descendente(v,n);
			}
			t2 = microsegundos();
			t = (t3 -(t2-t1))/k;
		}
		printf("%12d %15.5f %15.6f %15.6f %15.9f \n",n, t, t/a, t/b, t/c);
		n = n*2;
	}
}
//--------------------------------------------------------------------
void test_ins_ascendente(){
    double t,t1,t2,ta,tb,a,b,c,c1,c2,c3;
    int k,n = 500, v[32000];
    c1= 0.8;
    c2= 1;
    c3= 1.2;
    char *a1 = "n";	char *a2= "t";	char *a3 = "t/a";
    char *a4 = "t/b";	char *a5 = "t/c";
    printf("Test ordenacion por insercion con inicializacion ascendente\n");
    printf("%12s %15.5s %15.6s %15.6s %15.6s \n",a1,a2,a3,a4,a5);
    while(n <= 32000){
        ta = microsegundos();
        ascendente(v, n);
        ord_ins(v, n);
        tb= microsegundos();
        t = tb-ta;
        if(t < 500){
            ta = microsegundos();
            for(k = 0;k<1000;k++){
                ascendente(v, n);
                ord_ins(v,n);
            }
            tb= microsegundos();
            t1= tb-ta;
            ta = microsegundos();
            for(k = 0;k<1000;k++){
                ascendente(v, n);
            }
            tb= microsegundos();
            t2=tb-ta;
            t = (t1-t2)/k;
        }
        a = pow(n,c1);	b = pow(n,c2);	c = pow(n,c3);
        printf("%12d %15.5f %15.6f %15.7f %15.6f \n",n, t, t/a, t/b, t/c);
        n = n*2;
    }
}
//---------------------------------------------------------------------
void test_ins_descendente(){
    double t,t1,t2,ta,tb,a,b,c,c1,c2,c3;
    int k,n = 500, v[32000];
    c1= 1.8;
    c2= 2;
    c3= 2.2;
    char *a1 = "n";	char *a2= "t";	char *a3 = "t/a";
    char *a4 = "t/b";	char *a5 = "t/c";
    printf("Test ordenacion por insercion con inicializacion descendiente\n");
    printf("%12s %15.5s %15.6s %15.6s %15.6s \n",a1,a2,a3,a4,a5);
    while(n <= 32000){
        ta = microsegundos();
        descendente(v, n);
        ord_ins(v, n);
        tb= microsegundos();
        t = tb-ta;
        if(t < 500){
            ta = microsegundos();
            for(k = 0;k<1000;k++){
                descendente(v, n);
                ord_ins(v,n);
            }
            tb= microsegundos();
            t1= tb-ta;
            ta = microsegundos();
            for(k = 0;k<1000;k++)
                descendente(v, n);
            tb= microsegundos();
            t2=tb-ta;
            t = (t1-t2)/k;
        }
        a = pow(n,c1);	b = pow(n,c2);	c = pow(n,c3);
        printf("%12d %15.5f %15.6f %15.7f %15.7f \n",n, t, t/a, t/b, t/c);
        n = n*2;
    }
}
//-------------------------------------------------------------------
void test_ins_aleatorio(){
    double t,t1,t2,ta,tb,a,b,c,c1,c2,c3;
    int k,n = 500, v[32000];
    c1= 1.8;
    c2= 2;
    c3= 2.2;
    char *a1 = "n";	char *a2= "t";	char *a3 = "t/a";
    char *a4 = "t/b";	char *a5 = "t/c";
    printf("Test ordenacion por insercion con inicializacion aleatorio\n");
    printf("%12s %15.5s %15.6s %15.6s %15.6s \n",a1,a2,a3,a4,a5);
    while(n <= 32000){
        ta = microsegundos();
        aleatorio(v, n);
        ord_ins(v, n);
        tb= microsegundos();
        t = tb-ta;
        if(t < 500){
            ta = microsegundos();
            for(k = 0;k<1000;k++){
                aleatorio(v, n);
                ord_ins(v,n);
            }
            tb= microsegundos();
            t1= tb-ta;
            ta = microsegundos();
            for(k = 0;k<1000;k++)
                aleatorio(v, n);
            tb= microsegundos();
            t2=tb-ta;
            t = (t1-t2)/k;

        }
        a = pow(n,c1);	b = pow(n,c2);	c = pow(n,c3);
        printf("%12d %15.5f %15.6f %15.7f %15.7f \n",n, t, t/a, t/b, t/c);
        n = n*2;
    }
}
//--------------------------------------------------------------------
void inicializar_semilla() {
    srand(time(NULL));
}
//--------------------------------------------------------------------
void aleatorio(int v [], int n) {  /* se generan números pseudoaleatorio entre -n y +n */
    int i, m=2*n+1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
}
//--------------------------------------------------------------------
void ascendente(int v [], int n) {
    int i;
    for (i=0; i <=n; i++)
        v[i] = i;
}
//--------------------------------------------------------------------
void descendente(int v [], int n) {
    int i;
    for (i=0; i<=n; i++)
        v[i] = n-i;
}
//--------------------------------------------------------------------
void imprimirVector(int v[],int n){
	int i;
	 for(i = 0; i<=n;i++){
        if(i<n){
            printf("%d,",v[i]);
        }else{
            printf("%d\n",v[i]);
        }
     }
}

//--------------------------------------------------------------------
