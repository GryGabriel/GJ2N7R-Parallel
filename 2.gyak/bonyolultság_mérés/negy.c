#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void iterative_write(int,int*,int,FILE**);
void count_lines_iterative(int,int*,FILE**);

void recursive_write(int,int*,int,FILE**);
void count_lines_recursive(int,int*,FILE**);

void count_empty_lines(int*,FILE**);


int main(int argc, char *argv[]){
    srand(time(NULL));
    
    FILE *fp;
    int length;
    int array_size;
    int line_counter;
    int empty_lines;
    
    //tartalmazza a fájlba véletlenszerűen írandó karakterek ascii kódját
    //int ascii[]={10,32,48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122};
    
    int ascii[]={10,10,10,10,10,10,10,10,73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83,10,10,10,10,10,10,10,10,};
    
    
    //A paraméterben kapott szám mentése integerként
    sscanf(argv[argc-1],"%d",&length);
    
    //Fájlba írás
    fp = fopen("text.txt","w");
    
    array_size = sizeof(ascii)/sizeof(ascii[0]);
    iterative_write(length,ascii,array_size,&fp);
    //recursive_write(length,ascii,array_size,&fp);
    
    fclose(fp);
    
    
    
    //Sorok számának kiszámítása
    fp = fopen("text.txt","r");
    
    line_counter=1;
    count_lines_iterative(length,&line_counter,&fp);
    printf("[ITERATIVE]The file contains %d lines.\n",line_counter);
    
    count_lines_recursive(length,&line_counter,&fp);
    printf("[RECURSIVE]The file contains %d lines.\n",line_counter);
    
    fclose(fp);
    
    
    //Üres sorok száma
    fp = fopen("text.txt","r");
    
    empty_lines=0;
    count_empty_lines(&empty_lines,&fp);
    printf("The number of empty lines is: %d.\n", empty_lines);
    
    fclose(fp);
}


//Fájlba írás iteratív módon
void iterative_write(int length, int *ascii,int array_size, FILE **fp){
    for(int i=0;i<length;i++){
        fprintf(*fp,"%c",ascii[rand() % array_size]);
    }
}

//Fájlba írás rekurzív módon
void recursive_write(int length, int *ascii,int array_size, FILE **fp){
    if(length > 0){
        fprintf(*fp,"%c",ascii[rand() % array_size]);
        recursive_write(length-1,ascii,array_size,fp);
    }else{}q
}


//Visszaadja a sorok számát iteratívan
void count_lines_iterative(int length,int *counter,FILE **fp){
    char ch;
    for(int i=0;i<length;i++){
        ch=fgetc(*fp);
        if(ch=='\n'){
            *counter+=1;
        }
    }
}

//Visszaadja a sorok számát rekurzívan
void count_lines_recursive(int length,int *counter,FILE **fp){
    char ch;
    if(length > 0){
        ch = fgetc(*fp);
        if(ch=='\n'){
            *counter+=1;
        }
        count_lines_recursive(length-1,counter,fp);
    }
}


//Megszámolja az üres sorokat
void count_empty_lines(int *empty_lines,FILE **fp){
    char ch;
    int counter;
    
    counter=0;
    do{
        ch=fgetc(*fp);
        if(ch!='\n'){
            counter++;
        }else if(ch=='\n' || ch==EOF){
            if(counter==0){
                *empty_lines+=1;
            }
            counter=0;
        }
    }while(ch!=EOF);
}
 
