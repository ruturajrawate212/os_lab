#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t chopstick[N];

void *philosopher(void *num) {
    int id = *(int *)num;

    for (int meal = 0; meal < 3; meal++) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        if (id % 2 == 0) {
            pthread_mutex_lock(&chopstick[(id + 1) % N]);
            pthread_mutex_lock(&chopstick[id]);
        } else {
            pthread_mutex_lock(&chopstick[id]);
            pthread_mutex_lock(&chopstick[(id + 1) % N]);
        }

        printf("Philosopher %d is eating (meal %d)\n", id, meal + 1);
        sleep(2);

        pthread_mutex_unlock(&chopstick[id]);
        pthread_mutex_unlock(&chopstick[(id + 1) % N]);

        printf("Philosopher %d finished eating\n", id);
    }
    return NULL;
}

int main() {
    printf("\n===== DINING PHILOSOPHERS PROBLEM =====\n");

    pthread_t phil[N];
    int ids[N];

    for (int i = 0; i < N; i++)
        pthread_mutex_init(&chopstick[i], NULL);

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&phil[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(phil[i], NULL);

    for (int i = 0; i < N; i++)
        pthread_mutex_destroy(&chopstick[i]);

    printf("Dining Philosophers execution completed.\n");
    return 0;
}
