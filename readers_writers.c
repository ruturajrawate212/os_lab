#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex, rw_mutex;
int read_count = 0;

void *reader(void *arg) {
    int id = *(int *)arg;

    pthread_mutex_lock(&mutex);
    read_count++;
    if (read_count == 1)
        pthread_mutex_lock(&rw_mutex);
    pthread_mutex_unlock(&mutex);

    printf("Reader %d is reading\n", id);
    sleep(1);

    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0)
        pthread_mutex_unlock(&rw_mutex);
    pthread_mutex_unlock(&mutex);

    printf("Reader %d finished reading\n", id);
    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;

    pthread_mutex_lock(&rw_mutex);
    printf("Writer %d is writing\n", id);
    sleep(2);
    pthread_mutex_unlock(&rw_mutex);

    printf("Writer %d finished writing\n", id);
    return NULL;
}

int main() {
    printf("\n===== READERS–WRITERS PROBLEM =====\n");

    pthread_t r[3], w[2];
    int rid[3] = {1, 2, 3};
    int wid[2] = {1, 2};

    pthread_mutex_init(&rw_mutex, NULL);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 3; i++)
        pthread_create(&r[i], NULL, reader, &rid[i]);

    for (int i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, &wid[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(r[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);

    pthread_mutex_destroy(&rw_mutex);
    pthread_mutex_destroy(&mutex);

    printf("Readers–Writers execution completed.\n");
    return 0;
}
