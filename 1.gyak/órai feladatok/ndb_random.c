#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
    clock_t begin=clock();
    srand(time(NULL));
    
    int n,a,z;
    printf("Hány darab véletlenszám legyen legenerálva?\n");
    scanf("%d", &n);
    printf("Mi legyen a véletlenszámok alsó és felső határa?(szóközzel elválasztva)\n");
    scanf("%d %d",&a,&z);
    
    int array[n];
    FILE *fp;
    fp=fopen("n_random_szam","a+");
    for(int i=0;i<n;i++){
        array[i]=rand()%(z-a)+a;
        fprintf(fp,"%d ", array[i]);
    }
    fprintf(fp,"\n");
    fclose(fp);
    
    clock_t end=clock();
    double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("%f\n", time_spent);
    return 0;
}
