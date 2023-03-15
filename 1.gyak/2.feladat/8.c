#include <stdio.h>
#include <stdlib.h>

void print_int_arrays(int*,int);
void print_float_arrays(double*,int);
void scan_int_arrays(int*,int);
void scan_float_arrays(double*,int);

int main(){
    int int_array[] = {2,10,1000,33,3,73,22};
    double float_array[] = {3.34,5.19,4.2,99.1,111.11};
    
    printf("A tömbök fájlokba való kiírása..\n");
    int int_m = sizeof(int_array)/sizeof(int);
    print_int_arrays(int_array,int_m);
    
    int float_m = sizeof(float_array)/sizeof(double);
    print_float_arrays(float_array,float_m);
    printf("\n");
    
    printf("A tömbök fájlokból való kiolvasása..\n");
    int scan_int_array[int_m];
    scan_int_arrays(scan_int_array,int_m);
    for(int i=0;i<int_m;i++){
        printf("%d ",scan_int_array[i]);
    }
    printf("\n");
    
    double scan_float_array[float_m];
    scan_float_arrays(scan_float_array,float_m);
    for(int i=0;i<float_m;i++){
        printf("%f ",scan_float_array[i]);
    }
    printf("\n");
    
    return 0;
}

void scan_float_arrays(double array[],int m){
    FILE* fp;
    fp = fopen("float_file.txt","r");
    if(fp==NULL){
        printf("A fájl megnyitása sikertelen!\n");
        exit(1);
    }
    for(int i=0;i<m;i++){
        fscanf(fp,"%lf",&array[i]);
    }
    printf("Lebegőpontos tömbbe való írás sikeres!\n");
    fclose(fp);
}

void scan_int_arrays(int array[],int m){
    FILE* fp;
    fp = fopen("int_file.txt","r");
    if(fp==NULL){
        printf("A fájl megnyitása sikertelen!\n");
        exit(1);
    }
    for(int i=0;i<m;i++){
        fscanf(fp,"%d",&array[i]);
    }
    printf("Egész típusú tömbbe való írás sikeres!\n");
    fclose(fp);
}

void print_int_arrays(int array[], int m){
    FILE* fp;
    fp=fopen("int_file.txt","w");
    if(fp==NULL){
        printf("A fájl megnyitása sikertelen!\n");
        exit(1);
    }
    for(int i=0;i<m;i++){
        fprintf(fp,"%d ",array[i]);
    }
    fprintf(fp,"\n");
    printf("Egész típusú tömb fájlba való kiírása sikeres!\n");
    fclose(fp);
}

void print_float_arrays(double array[],int m){
    FILE* fp;
    fp=fopen("float_file.txt","w");
    if(fp==NULL){
        printf("A fájl megnyitása sikertelen!\n");
        exit(1);
    }
    for(int i=0;i<m;i++){
        fprintf(fp,"%f ",array[i]);
    }
    fprintf(fp,"\n");
    printf("Lebegőpontos típusú tömb fájlba való kiírása sikeres!\n");
    fclose(fp);
}
