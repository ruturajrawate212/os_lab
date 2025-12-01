#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>

#define NUM_READERS 3
#define NUM_WRITERS 2
#define READS_PER_READER 3
#define WRITES_PER_WRITER 3

int read_count = 0;

sem_t rw_mutex, mutex_rw;

void* reader(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < READS_PER_READER; i++) {
        sem_wait(&mutex_rw);
        read_count++;

        if (read_count == 1)
            sem_wait(&rw_mutex);

        sem_post(&mutex_rw);

        printf("[Reader %d] Reading...\n", id);
        sleep(rand() % 2 + 1);

        sem_wait(&mutex_rw);
        read_count--;

        if (read_count == 0)
            sem_post(&rw_mutex);

        sem_post(&mutex_rw);

        printf("[Reader %d] Finished Reading.\n", id);
        sleep(rand() % 2 + 1);
    }
    pthread_exit(NULL);
}

void* writer(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < WRITES_PER_WRITER; i++) {
        sem_wait(&rw_mutex);

        printf("[Writer %d] Writing...\n", id);
        sleep(rand() % 2 + 1);

        printf("[Writer %d] Finished Writing.\n", id);
        sem_post(&rw_mutex);

        sleep(rand() % 2 + 1);
    }
    pthread_exit(NULL);
}

int main() {
    printf("\n--- READER–WRITER PROBLEM (Semaphores) ---\n");

    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int id[NUM_READERS > NUM_WRITERS ? NUM_READERS : NUM_WRITERS];

    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex_rw, 0, 1);

    for (int i=0;i<NUM_READERS;i++){
        id[i] = i+1;
        pthread_create(&readers[i], NULL, reader, &id[i]);
    }

    for (int i=0;i<NUM_WRITERS;i++){
        id[i] = i+1;
        pthread_create(&writers[i], NULL, writer, &id[i]);
    }

    for (int i=0;i<NUM_READERS;i++) pthread_join(readers[i], NULL);
    for (int i=0;i<NUM_WRITERS;i++) pthread_join(writers[i], NULL);

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex_rw);

    printf("\n--- Reader–Writer Completed ---\n");
    return 0;
}
