#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define N 5
#define ROUNDS 1    
sem_t forks[N];
sem_t room;

void* philosopher(void* arg) {
    int id=*(int*) arg;
    int left=id;
    int right=(id+1)%N;
    for(int i=0;i<ROUNDS;i++){
        printf("Philosopher %d is thinking\n", id+1);
        usleep(200000);
        sem_wait(&room);
        sem_wait(&forks[left]);
        printf("Philosopher %d picked up left fork %d\n", id+1, left);
        sem_wait(&forks[right]);
        printf("Philosopher %d picked up right fork %d\n", id+1, right);
        printf("Philosopher %d is eating\n", id+1);
        usleep(200000);
        sem_post(&forks[left]);
        sem_post(&forks[right]);
        printf("Philosopher %d put down forks %d and %d\n", id+1, left, right);
        sem_post(&room);
        usleep(150000);
    }
    return NULL;
}

int main() {
    pthread_t ph[N];
    int id[N];
    sem_init(&room, 0, N-1);
    for(int i=0;i<N;i++)
        sem_init(&forks[i], 0, 1);
    for(int i=0;i<N;i++) {
        id[i] = i;
        pthread_create(&ph[i], NULL, philosopher, &id[i]);
    }
    for(int i=0;i<N;i++)
        pthread_join(ph[i], NULL);
    for(int i=0;i<N;i++)
        sem_destroy(&forks[i]);
    sem_destroy(&room);
    return 0;
}