#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Nem megfelelő paraméterszám!\n");
        exit(1);
    }
    FILE* fp = fopen(argv[1],"w");
    if(fp==NULL){
        printf("Fájl megnyitása sikertelen!\n");
        exit(1);
    }
    int m=atoi(argv[2]);    //Az atoi() függvény átváltja egy sztringre mutató pointer
                            //értékét integerre
    int array[m];
    srand(time(NULL));
    clock_t begin_generating = clock();
    for(int i=0;i<m;i++){
        array[i]=rand()%100+1;
    }
    clock_t finish_generating = clock();
    
    clock_t begin_writing = clock();
    for(int i=0;i<m;i++){
        fprintf(fp,"%d ",array[i]);
    }
    clock_t finish_writing = clock();

    double generate_time = (double)(finish_generating-begin_generating) / CLOCKS_PER_SEC;
    double write_time = (double)(finish_writing-begin_writing) / CLOCKS_PER_SEC;
    printf("A véletlenszámok generálásának ideje: %lf\n", generate_time);
    printf("A tömbelemek fájlba írásának ideje:: %lf\n", write_time);
    
    fclose(fp);
    
    return 0;
}
