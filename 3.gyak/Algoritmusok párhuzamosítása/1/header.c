#include "header.h"
#include <stdio.h>
#include <stdlib.h>

void* sum_of_elements(void *arg){
    int index = *(int*)arg;
    int thread_sum = 0;
    int* result = malloc(sizeof(int));
    for(int i=0;i<numbers.sizes[index-1];i++){
        thread_sum += numbers.elems[index-1][i];
    }

    *result = thread_sum;
    
    return (void*) result;
}