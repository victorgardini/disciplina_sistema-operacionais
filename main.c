/*
 * To compile on Linux, use the following command:
 * $ gcc -pthread main.c -o main
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_THREADS 10

void * print_hello_world(void *tid){ // Function for print thread ID and exit
    //int * valor = (int *) tid;
    printf("Olá, mundo! Boas vindas do thread %d\n", tid);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    // Program creats 10 threads and exit

    pthread_t threads[NUMBER_OF_THREADS];
    int status, i;
    
    for(i = 0; i < NUMBER_OF_THREADS; i++){
        printf("Metodo Main. Criando thread %d\n", i);
        
        // If not use -pthread on compilation command, this line will generate an warning
        // at (void *)i convertion, and an reference error of pthread_create function
        status = pthread_create(&threads[i], NULL, print_hello_world, (void *) i);
        
        
        if (status != 0) { // Some error had happened
            printf("Oops. pthread_create retornou um erro %d\n", status);
            break;
        }
    }

    /*  Sometimes, threads don't finished correctly.
        This loop makes sure that the program take back its execution
        only when threads are finished
    */
    for(i = 0; i < NUMBER_OF_THREADS; i++)
        pthread_join(threads[i], NULL);

    exit(0);
}
