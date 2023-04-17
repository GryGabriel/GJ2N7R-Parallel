#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 7
#define THREAD_COUNT 2

typedef struct Numbers{
    int elems[SIZE];
    int sum;
}Numbers;

void *total(void *arg){
    Numbers *numbers = (Numbers *)arg;
    for(int i=0;i<SIZE;i++){
        numbers->sum += numbers->elems[i];
        printf("%d ", numbers->sum);
    }
    printf("\n");
    return NULL;
}

int main(){
    pthread_t threads[THREAD_COUNT];
    Numbers numbers;
    numbers.sum=0;
    
    for(int i=0;i<SIZE;i++){
        numbers.elems[i]=i+1;
    }
    
    for(int i=0;i<THREAD_COUNT;i++){
        pthread_create(&threads[i],NULL,total,(void *)&numbers);
    }
    
    for(int i=0;i<THREAD_COUNT;i++){
        pthread_join(threads[i],NULL);
    }
    
    printf("The sum is: %d\n",numbers.sum);
    return 0;
}
