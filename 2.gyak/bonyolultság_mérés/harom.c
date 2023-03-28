#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_array(double*,int);

int main(){
    srand(time(NULL));
    printf("Hány elemű legyen a lebegőpontos tömb?\n");
    int m;
    scanf("%d",&m);
    double array[m];
    fill_array(array,m);
}

void fill_array(double array, int m){
    
}
