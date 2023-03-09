// Kristin Tong
// Oct 25, 2022
// Lab 4 - Matrix Multiplication with Threads
// Step 2 - copying and doubling a matrix using threads

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

// setting values of N and M
#define N 10
#define M 10
int lock = 0;

pthread_t threads[1];

// matrices A and B
double matrixA[N][M];
double matrixB[N][M];

// function declarations
void *copy(void* arg);
void *timestwo(void* arg);
void *printA(void);

int main() {
	int i, j, x=0;

	// initialize matrices A and B
    for (i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            matrixA[i][j] = x++;
    for (i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            matrixB[i][j] = 0;
	
	// print matrix A
	printf("Matrix A: \n");
	printA();

	// create threads
	pthread_create(&threads[0], NULL, *copy, NULL);
	pthread_create(&threads[1], NULL, *timestwo, NULL);

	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);

	printf("Matrix A final: \n");
	printA();

	return 0;
}

void *copy(void* arg) {
	// if locked, wait until unlocked
	if(lock==0){
		usleep(1);
	}
	else {
		int i = 0;
		int j = 0;

		for(i=0; i<N; i++){
			for(j=0; j<M; j++){
				matrixB[i][j] = matrixA[i][j];
			}
		}
	}
}

void *timestwo(void * arg) {
	int i, j;
	for(i=0; i<N; i++){
		for(j=0; j<M; j++){
			matrixA[i][j] = (2 * matrixA[i][j]);
		}
	}
	// set lock
	lock = 1; 
}

void *printA() {
	int i, j;
	for(i = 0; i < N; i++) {
		for(j = 0; j < M; j++) {
			printf("%g ", matrixA[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}