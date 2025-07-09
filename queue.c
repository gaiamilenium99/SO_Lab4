// ==========================
// queue.c - Thread-Safe Queue
// ==========================

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define QUEUE_SIZE 5

typedef struct {
    int items[QUEUE_SIZE];
    int front, rear, count;
    pthread_mutex_t lock;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} ThreadSafeQueue;

void init_queue(ThreadSafeQueue *q) {
    q->front = 0;
    q->rear = 0;
    q->count = 0;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->not_empty, NULL);
    pthread_cond_init(&q->not_full, NULL);
}

void enqueue(ThreadSafeQueue *q, int item) {
    pthread_mutex_lock(&q->lock);
    while (q->count == QUEUE_SIZE) {
        pthread_cond_wait(&q->not_full, &q->lock);
    }
    q->items[q->rear] = item;
    q->rear = (q->rear + 1) % QUEUE_SIZE;
    q->count++;
    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->lock);
}

int dequeue(ThreadSafeQueue *q) {
    pthread_mutex_lock(&q->lock);
    while (q->count == 0) {
        pthread_cond_wait(&q->not_empty, &q->lock);
    }
    int item = q->items[q->front];
    q->front = (q->front + 1) % QUEUE_SIZE;
    q->count--;
    pthread_cond_signal(&q->not_full);
    pthread_mutex_unlock(&q->lock);
    return item;
}

void *producer(void *arg) {
    ThreadSafeQueue *q = (ThreadSafeQueue *)arg;
    for (int i = 0; i < 10; i++) {
        printf("Producer enqueues %d\\n", i);
        enqueue(q, i);
    }
    return NULL;
}

void *consumer(void *arg) {
    ThreadSafeQueue *q = (ThreadSafeQueue *)arg;
    for (int i = 0; i < 10; i++) {
        int item = dequeue(q);
        printf("Consumer dequeues %d\\n", item);
    }
    return NULL;
}

int main() {
    ThreadSafeQueue q;
    init_queue(&q);
    pthread_t prod, cons;
    pthread_create(&prod, NULL, producer, &q);
    pthread_create(&cons, NULL, consumer, &q);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    return 0;
}
