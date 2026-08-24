#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct timeval start, end;
#define MATRIX_SIZE 100
#define NUM_THREADS 4

int matrixI[100][100];
int matrixII[100][100];
int matrixIII[100][100];

// for this here, i need to divide the arrays into sections, and divide these sections over the threads.
struct param {
    int start_row;
    int end_row;
};

void *threadFunc(void *arg) {
    struct param *p = (struct param *)arg;
    //the function expects to receive a pointer to a struct param as an argument, which contains information
    // about the range of rows that the thread should compute in the result matrix (matrixIII).
    // this is why i created this

    //---->> Here u can see the multiplcation operation over the matrix
    for (int i = p->start_row; i < p->end_row; i++) {
        for (int j = 0; j < 100; j++) {
            matrixIII[i][j] = 0;
            for (int b = 0; b < 100; b++) {
                matrixIII[i][j] += matrixI[i][b] * matrixII[b][j];
            }
        }
    }
    free(p); // this is to free the memory i used, to make sure to have a better performance
    pthread_exit(0);
}

int main() {
     gettimeofday(&start, NULL);// i started the timer from here so i will get the real time for all the prgoram till the end


    printf("Welcome to THE MATRIX MULTIPLIER!!\n");

    // Fill matrixI with sequence
    int sequence[] = {1, 2, 1, 2, 3, 5, 9};
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrixI[i][j] = sequence[(j + i * 2) % 7];
        }
    }

    // Fill matrixII with ID * Birthdate
    long long SecMatInt = 1234567890;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (j % 10 == 0)
                SecMatInt = 1234567890;
            matrixII[i][j] = SecMatInt % 10;
            SecMatInt /= 10;
        }
    }

   ///--->>> As I mentioned before, i need to divide the sectioned of the array, and seperte the parts over the threads,
   /// so here i am creating the threads, and seperating the section over the threads
    pthread_t threads[NUM_THREADS]; // this array is used to store the thread IDs of the threads that will be created.
    for (int t = 0; t < NUM_THREADS; t++) {
    //this line dynamically allocates memory for a struct param instance using malloc
    // is used to pass parameters to each thread, specifying the range of rows it should compute in the result matrix
        struct param *params = (struct param *)malloc(sizeof(struct param));
   // it calculates the starting row for the current thread based on the thread index (t) and
   //the total number of threads (NUM_THREADS).
        params->start_row = t * (MATRIX_SIZE / NUM_THREADS);
   //t calculates the ending row for the current thread.note that the ending row is exclusive,
   //meaning the thread will compute rows up to, but not including, end_row.
        params->end_row = (t + 1) * (MATRIX_SIZE / NUM_THREADS);
  //this line creates a new thread using pthread_create. It passes the thread ID (&threads[t]),
  // no specific thread attributes (NULL), the threadFunc function as the thread's start routine, and the params structure as the argument.
        if (pthread_create(&threads[t], NULL, threadFunc, (void *)params) != 0) {
            printf("There is a problem :(\n");
            exit(0);
        }
    }

    // we need to wait for all threads to finish
    for (int t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

   //-->> now the matrix is ready, and i prefer to print it to make sre that i am doing well
      printf("THIS IS matrixIII which is the solution \n");
    for (int h = 0; h < MATRIX_SIZE; h++) {
        for (int o = 0; o < MATRIX_SIZE; o++) {
            printf("%d ", matrixIII[h][o]);
        }
        printf("\n");
    }

    gettimeofday(&end, NULL);
    long long elapsed_time = (end.tv_sec - start.tv_sec) * 1000000LL +
                             (end.tv_usec - start.tv_usec);
    printf("The timer is %lld microseconds\n", elapsed_time);

    return 0;
}

