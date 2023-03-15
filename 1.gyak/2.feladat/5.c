#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]){
    if(argc!=3){
        printf("Nem megfelelő számú argumentumot adott meg!\n");
        exit(EXIT_FAILURE);
    }else{
        srand(time(NULL));
        int a,z;
        sscanf(argv[1],"%d",&a);
        sscanf(argv[2],"%d",&z);
        
        int random=rand()%(z-a)+a;
        printf("%d\n",random);
    }
    return 0;
}
