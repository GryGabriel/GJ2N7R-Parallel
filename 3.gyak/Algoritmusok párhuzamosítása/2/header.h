#ifndef HEADER_H 
#define HEADER_H

#include <pthread.h>

/**
 * Fill array containing integer values
*/
void fill_integers(int *integers,int size);

/**
 * Fill array containing float values
*/
void fill_floats(float *floats,int size);

/**
 * Count odd and even numbers in an integer array
*/
void count_parity(int *integers, int size, int *odds, int *evens);

/**
 * Count zeros in an integer array
*/
int count_zeros(int *integers, int size);

/**
 * Count negative values in an integer array
*/
int count_negatives(int *integers, int size);

/**
 * Count values that have absolute value smaller than 1
*/
int count_absolute_values_smaller_than_1(float *floats, int size);

/**
 * Count values that fall in a given interval
*/
int count_values_in_a_given_interval(float *floats, int size, int min, int max);


typedef struct Parity_counter{
    int *array;
    int *odds;
    int *evens;
    int index;
    int *sizes;
    pthread_mutex_t *mutex;
} Parity_counter;

/**
 * Count elements per thread
*/
void count_elements_per_thread(int thread_count, int size, int *sizes);


/**
 * Count odd and even numbers in an integer array
*/
void* count_parity_multithread(void* arg);

typedef struct Zero_counter{
    int *array;
    int *zeros;
    int index;
    int *sizes;
    pthread_mutex_t *mutex;
} Zero_counter;


/**
 * Count zero values in an integer array
*/
void* count_zeros_multithread(void *arg);


typedef struct Negative_counter{
    int *array;
    int *negatives;
    int index;
    int *sizes;
    pthread_mutex_t *mutex;
} Negative_counter;

/**
 * Count negative values in an integer array;
*/
void* count_negatives_multithread(void *arg);


typedef struct Absolute_counter{
    float *array;
    int *abs;
    int index;
    int *sizes;
    pthread_mutex_t *mutex;
} Absolute_counter;

/**
 * Count values that have their absolute value smaller than 1
*/
void* count_abs(void *arg);

typedef struct Interval_counter{
    float *array;
    int *count;
    int index;
    int *sizes;
    int min;
    int max;
    pthread_mutex_t *mutex;
} Interval_counter;

/**
 * Count values that fall in a given interval
*/
void* count_interval(void *arg);

#endif 