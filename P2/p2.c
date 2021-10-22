#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <stdbool.h>

#define VMAX 256000

void OrdenacionSeleccion(int v[], int n) {
    int i, j, minj, minx;
    for (i = 0; i < n - 1; i++) {
        minj = i;
        minx = v[i];
        for (j = i + 1; j < n; j++) {
            if (v[j] < minx) {
                minj = j;
                minx = v[j];
            }
        }
        v[minj] = v[i];
        v[i] = minx;
    }
}

void OrdenacionShell(int v[], int n) {
    int incremento = n, j, i, tmp;
    bool seguir = false;
    div_t aux;
    do {
        aux = div(incremento, 2);
        incremento = aux.quot;

        for (i = incremento + 1; i < n; i++) {
            tmp = v[i];
            j = i;
            seguir = true;

            while (j - incremento >= 0 && seguir) {
                if (tmp < v[j - incremento]) {
                    v[j] = v[j - incremento];
                    j = j - incremento;
                } else {
                    seguir = false;
                }
            }
            v[j] = tmp;
        }

    } while (incremento > 0);
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

void ascendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        v[i] = i + 1;
    }
}

void descendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        v[i] = n - i;
    }
}

void listarvector(int v[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        if (i == 0) {
            printf("[ %2d, ", v[i]);
        } else if (i < n - 1) {
            printf("%2d, ", v[i]);
        } else {
            printf("%2d] \n", v[i]);
        }
    }
}

/*
La funcion comprobar orden tendrá como entrada un vector y su tamaño
y nos devolvera 0 en caso de que el vector no esté ordenado y 1 en caso
de estar ordenado.Comprobamos el orden mirando que el anterior sea inferior 
al siguiente.
*/

int comprobarOrden(int v[], int n) {
    int i = 1, result;
    for (i = 1; i < n; i++) {
        if (v[i - 1] <= v[i]) {
            result = 1;
        } else {
            result = 0;
            break;
        }
    }
    return result;
}

