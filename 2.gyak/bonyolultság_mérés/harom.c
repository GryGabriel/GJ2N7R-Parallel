#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

void fill_array(double*,int);
bool check_inc_monotony(double*,int);
void array_out(double*,int);
void binary_search(double*,int,double);

int main(){
    srand(time(NULL));
    
    int m;
    int value;
    
    printf("Hány elemű legyen a lebegőpontos tömb?\n");
    scanf("%d",&m);
    
    //tömb feltöltése
    double array[m];
    fill_array(array,m);
    
    //bináris keresés
    value=((double)rand()/(double)(RAND_MAX)) * (double)(5);
    binary_search(array,m,value);
}

//Tömb elemeinek kiíratása
void array_out(double *array, int m){
    for(int i=0;i<m;i++){
        printf("%f ", array[i]);
    }
    printf("\n");
}

//Tömb feltöltése
void fill_array(double *array, int m){
    for(int i=0;i<m;i++){
        array[i] = ((double)rand()/(double)(RAND_MAX)) * (double)(5);
    }
    array_out(array,m);
    //monotonitás vizsgálata, majd tömb feltöltése új értékekkel addig, amíg monoton nem lesz
    if(!check_inc_monotony(array,m)){
        fill_array(array,m);
    }
}

//Tömb monotonitásának vizsgálata
bool check_inc_monotony(double *array, int m){
    bool monoton = true;
    for(int i=0;i<m;i++){
        for(int j=i+1;j<m;j++){
            if(array[j] < array[i]) return false;
        }
    }
    return true;
}

//Megkeresi a keresett lebegőpontos értékhez legközelebbi tömbértéket
void binary_search(double *array, int m, double value){
    double median;

    if(m%2==0){
        median=array[(int)round(m/2)];
    }else{
        median=array[(int)round(m/2)];
    }
    
    if(median==){}
}
