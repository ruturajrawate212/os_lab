#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty, full, mutex;

void* producer(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = rand() % 100 + 1;

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = item;
        printf("[Producer %d] Produced: %d at index %d\n", id, item, in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&full);

        sleep(rand() % 2 + 1);
    }
    printf("[Producer %d] Finished.\n", id);
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[out];
        printf("[Consumer %d] Consumed: %d at index %d\n", id, item, out);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&empty);

        sleep(rand() % 3 + 1);
    }
    printf("[Consumer %d] Finished.\n", id);
    pthread_exit(NULL);
}

int main() {
    printf("\n--- PRODUCER–CONSUMER (Semaphores) ---\n");

    pthread_t prod[NUM_PRODUCERS], cons[NUM_CONSUMERS];
    int id[NUM_PRODUCERS > NUM_CONSUMERS ? NUM_PRODUCERS : NUM_CONSUMERS];

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    for (int i=0; i<NUM_PRODUCERS; i++) {
        id[i] = i+1;
        pthread_create(&prod[i], NULL, producer, &id[i]);
    }

    for (int i=0; i<NUM_CONSUMERS; i++) {
        id[i] = i+1;
        pthread_create(&cons[i], NULL, consumer, &id[i]);
    }

    for (int i=0; i<NUM_PRODUCERS; i++) pthread_join(prod[i], NULL);
    for (int i=0; i<NUM_CONSUMERS; i++) pthread_join(cons[i], NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    printf("\n--- Producer–Consumer Completed ---\n");
    return 0;
}
