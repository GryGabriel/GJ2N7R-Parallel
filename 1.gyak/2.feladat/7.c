#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int primes(int);

int main(){
    clock_t start = clock(), end;
    int n;
    printf("Mi legyen az intervallum felső határa?\n");
    scanf("%d",&n);
    
    printf("%d\n",primes(n));
    
    end = clock();
    printf("A futási idő: %f volt\n",(double)(end - start) / CLOCKS_PER_SEC);
}

int primes(int n){
    int check,count=0;
    for(int i=1;i<=n;i++){
        check=0;
        for(int j=i;j>0;j--){
            if(i%j==0){
                check++;
            }
        }
        if(check==2){
            count++;
        }
    }
    return count;
}
