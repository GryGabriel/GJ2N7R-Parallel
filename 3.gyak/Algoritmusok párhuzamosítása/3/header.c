#include "header.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void fill_array(int *array, int size){
    srand(time(NULL));
    for(int i=0;i<size;i++){
        array[i] = rand() % 2000;
    }
}

void calculate_prefix_sequentially(int *array, int *sequential_prefix_array, int index){
    sequential_prefix_array[index] = array[index] + sequential_prefix_array[index-1];
}

void count_elements_per_thread(int *array, int array_size, int thread_count, int *elements_per_thread){
    int reminder = array_size%thread_count;

    for(int i=0;i<thread_count;i++){
        elements_per_thread[i] = array_size/thread_count;
        if(reminder-- > 0) elements_per_thread[i]++;
    }
}

void* crew_prefix_multithread(void *arg){
    Prefix* crew_struct = (Prefix*)arg;
    int index = crew_struct->index;
    int *array = crew_struct->array;
    int *elements_per_thread = crew_struct->elements_per_thread;
    int *crew_prefix_array = crew_struct->prefix_array;
    int start_index;
    int end_index;

    //Inicialize start-end indexes
        start_index = 0;
        for(int i=0;i<index;i++){
            start_index+= elements_per_thread[i];
        }
        end_index = start_index+elements_per_thread[index];

        for(int i=start_index;i<end_index;i++){
            for(int j=0;j<=i;j++){
                pthread_mutex_lock(crew_struct->mutex);
                crew_prefix_array[i] += array[j];
                pthread_mutex_unlock(crew_struct->mutex);
            }
        }

    free(crew_struct);

    return NULL;
}

void* erew_prefix_multithread1(void *arg){
    Prefix* erew_struct = (Prefix*)arg;
    int index = erew_struct->index;
    int *array = erew_struct->array;
    int *elements_per_thread = erew_struct->elements_per_thread;
    int *erew_prefix_array = erew_struct->prefix_array;
    int start_index;
    int end_index;

    //Inicialize start-end indexes
        start_index = 0;
        for(int i=0;i<index;i++){
            start_index+= elements_per_thread[i];
        }
        end_index = start_index+elements_per_thread[index];
    //Calculate prefixes
        for(int i=start_index;i<end_index;i++){
            if(i != 0){
                erew_prefix_array[i] = array[i-1] + array[i];
            }
        }

        free(erew_struct);

        return NULL;
}

void* erew_prefix_multithread2(void *arg){
    Prefix* erew_struct = (Prefix*)arg;
    int index = erew_struct->index;
    int *array = erew_struct->array;
    int *elements_per_thread = erew_struct->elements_per_thread;
    int *erew_prefix_array = erew_struct->prefix_array;
    int start_index;
    int end_index;
    int k = erew_struct->k+1;

    //Inicialize start-end indexes
        start_index = 0;
        for(int i=0;i<index;i++){
            start_index+= elements_per_thread[i];
        }
        end_index = start_index+elements_per_thread[index];
    //Calculate prefixes
        for(int i=start_index;i<end_index;i++){
            if(i != 0){
                pthread_mutex_lock(erew_struct->mutex);
                erew_prefix_array[i] = array[i-k] + array[i];
                pthread_mutex_unlock(erew_struct->mutex);
            }
        }

        free(erew_struct);
        return NULL;
}