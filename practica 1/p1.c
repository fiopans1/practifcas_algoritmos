#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//FUNCIONES:
int sumaSubMax1(int v[], int n) {
    int i, j;
    int estaSuma, sumaMax = 0;
    for (i = 0; i < n; i++) {
        estaSuma = 0;
        for (j = i; j < n; j++) {
            estaSuma += v[j];
            if (estaSuma > sumaMax) {
                sumaMax = estaSuma;
            }
        }
    }
    return sumaMax;
}

int sumaSubMax2(int v[], int n) {
    int j;
    int estaSuma=0, sumaMax=0;
    for(j=0;j<n;j++){
        estaSuma =estaSuma + v[j];
        if(estaSuma > sumaMax){
            sumaMax = estaSuma;
        }else if(estaSuma < 0){
            estaSuma = 0;
        }
    }
    return sumaMax;
}

void inicializar_semilla() {
    srand(time(NULL));
/* se establece la semilla de una nueva serie de enteros pseudo-aleatorios */
}

void aleatorio(int v [], int n) {
    int i, m=2*n+1;
    for (i=0; i < n; i++){
        v[i] = (rand() % m) - n;
    }
/* se generan números pseudoaleatorio entre -n y +n */
}

double microsegundos() { /* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 ){
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void listar_vector(int v[], int n){
    printf("[ ");
    for(int i=0;i<n;i++){
        printf("%3d ",v[i]);
    }
    printf("]");
}

double comprobar(int z){
    double t1,t2,t;
    int v[z];
    aleatorio(v, z);
    t1=microsegundos();
    sumaSubMax1(v, z);
    t2=microsegundos();
    t=t2-t1;
    if(t<500){
        t1=microsegundos();
        for(int i=0;i<1000;i++){
            sumaSubMax1(v,z);
        }
        t2=microsegundos();
        printf("*");
        return ((t2-t1)/1000);
    }else{
        return t;
    }

}
double comprobar1(int z){
    double t1,t2,t;
    int v[z];
    aleatorio(v, z);
    t1=microsegundos();
    sumaSubMax2(v, z);
    t2=microsegundos();
    t=t2-t1;
    if(t<500){
        t1=microsegundos();
        for(int i=0;i<10000;i++){
            sumaSubMax2(v,z);
        }
        t2=microsegundos();
        printf("*");
        return ((t2-t1)/10000);
    }else{
        return t;
    }

}

void test1() {
	int i, a, b;
	int v[6][5]={{ -9,2,-5,-4, 6},  
              { 4,0,9,2,5},  
              { -2,-1,-9,-7,-1},
			  { 9,-2,1,-7,-8},
			  { 15,-2,-5,-4,16},  
              { 7,-5,6,7,-7}};
	printf("test\n");
	printf("%33s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2");
	for (i=0; i<6; i++) {
		listar_vector(v[i], 5);
		a = sumaSubMax1(v[i], 5);
		b = sumaSubMax2(v[i], 5);
		printf("%15d%15d\n", a, b);
	}
}

void test2() {
    int i, a, b;
    int v[9];
    printf("test\n");
    printf("%33s%20s%20s\n", "", "sumaSubMax1", "sumaSubMax2");
    for (i=0; i<10; i++) {
        aleatorio(v, 9);
        listar_vector(v, 9);
        a = sumaSubMax1(v, 9);
        b = sumaSubMax2(v, 9);
        printf("%15d%15d\n", a, b);
    }
}

void test4() {//para sum2
    double t;
    printf("n   t(n)   t(n)/n^1.8   t(n)/n^2   t(n)/n^2.2\n");
    t=comprobar1(500);
    printf("%3d %3f %3f %3.9f %3f\n",500, t, t/pow(500,0.8),t/pow(500,1),t/pow(500,1.2));
    t=comprobar1(1000);
    printf("%3d %3f %3f %3.9f %3f\n",1000, t, t/pow(1000,0.8),t/pow(1000,1),t/pow(1000,1.2));
     t=comprobar1(2000);
    printf("%3d %3f %3f %3.9f %3f\n",2000, t, t/pow(2000,0.8),t/pow(2000,1),t/pow(2000,1.2));
     t=comprobar1(4000);
    printf("%3d %3f %3f %3.9f %3f\n",4000, t, t/pow(4000,0.8),t/pow(4000,1),t/pow(4000,1.2));
     t=comprobar1(8000);
    printf("%3d %3f %3f %3.9f %3f\n",8000, t, t/pow(8000,0.8),t/pow(8000,1),t/pow(8000,1.2));
     t=comprobar1(16000);
    printf("%3d %3f %3f %3.9f %3f\n",16000, t, t/pow(16000,0.8),t/pow(16000,1),t/pow(16000,1.2));
     t=comprobar1(32000);
    printf("%3d %3f %3f %3.9f %3f\n",32000, t, t/pow(32000,0.8),t/pow(32000,1),t/pow(32000,1.2));
}
void test3() {//para sum1
    //int i, a, b;
    //int v[M];
    double t;
    printf("n   t(n)   t(n)/n^1.8   t(n)/n^2   t(n)/n^2.2\n");
    t=comprobar(500);
    printf("%3d %3f %3f %3f %3f\n",500, t, t/pow(500,1.8),t/pow(500,2),t/pow(500,2.2));
    t=comprobar(1000);
    printf("%3d %3f %3f %3f %3f\n",1000, t, t/pow(1000,1.8),t/pow(1000,2),t/pow(1000,2.2));
     t=comprobar(2000);
    printf("%3d %3f %3f %3f %3f\n",2000, t, t/pow(2000,1.8),t/pow(2000,2),t/pow(2000,2.2));
     t=comprobar(4000);
    printf("%3d %3f %3f %3f %3f\n",4000, t, t/pow(4000,1.8),t/pow(4000,2),t/pow(4000,2.2));
     t=comprobar(8000);
    printf("%3d %3f %3f %3f %3f\n",8000, t, t/pow(8000,1.8),t/pow(8000,2),t/pow(8000,2.2));
     t=comprobar(16000);
    printf("%3d %3f %3f %3f %3f\n",16000, t, t/pow(16000,1.8),t/pow(16000,2),t/pow(16000,2.2));
     t=comprobar(32000);
    printf("%3d %3f %3f %3f %3f\n",32000, t, t/pow(32000,1.8),t/pow(32000,2),t/pow(32000,2.2));
}
int main() {
    inicializar_semilla();
    test3();
    test3();
    test3();
    test4();
    test4();
    test4();
    return 0;
}
