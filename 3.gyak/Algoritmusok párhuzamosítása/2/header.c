#include "header.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

void fill_integers(int *integers,int size){
    srand(time(NULL));
    for(int i=0;i<size;i++){
        integers[i] = -size +  rand()%(2*size);
    }
}

void fill_floats(float *floats,int size){
    srand(time(NULL));
    for(int i=0;i<size;i++){
        floats[i] =  -(float)size + ((float)rand()/(float)(RAND_MAX)) * (2*(float)size);
    }
}

void count_parity(int *integers, int size, int *odds, int *evens){
    for(int i=0; i<size;i++){
        if(integers[i] % 2 == 0){
            *evens+=1;
        }else{
            *odds+=1;
        }
    }
    printf("\n");
}

int count_zeros(int *integers, int size){
    int zeros = 0;
    for(int i=0;i<size;i++){
        if(integers[i] == 0){
            zeros++;
        }
    }
    return zeros;
}

int count_negatives(int *integers, int size){
    int negatives = 0;
    for(int i=0;i<size;i++){
        if(integers[i] < 0){
            negatives++;
        }
    }
    return negatives;
}

int count_absolute_values_smaller_than_1(float *floats, int size){
    int count = 0;
    for(int i=0;i<size;i++){
        if(fabs(floats[i]) < 1){
            count++;            
        }
    }
    return count;
}

int count_values_in_a_given_interval(float *floats, int size, int min, int max){
    int count = 0;
    for(int i=0;i<size;i++){
        if(floats[i] > min && floats[i] < max){
            count++;           
        }
    }
    return count;
}

void count_elements_per_thread(int thread_count, int size, int *sizes){
    for(int i=0;i<thread_count;i++){
        sizes[i] = size/thread_count;
    }

    if(size % thread_count > 0){
        int remainder = size % thread_count;
        int index = 0;
        while(remainder > 0){
            sizes[index]++;
            remainder--;
            if(++index > thread_count) index=0;
        }
    }
}

void* count_parity_multithread(void* arg){
    Parity_counter* args = (Parity_counter*)arg;
    int *array = args->array;
    int *odds = args->odds;
    int *evens = args->evens;
    int index = args->index;
    int *sizes = args->sizes;

    //Calculate the starting index by summing the previous sizes
    int starting_index = 0;
    for(int i=0;i <index;i++){
        starting_index += sizes[i];
    }

    //List through the given elements
    for(int i=starting_index;i<starting_index+sizes[index];i++){
        if(array[i] % 2 == 0){
            pthread_mutex_lock(args->mutex);
            (*evens)++;
            pthread_mutex_unlock(args->mutex);
        }else{
            pthread_mutex_lock(args->mutex);
            (*odds)++;
            pthread_mutex_unlock(args->mutex);
        }
    }

    free(args);
    return NULL;
}

void* count_zeros_multithread(void *arg){
    Zero_counter* args = (Zero_counter*)arg;
    int *array = args->array;
    int index = args->index;
    int *sizes = args->sizes;
    int *zeros = args->zeros;

    //Calculate the starting index by summing the previous sizes
    int starting_index = 0;
    for(int i=0;i <index;i++){
        starting_index += sizes[i];
    }

    //List through the given elements
    for(int i=starting_index;i<starting_index+sizes[index];i++){
        if(array[i] == 0){
            pthread_mutex_lock(args->mutex);
            (*zeros)++;
            pthread_mutex_unlock(args->mutex);
        }
    }

    free(args);
    return NULL;
}

void* count_negatives_multithread(void *arg){
    Negative_counter* args = (Negative_counter*)arg;
    int *array = args->array;
    int index = args->index;
    int *sizes = args->sizes;
    int *negatives = args->negatives;

    //Calculate the starting index by summing the previous sizes
    int starting_index = 0;
    for(int i=0;i <index;i++){
        starting_index += sizes[i];
    }

    //List through the given elements
    for(int i=starting_index;i<starting_index+sizes[index];i++){
        if(array[i] < 0){
            pthread_mutex_lock(args->mutex);
            (*negatives)++;
            pthread_mutex_unlock(args->mutex);
        }
    }

    free(args);
    return NULL;
}

void* count_abs(void *arg){
    Absolute_counter* args = (Absolute_counter*)arg;
    float *array = args->array;
    int index = args->index;
    int *sizes = args->sizes;
    int *abs = args->abs;

    //Calculate the starting index by summing the previous sizes
    int starting_index = 0;
    for(int i=0;i <index;i++){
        starting_index += sizes[i];
    }

    //List through the given elements
    for(int i=starting_index;i<starting_index+sizes[index];i++){
        if(fabs(array[i]) < 1){
            pthread_mutex_lock(args->mutex);
            (*abs)++;
            pthread_mutex_unlock(args->mutex);
        }
    }

    free(args);
    return NULL;
}

void* count_interval(void *arg){
    Interval_counter* args = (Interval_counter*)arg;
    float *array = args->array;
    int index = args->index;
    int *sizes = args->sizes;
    int *counter = args->count;
    int min = args->min;
    int max = args->max;

    //Calculate the starting index by summing the previous sizes
    int starting_index = 0;
    for(int i=0;i <index;i++){
        starting_index += sizes[i];
    }

    //List through the given elements
    for(int i=starting_index;i<starting_index+sizes[index];i++){
        if(array[i] > min && array[i] < max){
            pthread_mutex_lock(args->mutex);
            (*counter)++;
            pthread_mutex_unlock(args->mutex);
        }
    }

    free(args);
    return NULL;
}
