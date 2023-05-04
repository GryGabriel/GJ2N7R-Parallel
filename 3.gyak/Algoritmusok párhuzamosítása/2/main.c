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
        printf("%d value(s) is/are in the given interval [%d,%d]!\n", count_values_in_a_given_interval(floats, size, min, max), min, max);

    sequential_end = clock();
    time_spent = (double)(sequential_end-sequential_begin)/CLOCKS_PER_SEC;
    printf("Execution time sequentially: %f\n", time_spent);




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

        printf("Odds count: %d and even count: %d using multiple threads\n", odds, evens);

        /**
         * Check if there are any 0 values in the array
         */
        multithread_zeros = 0;



        /**
         * Check if there are any negative values
         */



    /**
     * Search for different values in the float array using multiple threads
    */
        /**
         * Check whether the values absolute value is smaller than 1 
         */


        /**
         * Check if the values are in a given interval
         */


    }else{ //If there are less values than threads
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
        printf("Execution time with multiple threads: %f\n", time_spent);

    free(threads);
    return 0;
}