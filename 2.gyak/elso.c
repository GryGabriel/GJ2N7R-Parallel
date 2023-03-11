#include <stdio.h>

int osszeg(int*, int);
int max(int*, int);
int min(int*, int);

int rekurziv_osszeg(int*, int, int*, int*);
int rekurziv_max(int*,int,int*,int*);
int rekurziv_min(int*,int,int*,int*);

int main(){
    int m;
    printf("Hány elemet tartalmazzon a tömb? ");
    scanf("%d", &m);

    int array[m];
    for(int i=0; i<m; i++){
        printf("Adja meg a tömb %d. elemét: ", i+1);
        scanf("%d", &array[i]);
    }
    //alap
    printf("A tömb elemeinek összege: %d\n", osszeg(array, m));
    printf("A tömb maximum értéke: %d\n", max(array, m));
    printf("A tömb minimum értéke: %d\n", min(array, m));
    //

    //rekurziv
    int osszeg=0, o=0;
    rekurziv_osszeg(array, m, &osszeg, &o);
    printf("A tömb elemeinek összege rekurzív függvényhívással: %d\n", osszeg);
    
    int rmax=array[0], k=0;
    rekurziv_max(array,m,&rmax,&k);
    printf("A tömb elemeinek maximuma rekurzív függvényhívással: %d\n", rmax);
    
    int rmin=array[0], l=0;
    rekurziv_min(array,m,&rmin,&l);
    printf("A tömb elemeinek minimuma rekurzív függvényhívással: %d\n", rmin);
    //
}

int osszeg(int array[], int m){
    int osszeg=0;
    for(int i=0; i<m; i++){
        osszeg+=array[i];
    }
    return osszeg;
}

int max(int array[], int m){
    int max = array[0];
    for(int i=0; i<m; i++){
        if(array[i] > max){
            max = array[i];
        }
    }
    return max;
}

int min(int array[], int m){
    int min = array[0];
    for(int i=0; i<m;i++){
        if(array[i] < min){
            min = array[i];
        }
    }
    return min;
}

int rekurziv_osszeg(int array[], int m, int* osszeg, int* o){
    if(*o < m){
        *osszeg+= array[*o]; 
        (*o)++;
        return rekurziv_osszeg(array,m,osszeg,o);
    }
    return 0;
}
int rekurziv_max(int array[], int m, int *rmax, int *k){
    if(*k < m){
        if(array[*k] > *rmax){
            *rmax=array[*k];
        }
        (*k)++;
        return rekurziv_max(array,m,rmax,k);
    }
    return 0;
}

int rekurziv_min(int array[], int m, int *rmin, int *l){
    if(*l < m){
        if(array[*l] < *rmin){
            *rmin=array[*l];
        }
        (*l)++;
        return rekurziv_min(array,m,rmin,l);
    }
    return 0;
}