double microsegundos() { /* obtiene la hora del sistema en microsegundos */
    struct timeval t;

    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void test1() {
    int n = 10, v[n];
    ascendente(v, n);
    printf("\n Ascendente \n");
    listarvector(v, n);
    comprobarOrden(v, n);
    printf("\n Descendente \n");
    descendente(v, n);
    listarvector(v, n);
    printf("\n Aleatorio \n");
    aleatorio(v, n);
    listarvector(v, n);
}

void testSeleccion() {
    int n = 10, v[n];

    printf("\n\n Inicializacion Descendente \n\n");
    descendente(v, n);
    listarvector(v, n);
    printf("\n Ordenado : %d \n", comprobarOrden(v, n));
    OrdenacionSeleccion(v, n);
    printf("\n\n Ordenacion por Seleccion \n\n");
    listarvector(v, n);
    printf("\n Ordenado : %d \n", comprobarOrden(v, n));
    printf("\n\n Inicializacion Aleatoria \n\n");
    aleatorio(v, n);
    listarvector(v, n);
    printf("\n Ordenado : %d \n", comprobarOrden(v, n));
    printf("\n\n Ordenacion por Seleccion \n\n");
    OrdenacionSeleccion(v, n);
    listarvector(v, n);
    printf("\n Ordenado : %d \n", comprobarOrden(v, n));
}

void testShell() {
    int n = 10, v[n];
    printf("\n\n Inicializacion Descendente \n\n");
    descendente(v, n);
    listarvector(v, n);
    printf("\n Ordenado : %d \n", comprobarOrden(v, n));
    OrdenacionShell(v, n);
    printf("\n\n Ordenacion por Shell \n\n");
    listarvector(v, n);
    printf("\n Ordenado : %d \n", comprobarOrden(v, n));
    printf("\n\n Inicializacion Aleatoria \n\n");
    aleatorio(v, n);
    listarvector(v, n);
    printf("\n Ordenado : %d \n", comprobarOrden(v, n));
    printf("\n\n Ordenacion por Shell \n\n");
    OrdenacionShell(v, n);
    listarvector(v, n);
    printf("\n Ordenado : %d \n\n", comprobarOrden(v, n));
}

void tiemposShellAsc() {
    int v[VMAX], n = 2000, k = 1000, i;
    double ta, tb, t, c1, c2, c3;
    printf("\nTiempoShellAsc \n\n");
    printf("    n           t(n)        t(n)/n    t(n)/n^1.122  t(n)/n^1.4\n");
    while (n <= VMAX) {
        c1 = pow(n, 1);
        c2 = pow(n, 1.122);
        c3 = pow(n, 1.4);
        ascendente(v, n);
        ta = microsegundos();
        OrdenacionShell(v, n);
        tb = microsegundos();
        t = tb - ta;
        if (t < 500) {
            ta = microsegundos();
            for (i = 0; i < k; i++) {
                ascendente(v, n);
                OrdenacionShell(v, n);
            }
            tb = microsegundos();
            t = tb - ta;
            ta = microsegundos();
            for (i = 0; i < k; i++) {
                ascendente(v, n);
            }
            tb = microsegundos();
            t = (t - (tb - ta)) / k;
            printf("*");
        } else {
            printf(" ");
        }
        printf("%6d %15f    %8f    %9f    %9f\n", n, t, t/c1, t/c2, t/c3);
        n = n * 2;
    }
}

void tiemposShellDesc() {
    int v[VMAX], n = 2000, k = 1000, i;
    double ta, tb, t, c1, c2, c3;
    printf("TiempoShellDesc \n\n");
    printf("    n            t(n)        t(n)/n   t(n)/n^1.118   t(n)/n^1.4\n");
    while (n <= VMAX) {
        c1 = pow(n, 1);
        c2 = pow(n, 1.118);
        c3 = pow(n, 1.4);
        descendente(v, n);
        ta = microsegundos();
        OrdenacionShell(v, n);
        tb = microsegundos();
        t = tb - ta;
        if (t < 500) {
            ta = microsegundos();
            for (i = 0; i < k; i++) {
                descendente(v, n);
                OrdenacionShell(v, n);
            }
            tb = microsegundos();
            t = tb - ta;
            ta = microsegundos();
            for (i = 0; i < k; i++) {
                descendente(v, n);
            }
            tb = microsegundos();
            t = (t - (tb - ta)) / k;
            printf("*");
        } else {
            printf(" ");
        }
        printf("%6d  %15f    %8f    %9f    %9f\n", n, t, t/c1, t/c2, t/c3);
        n = n * 2;
    }
}

void tiemposShellAleatorio() {
    int v[VMAX / 4], n = 500, k = 1000, i;
    double ta, tb, t, c1, c2, c3;
    printf("TiempoShellAleatorio \n\n");
    printf("    n           t(n)         t(n)/n     t(n)/n^1.2   t(n)/n^1.4\n");
    while (n <= VMAX / 4) {
        c1 = pow(n, 1);
        c2 = pow(n, 1.2);
        c3 = pow(n, 1.4);
        aleatorio(v, n);
        ta = microsegundos();
        OrdenacionShell(v, n);
        tb = microsegundos();
        t = tb - ta;
        if (t < 500) {
            ta = microsegundos();
            for (i = 0; i < k; i++) {
                aleatorio(v, n);
                OrdenacionShell(v, n);
            }
            tb = microsegundos();
            t = tb - ta;
            ta = microsegundos();
            for (i = 0; i < k; i++) {
                aleatorio(v, n);
            }
            tb = microsegundos();
            t = (t - (tb - ta)) / k;
            printf("*");
        } else {
            printf(" ");
        }
        printf("%6d  %15f    %8f    %9f    %9f\n", n, t, t/c1, t/c2, t/c3);
        n = n * 2;
    }
}

void tiemposSeleccionAsc() {
    int v[VMAX / 4], n = 500, k = 1000, i;
    double ta, tb, t, c1, c2, c3;
    printf("TiempoSeleccionAsc \n\n");
    printf("    n           t(n)       t(n)/n^1.6    t(n)/n^2    t(n)/n^2.2\n");
    while (n <= VMAX / 4) {
        c1 = pow(n, 1.6);
        c2 = pow(n, 2);
        c3 = pow(n, 2.2);
        ascendente(v, n);
        ta = microsegundos();
        OrdenacionSeleccion(v, n);
        tb = microsegundos();
        t = tb - ta;
        if (t < 500) {
            ta = microsegundos();
            for (i = 0; i < k; i++) {
                ascendente(v, n);
                OrdenacionSeleccion(v, n);
            }
            tb = microsegundos();
            t = tb - ta;
            ta = microsegundos();
            for (i = 0; i < k; i++) {
                ascendente(v, n);
            }
            tb = microsegundos();
            t = (t - (tb - ta)) / k;
            printf("*");
        } else {
            printf(" ");
        }
        printf("%6d  %15f    %8f    %9f    %9f\n", n, t, t/c1, t/c2, t/c3);
        n = n * 2;
    }
}

void tiemposSeleccionDesc() {
    int v[VMAX / 4], n = 500, k = 1000, i;
    double ta, tb, t, c1, c2, c3;
    printf("TiempoSeleccionDesc \n\n");
    printf("    n           t(n)       t(n)/n^1.7    t(n)/n^2    t(n)/n^2.2\n");
    while (n <= VMAX / 4) {
        c1 = pow(n, 1.7);
        c2 = pow(n, 2);
        c3 = pow(n, 2.2);
        descendente(v, n);
        ta = microsegundos();
        OrdenacionSeleccion(v, n);
        tb = microsegundos();
        t = tb - ta;
        if (t < 500) {
            ta = microsegundos();
            for (i = 0; i < k; i++) {
                descendente(v, n);
                OrdenacionSeleccion(v, n);
            }
            tb = microsegundos();
            t = tb - ta;
            ta = microsegundos();
            for (i = 0; i < k; i++) {
                descendente(v, n);
            }
            tb = microsegundos();
            t = (t - (tb - ta)) / k;
            printf("*");
        } else {
            printf(" ");
        }
        printf("%6d  %15f    %8f    %9f    %9f\n", n, t, t/c1, t/c2, t/c3);
        n = n * 2;
    }
}


void tiemposSeleccionAleatorio() {
    int v[VMAX / 4], n = 500, k = 1000, i;
    double ta, tb, t, c1, c2, c3;
    printf("TiempoSeleccionAleatorio \n\n");
    printf("    n           t(n)       t(n)/n^1.7  t(n)/n^1.99   t(n)/n^2.2\n");
    while (n <= VMAX / 4) {
        c1 = pow(n, 1.7);
        c2 = pow(n, 1.99);
        c3 = pow(n, 2.2);
        aleatorio(v, n);
        ta = microsegundos();
        OrdenacionSeleccion(v, n);
        tb = microsegundos();
        t = tb - ta;
        if (t < 500) {
            ta = microsegundos();
            for (i = 0; i < k; i++) {
                aleatorio(v, n);
                OrdenacionSeleccion(v, n);
            }
            tb = microsegundos();
            t = tb - ta;
            ta = microsegundos();
            for (i = 0; i < k; i++) {
                aleatorio(v, n);
            }
            tb = microsegundos();
            t = (t - (tb - ta)) / k;

            printf("*");
        } else {
            printf(" ");
        }
        printf("%6d  %15f    %8f    %9f    %9f\n", n, t, t/c1, t/c2, t/c3);
        n = n * 2;
    }
}

int main() {
    int i = 0;
    inicializar_semilla();
    test1();
    testSeleccion();
    testShell();
    while (i < 3) {
        tiemposShellAsc();
        printf("\n");
        tiemposShellDesc();
        printf("\n");
        tiemposShellAleatorio();
        printf("\n");
        tiemposSeleccionAsc();
        printf("\n");
        tiemposSeleccionDesc();
        printf("\n");
        tiemposSeleccionAleatorio();
        printf("\n");
        i++;
    }
}
