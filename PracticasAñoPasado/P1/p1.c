#include <stdio.h>
#include <sys/time.h>
#include <math.h>

//---------------------------------------
double microsegundos();
int fib1(int );
int fib2(int );
int fib3(int );
void testFib1();
void testFib2();
void testFib3();
void test();
//---------------------------------------

int main() {
	
	test();
	
	for(int i = 0;i<3;i++){	
		testFib1();
		testFib2();
		testFib3();
	}
}

//Primer algoritmo

int fib1(int n){
	
	int salida=0;
	
	if(n < 2){
			return n;
	}else{
		salida = fib1(n-1)+fib1(n-2);
		return salida;
		}
		
		

}

//Segundo algoritmo

int fib2(int n){
	
	int i = 1;
	int j = 0;
	
	for(int k = 1;k <= n ;k++){
		
		j= i + j;
		i = j-i;
		}
		
		return j;
}

//Tercer_algoritmo

int fib3(int n) {
	
	int i, j, k, h, t;
	i = 1; j = 0; k = 0; h = 1;
	
	while ( n > 0 ) {
		if ((n % 2) != 0) {
			t = j * h;
			j = (i * h) + (j * k) + t;
			i = (i * k) + t;
		}
		t = h * h;
		h = (2 * k * h) + t;
		k = (k * k) + t;
		n = n / 2;
	}
	
	return j;
}

//Test mostrando las primeras 20 lineas

void test(){
	int n,f1,f2,f3;
	n=0;f1=0;f2=0;f3=0;
	
	while(n <= 20){
		f1 =fib1(n);
		f2= fib2(n);
		f3 = fib3(n);
		
		printf("%12d %15d %15d %15d \n",n,f1,f2,f3);
		n++;
		
		}
	printf("---------------------------------------------------------------\n");
}

/* obtiene la hora actual en microsegundos */
double microsegundos() {
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

//---------------------------------------------------
void testFib1(){
	
	double t,t1,t2,taux,a,b,c,c1,c2,c3;
	int k,n = 2;
	c1=1.1;
	c2=(1+sqrt(5))/2;
	c3=2;
	char *a1 = "n";	char *a2= "t";	char *a3 = "t/a";	
	char *a4 = "t/b";	char *a5 = "t/c";
	printf("Test algoritmo 1 \n");
	printf("%12s %15.3s %15.6s %15.6s %15.6s \n",a1,a2,a3,a4,a5);
	while(n <= 32){
		
		t1 = microsegundos();
		fib1(n);
		t2=microsegundos();
		t = t2-t1;
		
		if(t < 500){
			t1 = microsegundos();
			for(k = 0;k<10000;k++)
				fib1(n);
			t2 = microsegundos();
			taux= t2-t1;
			t = taux/k;
			}
			a = pow(c1,n);	b = pow(c2,n);	c = pow(c3,n);
			
		printf("%12d %15.3f %15.6f %15.6f %15.6f \n",n, t, t/a, t/b, t/c);
		n = n*2;
		} 
	printf("---------------------------------------------------------------\n");
}
//----------------------------------------------
void testFib2(){
	
	double t,t1,t2,taux,a,b,c,c1;
	int k,n = 1000;
	c1= 0.8;
	char *a1 = "n";	char *a2= "t";	char *a3 = "t/a";
	char *a4 = "t/b";	char *a5 = "t/c";
	printf("Test algoritmo 2 \n");
	printf("%12s %15.3s %15.6s %15.6s %15.6s \n",a1,a2,a3,a4,a5);
	while(n <= 10000000){
		
		t1 = microsegundos();
		fib2(n);
		t2=microsegundos();
		t = t2-t1;
		
		if(t < 500){
			t1 = microsegundos();
			for(k = 0;k<10000;k++)
				fib2(n);
			t2 = microsegundos();
			taux= t2-t1;
			t = taux/k;
			}
			a = pow(n,c1);	b = n;	c = n*log(n);
			
		printf("%12d %15.3f %15.6f %15.6f %15.6f \n",n, t, t/a, t/b, t/c);
		n = n*10;
		} 
	printf("---------------------------------------------------------------\n");
}
//---------------------------------------------------

void testFib3(){
	
	double t,t1,t2,taux,a,b,c,c1;
	int k,n = 1000;
	c1= 0.5;
	char *a1 = "n";	char *a2= "t";	char *a3 = "t/a";
		char *a4 = "t/b";	char *a5 = "t/c";
	printf("Test algoritmo 3 \n");
	printf("%12s %15.3s %15.6s %15.6s %15.6s \n",a1,a2,a3,a4,a5);
		while(n <= 10000000){
		
		t1 = microsegundos();
		fib3(n);
		t2=microsegundos();
		t = t2-t1;
		
		if(t < 500){
			t1 = microsegundos();
			for(k = 0;k<10000;k++)
				fib3(n);
			t2 = microsegundos();
			taux= t2-t1;
			t = taux/k;
			}
			a = sqrt(log(n));	b = log(n);	c = pow(n,c1);
			
		printf("%12d %15.3f %15.6f %15.6f %15.6f \n",n, t, t/a, t/b, t/c);
		n = n*10;
		} 
	printf("---------------------------------------------------------------\n");
}

