// ==========================
// dining_philosophers.c - Dining Philosophers
// ==========================

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

pthread_mutex_t forks[N];
sem_t room;

void *philosopher(void *num) {
    int id = *(int *)num;
    while (1) {
        printf("Philosopher %d is thinking\\n", id);
        sem_wait(&room);
        pthread_mutex_lock(&forks[id]);
        pthread_mutex_lock(&forks[(id + 1) % N]);

        printf("Philosopher %d is eating\\n", id);

        pthread_mutex_unlock(&forks[(id + 1) % N]);
        pthread_mutex_unlock(&forks[id]);
        sem_post(&room);
    }
    return NULL;
}

int main() {
    pthread_t phil[N];
    int ids[N];
    sem_init(&room, 0, N - 1);
    for (int i = 0; i < N; i++)
        pthread_mutex_init(&forks[i], NULL);

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&phil[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < N; i++) {
        pthread_join(phil[i], NULL);
    }
    return 0;
}
