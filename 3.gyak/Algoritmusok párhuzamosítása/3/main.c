#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main(int argc, char *argv[]){ //The first parameter is the array size, the second is thread count
    int array_size;
    char *input;
    int *array;
    int *sequential_prefix_array;

    pthread_t *threads;
    int thread_count;
    int *elements_per_thread;
    int *crew_prefix_array;
    int *erew_prefix_array;
    int erew_k;
    pthread_mutex_t mutex;

    clock_t begin, end;
    double time_spent;
    
    //Get array size from the first parameter
        input = argv[1];
        sscanf(input, "%d", &array_size);

    //Get thread count from the second parameter
        input = argv[2];
        sscanf(input, "%d", &thread_count);
    
    //Allocate memory for the arrays
        array = (int*)malloc(array_size*sizeof(int));
        sequential_prefix_array = (int*)malloc(array_size*sizeof(int));
        threads = (pthread_t*)malloc(thread_count*sizeof(pthread_t));
    
    //Fill the array with random values
        fill_array(array, array_size);
    
    /**
     * Count prefix sequentially
    */
        begin = clock();
        //Calculate prefixes
            sequential_prefix_array[0] = array[0];
            for(int i=1;i<array_size;i++){
                calculate_prefix_sequentially(array, sequential_prefix_array, i);
            }

        end = clock();
        time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
        printf("Execution time with sequential computing: %f seconds!\n", time_spent);

    /**
     * Count prefix with multiple threads
    */
        //Calculate element count per thread
            if(array_size < thread_count) thread_count = array_size;
            elements_per_thread = (int*)malloc(thread_count*sizeof(int));
            count_elements_per_thread(array, array_size, thread_count, elements_per_thread);

        //CREW_PREFIX implementation
        begin = clock();

            crew_prefix_array = (int*)calloc(array_size, sizeof(int));
            pthread_mutex_init(&mutex, NULL);

            for(int i=0;i<thread_count;i++){
                Prefix* crew_struct = (Prefix*)malloc(sizeof(Prefix));
                crew_struct->index = i;
                crew_struct->array = array;
                crew_struct->elements_per_thread = elements_per_thread;
                crew_struct->prefix_array = crew_prefix_array;
                crew_struct->mutex = &mutex;
                pthread_create(&threads[i], NULL, crew_prefix_multithread, crew_struct);
            }
    
            for(int i=0;i<thread_count;i++){
                pthread_join(threads[i], NULL);
                printf("%d.: %d\n", i+1, crew_prefix_array[i]);
            }

            pthread_mutex_destroy(&mutex);
        
        end = clock();
        time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
        printf("Execution time of the crew prefix algorithm with multithread computing: %f seconds!\n", time_spent);

        //EREW_PREFIX implementation
        begin = clock();

            erew_prefix_array = (int*)calloc(array_size, sizeof(int));
            pthread_mutex_init(&mutex, NULL);

            erew_prefix_array[0] = array[0];
            for(int i=0;i<thread_count;i++){
                Prefix* erew_struct = (Prefix*)malloc(sizeof(Prefix));
                erew_struct->index = i;
                erew_struct->array = array;
                erew_struct->elements_per_thread = elements_per_thread;
                erew_struct->prefix_array = erew_prefix_array;
                pthread_create(&threads[i], NULL, erew_prefix_multithread1, erew_struct);
            }

            for(int i=0;i<thread_count;i++){
                pthread_join(threads[i], NULL);
            }

            erew_k=1;
            while(erew_k < array_size){
                for(int i=0;i<thread_count;i++){
                    Prefix* erew_struct = (Prefix*)malloc(sizeof(Prefix));
                    erew_struct->index = i;
                    erew_struct->array = erew_prefix_array;
                    erew_struct->elements_per_thread = elements_per_thread;
                    erew_struct->prefix_array = erew_prefix_array;
                    erew_struct->mutex = &mutex;
                    erew_struct->k = erew_k;
                    pthread_create(&threads[i], NULL, erew_prefix_multithread2, erew_struct);
                }

                for(int i=0;i<thread_count;i++){
                    pthread_join(threads[i], NULL);
                }

                erew_k *= 2;
            }
            
            for(int i=0;i<array_size;i++){
                printf("%d.: %d\n", i+1, erew_prefix_array[i]);
            }
            

            

            pthread_mutex_destroy(&mutex);

        end = clock();
        time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
        printf("Execution time of the erew prefix algorithm with multithread computing: %f seconds!\n", time_spent);

        //OPTIMAL_PREFIX implementation
        begin = clock();

        end = clock();
        time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
        printf("Execution time of the optimal prefix algorithm with multithread computing: %f seconds!\n", time_spent);

    //Free dinamic memory
        free(array);
        free(sequential_prefix_array);
        free(threads);
        free(elements_per_thread);
        free(crew_prefix_array);
        free(erew_prefix_array);

    return 0;
}
