#ifndef HEADER_H
#define HEADER_H

#include <pthread.h>

void fill_array(int *array, int size);

void calculate_prefix_sequentially(int *array, int *sequential_prefix_array, int index);

void count_elements_per_thread(int *array, int array_size, int thread_count, int *elements_per_thread);

typedef struct Prefix {
    int index;
    int *array;
    int *elements_per_thread;
    int *prefix_array;
    int k;
    pthread_mutex_t *mutex;
} Prefix;

void* crew_prefix_multithread(void *arg);

void* erew_prefix_multithread1(void *arg);

void* erew_prefix_multithread2(void *arg);

#endif