#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include<stdlib.h>
#include <time.h>
#include <math.h>
//ordenacion por insercion
void ord_sel(int v[], int n){
    int i, j, minj, minx;

    for(i=0; i<n; i++){
        minj=i;
        minx=v[i];

        for(j=i+1; j<n; j++){
            if(v[j]<minx){
                minj=j;
                minx=v[j];
            }
        }
        v[minj]=v[i];
        v[i]=minx;
    }
}
//ordenacion de shell
void ord_shell(int v[], int n){
    int incremento=n-1;
    int i,j,tmp;
bool seguir;
    do{
        incremento=incremento/2;
        for(i=incremento;i<n;i++){
            tmp=v[i];
            j=i;
            seguir=true;
            while((j-incremento>=0) && seguir){
                if(tmp<v[j-incremento]){
                    v[j]=v[j-incremento];
                    j=j-incremento;

                }else{
                    seguir=false;
                }
            }
            v[j]=tmp;
        }

    }while(incremento!=1);


}

//seleccionar un algoritmo
void algoritmo(int v[], int n, int i){
	if(i==1) ord_sel(v, n);
	if(i==2) ord_shell(v, n);
}
double microsegundos() { /* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 ){
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
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
void ascendente(int v [], int n) {
    int i;
    for (i=0; i < n; i++)
        v[i] = i;
    }
void descendente(int v[], int n){
	int i;
	for (i=n; i>0; i--)
		v[n-i] = i;

}
void iniciarorden(int v[], int n,int elegir){
    if(elegir==1) ascendente(v,n);
    if(elegir==2) descendente(v,n);
    if(elegir==3) aleatorio(v,n);
}

void printVector(int v[], int n){
	int i;
	for(i=0; i<n;i++){
		if(i==(n-1)) printf("%d", v[i]);
			else printf("%d, ", v[i]);
	}
    printf("\n");
}

int ordenado(int v[], int n){
	int i, b, a=v[0];
	for(i=1; i<n;i++){
		b=v[i];
		if(a>b) return 0;
	}
	return 1;
}

void testFunciona(int i){
	int n=15, v[n];
	aleatorio(v, n);
	printf("Inicializacion aleatoria\n");
	printVector(v, n);
	printf("Ordenado? %d\n", ordenado(v, n));
	printf("Ordenando...\n");
	algoritmo(v, n, i);
	printVector(v, n);
	printf("Ordenado? %d\n", ordenado(v, n));
	descendente( v, n);
    printf("Inicialización descendenten\n");
	printVector(v, n);
	printf("Ordenado? %d\n", ordenado(v, n));
	printf("Ordenando...\n");
	algoritmo(v, n, i);
	printVector(v, n);
	printf("Ordenado? %d\n", ordenado(v, n));
}
double calculartiempos(int n,int alg,int orden){
    int v[n],i;
    double t1,t2,t3,t4,t;
    iniciarorden(v,n,orden);
    t1=microsegundos();
    algoritmo(v,n,alg);
    t2=microsegundos();
    t=t2-t1;
    if(t<500){
        t1=microsegundos();
        for(i=0;i<1000;i++){
            iniciarorden(v,n,orden);
            algoritmo(v,n,alg);
        }
        t2=microsegundos();
        t3=microsegundos();
        for(i=0;i<1000;i++){
            iniciarorden(v,n,orden);
        }
        t4=microsegundos();
        printf("(*)");
        t=(t2-t1)-(t4-t3);
        return (t/1000);
    }else{
        printf("   ");
        return t;
    }
}
void printfalgord(int alg, int orden){
    if(alg==1) printf("Ordenacion por seleccion ");
    if(alg==2) printf("Ordenacion por shell ");
    if(orden==1) printf("con inicialización ascendente\n");
    if(orden==2) printf("con inicialización descendente\n");
    if(orden==3) printf("con inicialización aleatorio\n");


}
void test(int orden,int alg,int tamini,int nmax,float p) {
    double t,contador=tamini;
    int i;
	printfalgord(alg,orden);
    printf("%14s%14s%14s","n","t(n)","t(n)/n^");
    printf("%.2f",p-0.2);
	printf("%13s","t(n)/n^");
    printf("%.2f",p);
    printf("%13s","t(n)/n^");
    printf("%.2f\n",p+0.2);

    for(i=1;i<=nmax;i++){
        t=calculartiempos(contador,alg,orden);
        printf("%12.0f%15.3f%15.6f",contador,t,t/pow(contador,p-0.2));
        printf("%15.6f%15.6f\n",t/pow(contador,p),t/pow(contador,p+0.2));
        contador=contador*2;
    }
}

//1=Seleccion
//2=Shell
//1=ascendente
//2=descendente
//3=aleatorio
//hipotesis para shell:  ascendente:1.12, descendente:1.15, aleatorio:1.17
int main(){
    inicializar_semilla();
    test(1,1,500,8,2);
    test(1,1,500,8,2); 
    test(2,1,500,8,2);
    test(3,1,500,8,2);
    test(1,2,500,8,1.12);
    test(2,2,500,8,1.17);
    test(3,2,500,8,1.17);




    return 0;
}