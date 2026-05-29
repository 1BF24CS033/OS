#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
int *buffer;
int buffer_size;
int max_items;
int in = 0;
int out = 0;

sem_t empty;
sem_t full;
sem_t sem_mutex;

void *producer(void *arg) {
    for (int i = 0; i < max_items; i++) {
        sem_wait(&empty);
        sem_wait(&sem_mutex);

        buffer[in] = i;
        printf("Produced: %d at buffer[%d]\n", i, in);
        in = (in + 1) % buffer_size;
        sem_post(&sem_mutex);
        sem_post(&full);
        usleep(100000); 
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < max_items; i++) {
        sem_wait(&full);
        sem_wait(&sem_mutex);
        int item = buffer[out];
        printf("Consumed: %d from buffer[%d]\n", item, out);
        out = (out + 1) % buffer_size;
        sem_post(&sem_mutex);
        sem_post(&empty);
        
        usleep(150000); 
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    printf("Enter the size of the buffer: ");
    if (scanf("%d", &buffer_size) != 1 || buffer_size <= 0) {
        printf("Invalid buffer size.\n");
        return 1;
    }

    printf("Enter the total number of items to produce/consume: ");
    if (scanf("%d", &max_items) != 1 || max_items <= 0) {
        printf("Invalid number of items.\n");
        return 1;
    }

    buffer = (int *)malloc(buffer_size * sizeof(int));
    if (buffer == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    sem_init(&sem_mutex, 0, 1);
    sem_init(&empty, 0, buffer_size); // Initialized to user's buffer_size
    sem_init(&full, 0, 0);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    free(buffer);
    sem_destroy(&sem_mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}