#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
    srand(time(NULL));
    int a=500,z=10000;
    int random_egesz = a+(rand()%(z-a));
    printf("Random egész: %d\n",random_egesz);
    
    double random_float =(double)a + (((float)rand()/(float)(RAND_MAX)) * ((double)z-(double)a));
    printf("Random lebegőpontos: %f\n", random_float);
}
