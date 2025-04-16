#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 4
#define SIZE 20
int array[SIZE] = {1, 3, 7, 4, 5, 7, 8, 9, 10, 7, 11, 12, 7, 13, 14, 7, 15, 16, 7, 17};
int target = 7;

int result[SIZE];
int count = 0;
pthread_mutex_t mutex;

typedef struct {
    int start;
    int end;
} ThreadArgs;

void* thread_func(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;

    for (int i = args->start; i < args->end; ++i) {
        if (array[i] == target) {
            pthread_mutex_lock(&mutex);
            result[count++] = i;
            pthread_mutex_unlock(&mutex);
        }
    }

    pthread_exit(NULL);
}

int compare_desc(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    pthread_t threads[N];
    ThreadArgs args[N];

    pthread_mutex_init(&mutex, NULL);

    int block = SIZE / N;
    for (int i = 0; i < N; ++i) {
        args[i].start = i * block;
        args[i].end = (i == N - 1) ? SIZE : args[i].start + block;

        if (pthread_create(&threads[i], NULL, thread_func, &args[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    for (int i = 0; i < N; ++i) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    qsort(result, count, sizeof(int), compare_desc);

    printf("Найденные индексы значения %d (по убыванию): ", target);
    for (int i = 0; i < count; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}
