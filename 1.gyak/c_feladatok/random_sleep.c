#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    srand(time(NULL));
    printf("I will generate a random number in:\n");
    for(int i=3; i>0; i--){
        printf("%d..\n", i);
        sleep(1);
    }
    printf("Here is your random number:%d\n", rand()%(5-1)+1);
    return 0;
}
