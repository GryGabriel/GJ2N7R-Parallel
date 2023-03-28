#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *other_threads(void *arg){
    int i=*(int*)arg;
    printf("The %d. thread has begun.\n",i);
    sleep(1);
    printf("The %d. thread has stopped.\n",i);
    return NULL;
}

int main(){
    clock_t start_time, end_time;
    
    start_time = clock();
    
    int size=60;
    int thread_args[size];
    pthread_t threads[size];
    
    for(int i=0;i<size;i++){
        thread_args[i] = i+1;
        pthread_create(&threads[i],NULL,other_threads,&thread_args[i]);
    }
    
    for(int i=0;i<size;i++){
        pthread_join(threads[i],NULL);
    }
    
    printf("All threads have been terminated!\n");
    
    end_time = clock();
    
    printf("The program runtime was: %f seconds.\n", (double)(end_time-start_time)/CLOCKS_PER_SEC);
    return 0;
}
