//Santiago Rey Garcia y Alexandre Perez Paredes

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define UMBRAL 100
#define intercambiar(x,y) {int aux=x; x=y; y=aux;}

//------------------------Cabeceras------------------------------------
double microsegundos();
void ord_ins (int v [],int n);
void quicksort(int v[],int n);
void quicksort_aux(int v[],int izq,int der);
void test();
void inicializar_semilla();
void aleatorio(int v [], int n);
void ascendente(int v [], int n);
void descendente(int v [], int n);
void imprimirVector(int v[],int n);
void test_aleatoria();
void test_ascendente();
void test_descendente();

//---------------------------------------------------------------------
int main(){
	int i =0;
	inicializar_semilla();
	test();
	while(i<3){
		test_aleatoria();
        	test_ascendente();
        	test_descendente();
	        i++;
	}

}
//---------------------------------------------------------------------
double microsegundos() {
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}
//---------------------------------------------------------------------
void quicksort(int v[],int n){
	quicksort_aux(v,0,n-1);
	if(UMBRAL > 1 ){
        	ord_ins(v,n);
	}
}
//---------------------------------------------------------------------
void quicksort_aux(int v[],int izq,int der){
	int i,j,x;
	int pivote;
	if(izq + UMBRAL <= der){
		x = (rand() % (der-izq+1)) + izq;
		pivote = v[x];
		intercambiar(v[izq],v[x]);
		i = izq + 1;
		j = der ;
		while(i <= j){
			while(i <= der && v[i] < pivote){
				i++;
			}
			while(j>=izq && v[j] > pivote){
				j--;
			}
			if(i <= j){
				intercambiar(v[i],v[j]);
				i++;
				j--;
			}
		}
		intercambiar(v[izq],v[j]);
		quicksort_aux(v,izq,j-1);
		quicksort_aux(v,j+1,der);
	}
}
//---------------------------------------------------------------------
void ord_ins (int v [],int n){ 
	int i,j,x;
	for(i=1;i < n;i++){
		x=v[i];
		j=i-1;
		while(j>=0 && v[j]>x){
			v[j+1] = v[j];
			j--;
		}
		v[j+1] = x;
	}
}
//---------------------------------------------------------------------
void test(){
	int v[20], n=20;

	printf("\nInicializacion aleatoria: \n");
	aleatorio(v,n);
	imprimirVector(v,n);
	quicksort(v,n);
	imprimirVector(v,n);
	printf("\nInicializacion ascendente \n");
	ascendente(v,n);
	imprimirVector(v,n);
	quicksort_aux(v,0,n-1);
	quicksort(v,n);
	imprimirVector(v,n);
	printf("\nInicializacion descendente \n");
	descendente(v,n);
	imprimirVector(v,n);
	quicksort(v,n);
	imprimirVector(v,n);
}
//---------------------------------------------------------------------
void inicializar_semilla() {
	srand(time(NULL));
}
//---------------------------------------------------------------------
void aleatorio(int v [], int n) {  /* se generan números pseudoaleatorio entre -n y +n */
	int i, m=2*n+1;
	for (i=0; i < n; i++)
		v[i] = (rand() % m) - n;
}
//---------------------------------------------------------------------
void ascendente(int v [], int n) { //inicializa un vector de forma ascendente
	int i;
	for (i=0; i <n; i++)
		v[i] = i;
}
//---------------------------------------------------------------------
void descendente(int v [], int n) { //inicializa un vector de forma descendente
	int i;
	for (i=0; i<n; i++)
		v[i] = n-1-i;
}
//--------------------------------------------------------------------
void imprimirVector(int v[],int n){
	int i;
	for(i = 0; i<n;i++){
		if(i<n-1){
			printf("%d,",v[i]);
		}else{
			printf("%d\n",v[i]);
		}
	}
}
//--------------------------------------------------------------------
void test_aleatoria(){
	double t,t1,t2,ta,tb,a,b,c,c1,c2,c3;
	int k,n = 250, v[2048000];
	c1= 0.8;
	c2= 0.99;
	c3= 1.2;
	char *a1 = "n";	char *a2= "t";	char *a3 = "t/a";
	char *a4 = "t/b";	char *a5 = "t/c";
	printf("Test quicksort con inicializacion aleatoria\n");
	printf("%12s %15.5s %15.6s %15.6s %15.6s \n",a1,a2,a3,a4,a5);
	while(n <= 2048000){
		ta = microsegundos();
		aleatorio(v, n);
		quicksort(v, n);
		tb= microsegundos();
		t = tb-ta;
		if(t < 500){
			ta = microsegundos();
			for(k = 0;k<1000;k++){
				aleatorio(v, n);
				quicksort(v,n);
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
	a = pow(n,c1)*log(n);
	b = pow(n,c2)*log(n);
	c = pow(n,c3)*log(n);
	printf("%12d %15.5f %15.8f %15.8f %15.8f \n",n, t, t/a, t/b, t/c);
	n = n*2;
	}
}
//--------------------------------------------------------------------
void test_ascendente(){
	double t,t1,t2,t3,a,b,c,c1,c2,c3;
	int k,n = 250, v[2048000];
	c1= 0.8;
	c2= 1.05;
	c3= 1.2;
	char *a1 = "n"; char *a2= "t"; char *a3 = "t/a";
	char *a4 = "t/b";char *a5 = "t/c";
	printf("Test quicksort con inicializacion ascendente\n");
	printf("%12s %15.5s %15.6s %15.6s %15.6s \n",a1,a2,a3,a4,a5);
	while(n <= 2048000){
		ascendente(v,n);
		t1 = microsegundos();
		quicksort(v,n);
		t2 = microsegundos();
		t = t2 - t1;

		if(t < 500){
			t1 = microsegundos();
			for(k=0;k<1000;k++){
				ascendente(v,n);
				quicksort(v,n);
			}
			t2 = microsegundos();
			t3 = t2 - t1;
			t1 = microsegundos();
			for(k=0;k<1000;k++){
				ascendente(v,n);
			}
			t2 = microsegundos();
			t = (t3 -(t2-t1))/k;
		}
		a = pow(n,c1)*log(n);
		b = pow(n,c2)*log(n);
		c = pow(n,c3)*log(n);
		printf("%12d %15.5f %15.8f %15.8f %15.8f \n",n, t, t/a, t/b, t/c);
		n = n*2;
	}
}
//--------------------------------------------------------------------
void test_descendente(){
	double t,t1,t2,t3,a,b,c,c1,c2,c3;
	int k,n = 250, v[2048000];
	c1= 0.8;
	c2= 1.025;
	c3= 1.2;
	char *a1 = "n";char *a2= "t";char *a3 = "t/a";
	char *a4 = "t/b";char *a5 = "t/c";
	printf("Test quicksort con inicializacion descendente\n");
	printf("%12s %15.5s %15.6s %15.6s %15.6s \n",a1,a2,a3,a4,a5);
	while(n <= 2048000){
		descendente(v,n);
		t1 = microsegundos();
		quicksort(v,n);
		t2 = microsegundos();
		t = t2 - t1;

		if(t < 500){
			t1 = microsegundos();
			for(k=0;k<1000;k++){
			descendente(v,n);
			quicksort(v,n);
			}
			t2 = microsegundos();
			t3 = t2 - t1;
			t1 = microsegundos();
			for(k=0;k<1000;k++){
			descendente(v,n);
			}
			t2 = microsegundos();
			t = (t3 -(t2-t1))/k;
		}
		a = pow(n,c1)*log(n);
		b = pow(n,c2)*log(n);
		c = pow(n,c3)*log(n);
		printf("%12d %15.5f %15.8f %15.8f %15.8f \n",n, t, t/a, t/b, t/c);
		n = n*2;
	}
}
//--------------------------------------------------------------------
