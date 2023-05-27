#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide numbers as command-line parameters.\n");
        return 1;
    }

    // Concatenate all the numbers into a single string
    char code[1000];

    for(int i=1;i<argc;i++){
        strcat(code,argv[i]);
        if(i<argc-1)
            strcat(code, " ");
    }

    int number_count = argc-1;
    int numbers[number_count][2];


    char *token;
    int number;
    int counter;

    token = strtok(code,",");
    counter = 0;
    while(token != NULL){
        numbers[counter][0] = atoi(token);
        token = strtok(NULL, " ");
        numbers[counter][1] = atoi(token);
                printf("%d\n", numbers[counter][1]);
        token = strtok(NULL, ",");
        counter++;
    }

    for(int i=0;i<number_count;i++){
        printf("%d %d\n", numbers[i][0],numbers[i][1]);
    }

    return 0;
}