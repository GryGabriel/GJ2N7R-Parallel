#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>


int main(int argc, char *argv[]){

    pthread_t *threads;
    char *input;
    int size; //The size of the array
    int thread_count; //The number of threads

    bool complex; //If the input size is smaller then the input thread_count, not all threads are needed and the task becoems easier
    int odds, evens;
    int min, max;

    int *sizes;
    pthread_mutex_t mutex;
    int multithread_zeros;
    int multithread_negative_values;
    int multithread_abs;
    int multithread_fall_in_interval;

    clock_t sequential_begin, sequential_end;
    clock_t multithread_begin, multithread_end;

    double time_spent;

    /**
     * Storing the two input parameters in the 'size' and 'thread_count' variable
    */
    input = argv[1];
    sscanf(input, "%d", &size);
    input = argv[2];
    sscanf(input,"%d", &thread_count);

    int *integers = (int*)calloc(size, sizeof(int));
    float *floats = (float*)calloc(size, sizeof(float)); 

    /**
     * Fill arrays with random numbers 
    */
    fill_integers(integers,size);
    fill_floats(floats,size);


    sequential_begin = clock();

    /**
     * Search for different values in the integer array sequentially 
    */
        /**
         * Check how many odd and even numbers does the array contain 
         */
        odds = 0;
        evens = 0;
        count_parity(integers,size,&odds,&evens);
        printf("The integers contain %d odd and %d even numbers!\n", odds, evens);

        /**
         * Check if there are any 0 values in the array
         */
        printf("The array cotains %d zero(s)!\n", count_zeros(integers,size));

        /**
         * Check if there are any negative values
         */
        printf("The array cotains %d negative values!\n", count_negatives(integers,size));


    /**
     * Search for different values in the float array sequentially
    */ 
        /**
         * Check whether the values' absolute values are smaller than 1 
         */
        printf("%d value(s) has/have the absolute value smaller than 1!\n", count_absolute_values_smaller_than_1(floats, size));

        /**
         * Check if the values are in a given interval
         */
        min = -100;
        max = 100;
        printf("%d value(s) fall(s) in the given interval [%d,%d]!\n", count_values_in_a_given_interval(floats, size, min, max), min, max);

    sequential_end = clock();
    time_spent = (double)(sequential_end-sequential_begin)/CLOCKS_PER_SEC;
    printf("Execution time sequentially: %f!\n\n", time_spent);




//BEGIN MULTITHREAD EXECUTIONS

    multithread_begin = clock();

    /**
     * Allocate memory for the threads 
     * If there are less elements then threads, not all threads are needed
     * In this case the thread_count is equal with the size
    */
        if(size < thread_count){ 
            thread_count = size;
            complex = false;
        }else{
            complex = true;
        }
        threads = malloc(thread_count*sizeof(pthread_t));

    if(complex){ //If there are more values than threads
    /**
     * Create a Parity type structure and calculate element count for all the threads with the count_elements_per_thread function
    */
    sizes = malloc(thread_count*sizeof(int));
    count_elements_per_thread(thread_count,size,sizes);

    /**
     * Search for different values in the integer array using multiple threads
    */   
        /**
         * Check how many odd and even numbers does the array contain 
         */
        odds = 0;
        evens = 0;
        pthread_mutex_init(&mutex, NULL);
        for(int i=0;i<thread_count;i++){
            Parity_counter* counter = (Parity_counter*)malloc(sizeof(Parity_counter));
            counter->array = integers;
            counter->odds = &odds;
            counter->evens = &evens;
            counter->index = i;
            counter->sizes = sizes;
            counter->mutex = &mutex;
            pthread_create(&threads[i], NULL, count_parity_multithread, counter);
        }

        for(int i=0;i<thread_count;i++){
            pthread_join(threads[i], NULL);
        }
        pthread_mutex_destroy(&mutex);

        printf("Odds count: %d and even count: %d using multiple threads!\n", odds, evens);

        /**
         * Check if there are any 0 values in the array
         */
        multithread_zeros = 0;
        pthread_mutex_init(&mutex, NULL);
        for(int i=0;i<thread_count;i++){
            Zero_counter* counter = (Zero_counter*)malloc(sizeof(Zero_counter));
            counter->array = integers;
            counter->index = i;
            counter->sizes = sizes;
            counter->zeros = &multithread_zeros;
            counter->mutex = &mutex;
            pthread_create(&threads[i], NULL, count_zeros_multithread, counter);
        }

         for(int i=0;i<thread_count;i++){
            pthread_join(threads[i], NULL);
        }
        pthread_mutex_destroy(&mutex);

        printf("Zero count: %d using multiple threads!\n", multithread_zeros);

        /**
         * Check if there are any negative values
         */
        multithread_negative_values = 0;
        pthread_mutex_init(&mutex, NULL);
        for(int i=0;i<thread_count;i++){
            Negative_counter* counter = (Negative_counter*)malloc(sizeof(Negative_counter));
            counter->array = integers;
            counter->index = i;
            counter->sizes = sizes;
            counter->negatives = &multithread_negative_values;
            counter->mutex = &mutex;
            pthread_create(&threads[i], NULL, count_negatives_multithread, counter);
        }

        for(int i=0;i<thread_count;i++){
            pthread_join(threads[i], NULL);
        }
        pthread_mutex_destroy(&mutex);

        printf("Negative value count: %d using multiple threads!\n", multithread_negative_values);



    /**
     * Search for different values in the float array using multiple threads
    */
        /**
         * Check whether the values' absolute value is smaller than 1 
         */
        multithread_abs = 0;
        pthread_mutex_init(&mutex, NULL);
        for(int i=0;i<thread_count;i++){
            Absolute_counter* counter = (Absolute_counter*)malloc(sizeof(Absolute_counter));
            counter->array = floats;
            counter->index = i;
            counter->sizes = sizes;
            counter->abs = &multithread_abs;
            counter->mutex = &mutex;
            pthread_create(&threads[i], NULL, count_abs, counter);
        }

        for(int i=0;i<thread_count;i++){
            pthread_join(threads[i], NULL);
        }
        pthread_mutex_destroy(&mutex);

        printf("%d value(s) has/have their absolute value smaller than 1!\n", multithread_abs);

        /**
         * Check if the values are in a given interval
         */
        multithread_fall_in_interval = 0;
        pthread_mutex_init(&mutex, NULL);
        for(int i=0;i<thread_count;i++){
            Interval_counter* counter = (Interval_counter*)malloc(sizeof(Interval_counter));
            counter->array = floats;
            counter->index = i;
            counter->sizes = sizes;
            counter->count = &multithread_fall_in_interval;
            counter->mutex = &mutex;
            counter->min = min;
            counter->max = max;
            pthread_create(&threads[i], NULL, count_interval, counter);
        }

        for(int i=0;i<thread_count;i++){
            pthread_join(threads[i], NULL);
        }
        pthread_mutex_destroy(&mutex);

        printf("%d value(s) fall(s) in the given interval [%d,%d]!\n", multithread_fall_in_interval, min, max);


    }else{ //If there are less values than threads. NOT IMPLEMENTED
    printf("NOT IMPLEMENTED (SIZE OF THE ARRAY IS SMALLER THAN THE NUMBER OF THREADS)!\n\n");
     /**
      * Search for different values in the integer array using multiple threads
      */

        /**
         * Check how many odd and even numbers does the array contain 
         */


        /**
         * Check if there are any 0 values in the array
         */


        /**
         * Check if there are any negative values
         */


        /**
         * Check if the values are in a given interval
         */


    /**
     * Search for different values in the float array using multiple threads
    */
        /**
         * Check how many odd and even numbers does the array contain 
         */


        /**
         * Check if there are any 0 values in the array
         */


        /**
         * Check if there are any negative values
         */


        /**
         * Check whether the values absolute value is smaller than 1 
         */


        /**
         * Check if the values are in a given interval
         */
    

    }

        multithread_end = clock();
        time_spent = (double)(multithread_end - multithread_begin)/CLOCKS_PER_SEC;
        printf("Execution time with multiple threads: %f\n\n!", time_spent);

    free(threads);
    return 0;
}