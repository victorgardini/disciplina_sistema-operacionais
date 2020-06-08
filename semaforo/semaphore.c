#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 1000000000  /* quantos números eu posso produzir */

pthread_mutex_t the_mutex;
pthread_cond_t condc, condp; /* usado para sinalização */
int buffer = 0; /* buffer usado entre produtos e consumidor */

void * producer (void * ptr){
    int i;

    for (i = 1; i < MAX; i++){
        pthread_mutex_lock(&the_mutex); /* obtém acesso exclusivo ao buffer */
        while (buffer != 0)
            pthread_cond_wait(&condp, &the_mutex);
        buffer = i; /* poe item no buffer */
        pthread_cond_signal(&condc); /* acorda o consumidor */
        pthread_mutex_unlock(&the_mutex); /* libera acesso ao buffer */
    }
    pthread_exit(0);
}

void * consumer (void * ptr){ /* dados do consumidor */
    int i;

    for (i = 1; i < MAX; i++){
        pthread_mutex_lock(&the_mutex); /* obtém acesso exclusivo ao buffer */
        while (buffer == 0)
            pthread_cond_wait(&condc, &the_mutex);
        buffer = 0;
        pthread_cond_signal(&condp);        /* acorda o produtor */
        pthread_mutex_unlock(&the_mutex); /* libera acesso ao buffer */
    }
    pthread_exit(0);
}

int main() {
    pthread_t pro, con;
    pthread_mutex_init(&the_mutex, 0);
    
    pthread_cond_init(&condc, 0);
    pthread_cond_init(&condp, 0);

    pthread_create(&con, 0, consumer, 0);
    pthread_create(&pro, 0, producer, 0);

    pthread_join(pro, 0);
    pthread_join(con, 0);

    pthread_cond_destroy(&condc);
    pthread_cond_destroy(&condp);

    pthread_mutex_destroy(&the_mutex);

    return 0;
}