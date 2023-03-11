//
//  masodik.c
//  
//
//  Created by Garay Gabor on 2023. 03. 10..
//

#include "masodik.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void fill_array(int*,int,int,int);
void diff_array(int*,int,int,int);
int is_array_diff(int*,int);
void array_content(int*,int);

int main(){
    srand(time(NULL));
    int m;
    printf("Hány elemű legyen a tömb?\n");
    scanf("%d", &m);
    int array[m], a, z;
    
    printf("Mi legyen az értékek alsó és felső határa?\n");
    scanf("%d %d", &a, &z);
    
    fill_array(array,m,a,z);
    array_content(array,m);
    is_array_diff(array,m);
    
    diff_array(array,m,a,z);
    array_content(array,m);
    is_array_diff(array,m);
}

void fill_array(int array[], int m, int a, int z){
    for(int i =0; i < m; i++){
        array[i] = rand()%(z-a)+a;
    }
}

void diff_array(int *array, int m, int a, int z){
    int check=0;
    while(1){
        check=0;
        for(int i=0; i<m; i++){
            for(int j=i+1; j<m;j++){
                if(array[i]==array[j]){
                    array[i] = rand()%(z-a)+a;
                    check++;
                }
            }
        }
        if(check==0){
            break;
        }else{
            continue;
        }
    }
}

int is_array_diff(int array[], int m){
    for(int i=0;i<m;i++){
        for(int j=i+1;j<m;j++){
            if(array[i]==array[j]){
                printf("A tömb tartalmaz duplikált eleme(ke)t.\n");
                return 0;
            }
        }
    }
    printf("A tömb elemei egyediek.\n");
    return 1;
}

void array_content(int array[], int m){
    printf("A tömb tartalma:\n");
    for(int i=0; i<m; i++){
        printf("a(z) %d. elem: %d\n", i+1,array[i]);
    }
}
