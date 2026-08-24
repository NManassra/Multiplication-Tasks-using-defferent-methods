/// Student's Name : Student A
/// Student's ID : STUDENT_A
/// Instroctur's Name : Dr. Abdel Salam Sayyad
/// Section : 1
/// Year of Birth : 2004
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define MATRIX_SIZE 100
#define NUM_THREADS 50

int matrixI[100][100];
int matrixII[100][100];
int matrixIII[100][100];

// for this here, i need to divide the arrays into sections, and divide these sections over the threads.
struct param {
    int start_row;
    int end_row;
};

void matrixMultiply(int start_row, int end_row) {
    //---->> Here u can see the multiplcation operation over the matrix
    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrixIII[i][j] = 0;
            for (int b = 0; b < MATRIX_SIZE; b++) {
                matrixIII[i][j] += matrixI[i][b] * matrixII[b][j];
            }
        }
    }
}

void *threadFunc(void *arg) {
    struct param *p = (struct param *)arg;
     //the function expects to receive a pointer to a struct param as an argument, which contains information
    // about the range of rows that the thread should compute in the result matrix (matrixIII).
    // this is why i created this
    matrixMultiply(p->start_row, p->end_row);
    free(p);
    return NULL;
}
///-> the function is responsible for creating a pool of threads, assigning a range of rows to each thread,
/// and then waiting for all threads to complete.
 ///tt also measures the execution time and prints the result matrix along with the total execution time.
void *monitorThread(void *args) {
    struct timeval start_time, end_time; // this to store the time of strarting and ending to measure the excutiong
    gettimeofday(&start_time, NULL); // start timer
    pthread_t threads[NUM_THREADS];// i used this to indicte an array of threads
    pthread_attr_t attr; // here this variable will be used to store and manipulate the attributes of a thread.
    //-->>function takes the address of the attr variable and sets it to the default attributes for a thread.
    //after this line, attr contains default attributes that can be modified as needed.
    pthread_attr_init(&attr);
    int rows_per_thread = MATRIX_SIZE / NUM_THREADS; // we need to calulate the number of rows that each thread will take

    // create threads
    for (int j = 0; j < NUM_THREADS; j++) {
        struct param *params = (struct param *)malloc(sizeof(struct param));// allocate memory for struct param to pass parameters to the thread
        params->start_row = j * rows_per_thread;  // calculate the start and end rows for the current thread
        params->end_row = (j + 1) * rows_per_thread;
        pthread_create(&threads[j], &attr, threadFunc, (void *)params);// create a new thread and pass the thread ID, attributes, threadFunc, and params as arguments
    }
    pthread_attr_destroy(&attr);
    // here plese note that i put this as a solution for te detached threads to make sure that it will work
    //and note that if i kept the for loop, and erased the join line it will work also
    //but i kept it here to make sure that it will print correct results
     for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    gettimeofday(&end_time, NULL);//stop timer
    // calculate the execution time in seconds
    double execution_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1e6;
  printf("THIS IS matrixIII which is the result\n");
   for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", matrixIII[i][j]);
        }
        printf("\n");
    }
    printf("\nthe timer is %f seconds\n", execution_time);
    pthread_exit(NULL);
}


int main() {
    pthread_t monitor_thread;
    pthread_create(&monitor_thread, NULL, monitorThread, NULL);

    printf("Selam, Welcome to THE MATRIX MULTIPLIER!! \n");

    // Initialize matrixI
    int sequence[] = {1, 2, 1, 2, 3, 5, 9};

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            matrixI[i][j] = sequence[(j + i * 2) % 7];
        }
    }

    // Print matrixI
    printf("THIS IS matrixI\n");
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            printf("%d ", matrixI[i][j]);
        }
        printf("\n");
    }

    // Initialize matrixII
    long long SecMatInt = 1234567890;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if (j % 10 == 0)
                SecMatInt = 1234567890;
            matrixII[i][j] = SecMatInt % 10;
            SecMatInt /= 10;
        }
    }

    // Print matrixII
    printf("\nTHIS IS matrixII\n");
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            printf("%d ", matrixII[i][j]);
        }
        printf("\n");
    }

    pthread_join(monitor_thread, NULL);
    return 0;
}
