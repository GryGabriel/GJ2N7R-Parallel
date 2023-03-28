#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_array(int*,int);
void print_array(int*,int);
void diff_array(int*,int,int,int);
int do_elements_differ(int*,int);

int main(){
    int m;
    printf("Hány elemű legyen a tömb?\n");
    scanf("%d",&m);
    
    int array[m];
    fill_array(array,m);
}

void fill_array(int array[], int m){
    srand(time(NULL));
    printf("Mi legyen a tömb elemeinek alsó és felső határa?(Szóközzel elválasztva adja meg!)\n");
    int a,z;
    scanf("%d %d",&a,&z);
    for(int i=0;i<m;i++){
        array[i] = a+rand()%(z-a);
    }
    if(do_elements_differ(array,m)==1){
        printf("A következő tömb elemei egyediek: ");
        print_array(array,m);
    }else{
        printf("A következő tömb elemei még nem egyediek..: ");
        print_array(array,m);
        diff_array(array,m,a,z);
    }
}

void print_array(int array[], int m){
    for(int i=0;i<m;i++){
        printf("%d ",array[i]);
    }
    printf("\n");
}

void diff_array(int array[],int m,int a,int z){
    int check;
    while(1){
        check=0;
        for(int i=0;i<m;i++){
            for(int j=i+1;j<m;j++){
                if(array[i]==array[j]){
                    array[j]=a+rand()%(z-a);
                    check++;
                }
            }
        }
        if(check==0){
            break;
        }
    }
    printf("A következő tömb elemei már egyediek: ");
    print_array(array,m);
}

int do_elements_differ(int array[], int m){
    for(int i=0;i<m;i++){
        for(int j=i+1;j<m;j++){
            if(array[i]==array[j]){
                return 0;
            }
        }
    }
    return 1;
}
