/* 
** Universidade Federal de Sao Carlos
** Programação Paralela e Distribuída
** 2020/12
**/


#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <omp.h>

float *A, *B, *C;

int
main(int argc, char *argv[])
{

	int lin_a=100,col_a=100,lin_b=100,col_b=100,lin_c=100,col_c=100;
	int i,j,k;
    int n_threads;

	// printf("Linhas A: ");
	// scanf("%d",&lin_a);
	// printf("Colunas A / Linhas B: ");
	// scanf("%d",&col_a);
	// lin_b=col_a;
	// printf("Colunas B: ");
	// scanf("%d",&col_b);
	// printf("\n");
	lin_c=lin_a;
	col_c=col_b;

	// Alocacao dinamica das matrizes, com linhas em sequencia 
	A=(float *)malloc(lin_a*col_a*sizeof(float));
	B=(float *)malloc(lin_b*col_b*sizeof(float));
	C=(float *)malloc(lin_c*col_c*sizeof(float));

	// Atribucao de valores iniciais as matrizes 
  // Se não descomenentar a linha a seguir, os mesmos valores serão gerados em todas as execuções,
  // o que é bom no caso de fazermos uma análise comparativa.
	// srandom(time(NULL));

	for(i=0; i < lin_a * col_a; i++) 
		A[i]=(float)rand() / (float)RAND_MAX; 

	for(i=0; i < lin_b * col_b; i++) 
		B[i]=(float)rand() / (float)RAND_MAX; 

	// calculo da multiplicacao

    // Variáveis para medida do tempo.
	struct timeval inic, fim;
    struct rusage r1, r2;

    // Obtém tempo e consumo de CPU antes de executar o algoritmo k-means (utilizando threads).
	gettimeofday(&inic, 0);
    getrusage(RUSAGE_SELF, &r1);
 
	for(i=0; i < lin_c; i++) 
		for(j=0; j < col_c; j++) {
			C[i*col_c+j]=0;    
			for(k=0; k < col_a; k++) 
				C[i*col_c+j] = C[i*col_c+j] + A[i*col_a+k] * B[k*col_b+j];
		}

    // Obtém tempo e consumo de CPU após executar o algoritmo k-means (utilizando threads).
	gettimeofday(&fim,0);
	getrusage(RUSAGE_SELF, &r2);

	// printf("\nElapsed time:%f sec\tUser time:%f sec\tSystem time:%f sec\n",
	//  (fim.tv_sec+fim.tv_usec/1000000.) - (inic.tv_sec+inic.tv_usec/1000000.),
	//  (r2.ru_utime.tv_sec+r2.ru_utime.tv_usec/1000000.) - (r1.ru_utime.tv_sec+r1.ru_utime.tv_usec/1000000.),
	//  (r2.ru_stime.tv_sec+r2.ru_stime.tv_usec/1000000.) - (r1.ru_stime.tv_sec+r1.ru_stime.tv_usec/1000000.));

    //  n_threads = omp_get_num_threads();

     FILE *arq;

    arq = fopen(argv[1], "a");
    fprintf(arq, "%lf\n", (fim.tv_sec+fim.tv_usec/1000000.) - (inic.tv_sec+inic.tv_usec/1000000.));
    fclose(arq);

	return(0);
}

