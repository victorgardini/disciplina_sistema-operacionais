#define N 100                           /* número de lugares no buffer */
#define TRUE 1                          
#define FALSE 0

typedef int semaphore;                  /* semáforos são um tipo essencial de int */
semaphore mutex = 1;                    /* controla o acessoo à região crítica */
semaphore empty = N;                    /* conta os lugares vazios no buffer */
semaphore full = 0;                     /* conta os lugares preenchidos no buffer */

void
producer (void){
    int item;

    while (TRUE){
        item = produce_item();          /* gera algo para por no buffer */
        down(&empty);                   /* decresce o contador empty */
        down(&mutex);                   /* entra na região crítica */
        insert_item(item);              /* põe o novo item no buffer */
        up(&mutex);                     /* sai da região crítica */
        up(&full);                      /* incrementa o contador de lugares preenchidos */
    }
    
}

void
consumer(void){
    int item;

    while (TRUE){
        down(&full);                    /* decresce o contador full */
        down(&mutex);                   /* entra na região crítica */
        item = remove_item();           /* pega o item do buffer */
        up(&mutex);                     /* sai da regiao critica */
        up(&empty);                     /* incrementa o contador de lugares vazios */
        consume_item(item);             /* faz algo com o item */
    }
}