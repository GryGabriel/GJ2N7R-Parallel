#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    int a = rand()%100+1;
    int b = rand()%100+1;
    int d;
    time_t start = time(NULL),stop;
    while(1){
        printf("Adja meg a(z) %d + %d értékét: \n",a,b);
        scanf("%d",&d);
        if(d==a+b){
            printf("Helyes!\n");
            stop=time(NULL);
            break;
        }
        else continue;
    }
    printf("A válaszidő %ld másodperc volt!\n", stop-start);
}
