#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

int main(){
    srand(time(NULL));
    pthread_t threads[THREAD_COUNT];
    int elems_per_thread;
    int sequential_sum;
    int thread_sum, *return_sum;
    clock_t begin, end;
    double time_spent;

    elems_per_thread = SIZE/THREAD_COUNT;
    /**
     * Ha minden szálnak azonos darabszámú elem jut
    */
    if(SIZE%THREAD_COUNT == 0){ 
        /**
         * Tömb feltöltése véletlenszerű elemekkel
        */
        for(int i=0; i< THREAD_COUNT; i++){
            numbers.elems[i] = malloc(elems_per_thread * sizeof(int));
            numbers.sizes[i] = SIZE/THREAD_COUNT;
            for(int j=0; j< elems_per_thread; j++){
                numbers.elems[i][j] = rand() % 50;
            }
        }

    /**
     * Ha eltérő darabszámú elemet tartalmaznak a szálak 
    */
    }else {
        /**
         * Tömb feltöltése véletlenszerű elemekkel
        */
        for(int i=0; i< THREAD_COUNT; i++){
            if(i < THREAD_COUNT-1){
                numbers.elems[i] = malloc(elems_per_thread * sizeof(int));
                numbers.sizes[i] = SIZE/THREAD_COUNT;
                for(int j=0; j< elems_per_thread; j++){
                    numbers.elems[i][j] = rand() % 50;
                }
            }else{
                numbers.elems[THREAD_COUNT-1] = malloc((SIZE/THREAD_COUNT + SIZE%THREAD_COUNT) * sizeof(int));
                numbers.sizes[i] = (SIZE/THREAD_COUNT + SIZE%THREAD_COUNT);
                for(int j=0; j< numbers.sizes[i]; j++){
                    numbers.elems[THREAD_COUNT-1][j] = rand() % 50;
                }
           } 
        }
    }



    /**
     * Sequential computing
    */
    begin = clock();

    sequential_sum = 0;
    for(int i=0; i<THREAD_COUNT;i++){
        for(int j=0; j<numbers.sizes[i];j++){
            sequential_sum += numbers.elems[i][j];
        }
    }

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("The sequential sum is:%d\n", sequential_sum);
    printf("Execution time sequentially: %f\n\n", time_spent);
    
    /**
     * Computing using threads 
    */
    begin = clock();

    for(int i=0; i< THREAD_COUNT; i++){
        pthread_create(&threads[i],NULL,sum_of_elements, (void*)&i);
    }

    thread_sum = 0;
    for(int i=0; i< THREAD_COUNT; i++){
        pthread_join(threads[i],(void**) &return_sum);
        thread_sum += *return_sum;
        printf("%d\n", *return_sum);
    }
    
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("The sum using threads is: %d\n", thread_sum);
    printf("Execution time using threads: %f\n\n", time_spent);

    return 0;
}