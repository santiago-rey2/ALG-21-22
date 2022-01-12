//Santiago Rey Garcia y Alexandre Perez Paredes

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

//-------------------Esctructuras de datos----------------------------- 
struct nodo {
	int elem;
	int num_repeticiones;
	struct nodo *izq, *der;
};
typedef struct nodo *posicion;
typedef struct nodo *arbol;
//------------------------Cabeceras------------------------------------
arbol creararbol(); /* devuelve un arbol vacio */
int esarbolvacio(arbol);
posicion buscar(int, arbol);
arbol eliminararbol(arbol); /* borra todos los nodos liberando la
memoria y devolviendo un arbol vacio */
posicion hijoizquierdo(arbol);
posicion hijoderecho(arbol);
int elemento(posicion);
int numerorepeticiones(posicion);
int altura(arbol);
int max(int x,int y);
void visualizar(arbol); /* imprime el contenido del arbol */
void test();
void testTmp();
double microsegundos();
void aleatorio(int v [], int n);
double tiempoInsercion(int v[],int n,arbol *a);
double tiempoBusqueda(int v[],int n,arbol *a);
void testTmp2();
//---------------------------------------------------------------------
int main (){
	int i =0;
	test();
	testTmp();
	while(i<3){
		testTmp2();
		i++;
	}
}
//---------------------------------------------------------------------
static struct nodo *crearnodo(int e) {
	struct nodo *p = malloc(sizeof(struct nodo));
	if (p == NULL) {
	printf("memoria agotada\n"); exit(EXIT_FAILURE);
	}
	p->elem = e;
	p->num_repeticiones = 1;
	p->izq = NULL;
	p->der = NULL;
	return p;
}

