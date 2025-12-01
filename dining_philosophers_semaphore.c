#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>

#define NUM_PHILOSOPHERS 3
#define EAT_LIMIT 3

sem_t forks[NUM_PHILOSOPHERS];

void* philosopher(void* arg) {
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    for (int i = 0; i < EAT_LIMIT; i++) {
        printf("[Philosopher %d] Thinking\n", id);
        sleep(rand() % 2 + 1);

        printf("[Philosopher %d] Tries to pick forks\n", id);

        int first = left < right ? left : right;
        int second = left < right ? right : left;

        sem_wait(&forks[first]);
        sem_wait(&forks[second]);

        printf("[Philosopher %d] Eating (%d/%d)\n", id, i+1, EAT_LIMIT);
        sleep(rand() % 2 + 1);

        sem_post(&forks[second]);
        sem_post(&forks[first]);

        printf("[Philosopher %d] Finished eating %d times\n", id, i+1);
    }
    pthread_exit(NULL);
}

int main() {
    printf("\n--- DINING PHILOSOPHERS (Semaphores) ---\n");

    pthread_t phil[NUM_PHILOSOPHERS];
    int id[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        sem_init(&forks[i], 0, 1);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        id[i] = i;
        pthread_create(&phil[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(phil[i], NULL);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        sem_destroy(&forks[i]);

    printf("\n--- Dining Philosophers Completed ---\n");
    return 0;
}
