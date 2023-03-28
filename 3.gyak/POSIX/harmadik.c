#include <stdio.h>
#include <pthread.h>

#define COUNT 10
#define RANGE 100

int prime_counter[COUNT];

void *count_primes(void *arg){
    int start = *(int*)arg * RANGE;
    int end = start+RANGE;
    int count=0;
    int is_prime;
    
    for(int i=start;i<end;i++){
        is_prime=1;
        for(int j=2;j<end;j++){
            if(i%j==0 && i!=j){
                is_prime=0;
            }
        }
        if(is_prime==1){
            count++;
            if(*(int*)arg==0)
                printf("%d. thread: %d, count: %d\n",*(int*)arg,i,count);
        }
    }
    printf("\n\n");
    prime_counter[*(int*)arg]=count;
    
    return NULL;
}

int main(){
    pthread_t threads[COUNT];
    int thread_args[COUNT];
    
    for(int i=0;i<COUNT;i++){
        thread_args[i]=i;
        pthread_create(&threads[i],NULL,count_primes,&thread_args[i]);
    }
    
    for(int i=0;i<COUNT;i++){
        pthread_join(threads[i],NULL);
    }
    printf("The threads have been terminated.\n");
    
    printf("Prime count: ");
    for(int i=0;i<COUNT;i++){
        printf("%d ",prime_counter[i]);
    }
    
    printf("\n");
}