//---------------------------------------------------------------------
arbol creararbol(){
	arbol a = NULL;
	return a;
}
//---------------------------------------------------------------------
int esarbolvacio(arbol a){
	return a == NULL;
}
//---------------------------------------------------------------------
posicion buscar(int x, arbol a){
	if(esarbolvacio(a)){
		return NULL;
	}else if(x == a->elem){
		return a;
	}else if(x < a->elem){
		return buscar(x,a->izq);
	}else{
		return buscar(x,a->der);
	}
}
//---------------------------------------------------------------------
arbol eliminararbol(arbol a){
	arbol aux;
	if(esarbolvacio(a)){
		return a;
	}else{
		aux = a->der;
		if(!esarbolvacio(aux)){
			eliminararbol(aux);
		}else{
			free(aux);
		}
		aux = a->izq;
		if(!esarbolvacio(aux)){
			eliminararbol(aux);
		}else{	
			free(aux);
		}
		a = NULL;
	}
	return a;
}
//---------------------------------------------------------------------
posicion hijoizquierdo(arbol a){
	return a->izq;
}
//---------------------------------------------------------------------
posicion hijoderecho(arbol a){
	return a->der;
}
//---------------------------------------------------------------------
int elemento(posicion p){
	return p->elem;
}
////---------------------------------------------------------------------
int numerorepeticiones(posicion p){
	return p->num_repeticiones;
}
////---------------------------------------------------------------------
int altura(arbol a){
	if(esarbolvacio(a))
		return -1;
	else
		return 1 + max(altura(hijoizquierdo(a)),altura(hijoderecho(a))); 
}
//---------------------------------------------------------------------
void visualizar(arbol a){	
	if(!esarbolvacio(a)){
		if(!esarbolvacio(a->izq)){
			printf("(");
			visualizar(a->izq);
			printf(")");
		}
		
		printf(" %d ",a->elem);
		
		if(!esarbolvacio(a->der)){
			printf("(");
			visualizar(a->der);
			printf(")");
		}
	}else{
		printf("()");
	}
}
//---------------------------------------------------------------------
int max(int x,int y){
	if(x > y)
		return x;
	else
		return y;
}
//---------------------------------------------------------------------
arbol insertar(int e, arbol a){
	if (a == NULL)
		return crearnodo(e);
	else if (e < a->elem)
		a->izq = insertar(e, a->izq);
	else if (e > a->elem)
		a->der = insertar(e, a->der);
	else
		a->num_repeticiones++;
	return a;
}
//---------------------------------------------------------------------
void test(){
	arbol a;posicion p;int i;
	a = creararbol();
	printf("arbol vacío: "); visualizar(a);
	printf("\nAltura el árbol: %d\n",altura(a));
	printf("Inserto un 3\n"); a = insertar(3,a);
	printf("Inserto un 1\n"); a = insertar(1,a);
	printf("Inserto un 2\n"); a = insertar(2,a);
	printf("Inserto un 5\n"); a = insertar(5,a);
	printf("Inserto un 4\n"); a = insertar(4,a);
	printf("Inserto un 5\n"); a = insertar(5,a);
	printf("Arbol: "); visualizar(a);
	printf("\nAltura del arbol: %d\n",altura(a));
	for(i=0;i < 7;i++){
		p = buscar(i,a);
		if(p!=NULL)
			printf("busco %d y encuentro %d repetido: %d veces\n",i,p->elem,p->num_repeticiones);
		else
			printf("busco %d y no encontrado \n",i);
	}
	printf("Borramos el arbol liberamos toda la memoria: ");a = eliminararbol(a);
	printf("Arbol vacio : ");visualizar(a);
	printf("\nAltura del arbol: %d\n",altura(a));

}
//---------------------------------------------------------------------
double microsegundos(){
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void testTmp(){
	int i = 8000;arbol a;double t;int v[256000];
	double tb;char *a1 = "n";char *a2= "t_ins(n)";
	char *a3 = "t_bus(n)";
	printf("%7s %10s %10s \n",a1,a2,a3);
	a = creararbol();
	while(i<=256000){
		t = tiempoInsercion(v,i,&a);
		tb = tiempoBusqueda(v,i,&a);
		printf("%7d %10.3f %10.3f\n",i,t,tb);
		a = eliminararbol(a);
		i = i*2;
	}
}
//---------------------------------------------------------------------
void testTmp2(){
	int i = 8000;arbol a;double t;int v[256000];
	double tb;char *a1 = "n";char *a2= "t";char *a3 = "t/a";
	char *a4 = "t/b";char *a5 = "t/c";
	double ci1;double ci2;double ci3;
	printf("Insercion de n elementos aleatorios\n");
	printf("%7s %13s %13s %13s %13s \n",a1,a2,a3,a4,a5);
	a = creararbol();
	while(i<=256000){
		ci1 = i;ci2 = pow(i,0.999)*log(i);ci3 = pow(i,1.5);
		t = tiempoInsercion(v,i,&a);
		printf("%7d %13.3f %13.8f %13.8f %13.8f \n",i,t,t/ci1,t/ci2,t/ci3);
		a = eliminararbol(a);
		i = i*2;
	}
	i=8000;
	printf("Busqueda de n elementos aleatorios\n");
	printf("%7s %13s %13s %13s %13s \n",a1,a2,a3,a4,a5);
	while(i<=256000){
		ci1 = i;ci2 = pow(i,1.121)*log(i);ci3 = pow(i,1.5);
		t = tiempoInsercion(v,i,&a);
		tb = tiempoBusqueda(v,i,&a);
		printf("%7d %13.3f %13.8f %13.8f %13.8f \n",i,tb,t/ci1,tb/ci2,tb/ci3);
		a = eliminararbol(a);
		i = i*2;
	}
}
//---------------------------------------------------------------------
double tiempoInsercion(int v[],int n,arbol *a){
	double t;double t1;double t2;int k;
	aleatorio(v,n);
	t1 = microsegundos();
	for(k=0;k<n;k++){
		*a = insertar(v[k],*a);
	}
	t2 = microsegundos();
	t = t2-t1;
	return t;
}
//---------------------------------------------------------------------
double tiempoBusqueda(int v[],int n,arbol *a){
	double t;double t1;double t2;int k;
	aleatorio(v,n);
	t1 = microsegundos();
	for(k=0;k<n;k++){
		buscar(v[k],*a);
	}
	t2 = microsegundos();
	t = t2-t1;
	return t;
}
//---------------------------------------------------------------------
void aleatorio(int v [], int n) {  /* se generan números pseudoaleatorio entre -n y +n */
	int i, m=2*n+1;
	for (i=0; i < n; i++)
		v[i] = (rand() % m) - n;
}
//---------------------------------------------------------------------
