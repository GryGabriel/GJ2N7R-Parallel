#include "../include/header.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>  
#include <pthread.h>
#include <omp.h>


// void save_input(char *input_code, int argc, char *argv[]){
//     int counter = 0;
//     for(int i=1;i<argc;i++){
//         strcat(input_code, argv[i]);
//         counter+= strlen(argv[i]);
//         if(i<argc-1){
//             strcat(input_code, " ");
//             counter++;
//         } 
//     }

//     input_code[counter] = '\0';
// }

void save_input(char *input_code, int *thread_count, int *pair_count){

    FILE *fp;

    char ch;
    char get_thread_count[1000];
    int thread_counter;
    int input_counter;

    bool second_line;
    char *token;

    fp = fopen("files/input.txt", "r");

    second_line = false;
    thread_counter = 0;
    input_counter = 0;
    do{
        ch = fgetc(fp);

        if(!second_line){
            if(ch == '\n'){
                second_line = true;
            }
            get_thread_count[thread_counter] = ch;
            thread_counter++;
        }else{
            if(ch == ','){
                (*pair_count)++;
            }
            input_code[input_counter] = ch;
            input_counter++;
        }
    }while(ch != EOF);

    get_thread_count[thread_counter-1] = '\0';
    token = strtok(get_thread_count, "\n");
    *thread_count = atoi(token);

    input_code[input_counter-1] = '\0';

    fclose(fp);
}

void check_character_order(char *input_code){
    int counter=0;
    while(1){
        
        //Check if command-line parameter is given
            if(strlen(input_code) == 0){
                printf("No code has been given!\nTry again!\n");
                exit(1);
            }
        //Check if the first character is a digit
            if(!isdigit(input_code[counter])){
                printf("The text content or order is incorrect!\nTry again\n");
                exit(1);
            }
        //Iterate through the digits
            while(isdigit(input_code[counter])){
                counter++;
            }

        //Check if the last digit is followed by a comma
            if(!(input_code[counter] == ','  && isdigit(input_code[++counter]))){
                printf("The text content or order is incorrect!\nTry again!\n");
                exit(1);
            }

        //Iterate through the digits
            while(isdigit(input_code[counter])){
                counter++;
            }

        //Check if end has been reached
            if(counter == (int)strlen(input_code)){
                break;
            }
        //If not reached check if the last digit is followed by a space
            if(!(input_code[counter] == ' ')){
                printf("The text content or order is incorrect!\nTry again!\n");
                exit(1);
            }else{
                counter++;
            }

    }
}

void create_pairs(char *input_code, int **number_pairs){
    char *token;
    int counter;

    token = strtok(input_code, ",");
    counter = 0;
    while(token != NULL){
        number_pairs[counter][0] = atoi(token);
        token = strtok(NULL, " ");
        number_pairs[counter][1] = atoi(token);
        token = strtok(NULL, ",");
        counter++;
    }
}

void count_chars_in_text_file(int *text_char_count){
    FILE *fp;
    char ch;

    fp = fopen("files/text.txt", "r");

    //count all characters in text file 
    do{
        ch = fgetc(fp);
        (*text_char_count)++;
    }while(ch != EOF);

    fclose(fp);
}

void save_text(char *text){
    FILE *fp;
    char ch;
    int i; //char counter

    fp = fopen("files/text.txt", "r");

    //save each character and increase value of i
    i = 0;
    do{
        ch = fgetc(fp);
        text[i] = ch;
        i++;
    }while(ch != EOF);

    //terminator
        text[i-1] = '\0';

    fclose(fp);
}


void decrypt_code_sequential(int pair_count, int **number_pairs, char *text, char *decrypted_text){
    for(int i=0;i<pair_count;i++){
        int index;
        int row;
        int line_count;
        
        row = number_pairs[i][0];
        index = 0;
        line_count = 0;
        while(line_count < row-1){
            if(text[index] == '\n'){
                line_count++;
            }
            index++;
        }
        index += number_pairs[i][1]-1;
        decrypted_text[i] = text[index];
    }
    decrypted_text[pair_count] = '\0';
}



void count_pairs_per_thread(int pair_count, int **pairs_per_thread, int *thread_count){
    int remaining;

    //Determine letters per thread
        if(pair_count <= *thread_count){ //In case of more threads than letters (or equal) 
            *thread_count = pair_count;
        }
    
    //Allocate memory for pairs_per_thread
        *pairs_per_thread = malloc(*thread_count * sizeof(int));

    //Assign letter count to threads and dispense the remaining
        remaining = pair_count % *thread_count;
        
        for(int i=0;i<*thread_count;i++){
            (*pairs_per_thread)[i] = pair_count / *thread_count;
            if(remaining > 0){
                ((*pairs_per_thread)[i])++;
                remaining--;
            }
        }
}

void* thread_decryption(void *args){ 
    ThreadStruct thread_struct = *(ThreadStruct*)args;
    char *text = thread_struct.text;
    char *decrypted_text = thread_struct.decrypted_text;
    int **number_pairs = thread_struct.number_pairs;
    int *pairs_per_thread = thread_struct.pairs_per_thread;
    int index = thread_struct.index; 

    pthread_mutex_t mutex;

    int start;
    int end;

    start = 0;
    for(int i=0;i<index;i++){
        start += pairs_per_thread[i];
    }
    end = start+ pairs_per_thread[index];

   pthread_mutex_init(&mutex, NULL);

    for(int i=start;i<end;i++){
        int text_index = 0;
        int line_count = 0;
        int row = number_pairs[i][0]-1;
        while(line_count < row){
            if(text[text_index] == '\n'){
                line_count++;
            }
            text_index++;
        }
        pthread_mutex_lock(&mutex);
        text_index+= number_pairs[i][1]-1;
        decrypted_text[i] = text[text_index];
        pthread_mutex_unlock(&mutex);
    }
    pthread_mutex_destroy(&mutex);
    return NULL;
}

void decrypt_code_POSIX(int pair_count, int **number_pairs, char *text, char *decrypted_text, int thread_count){
    int *pairs_per_thread = NULL;
    count_pairs_per_thread(pair_count, &pairs_per_thread, &thread_count);

    pthread_t threads[thread_count];
    ThreadStruct thread_struct[thread_count];

    for(int i=0;i<thread_count;i++){
        thread_struct[i].text = text;
        thread_struct[i].decrypted_text = decrypted_text;
        thread_struct[i].number_pairs = number_pairs;
        thread_struct[i].pairs_per_thread = pairs_per_thread;
        thread_struct[i].index = i;
        pthread_create(&threads[i], NULL, thread_decryption, &thread_struct[i]);
    }

    for(int i=0;i<thread_count;i++){
        pthread_join(threads[i], NULL);
    }

    decrypted_text[pair_count] = '\0';

    free(pairs_per_thread);
}



void decrypt_code_OMP(int pair_count, int **number_pairs, char *text, char *decrypted_text, int thread_count){
    omp_set_num_threads(thread_count);
    #pragma omp parallel for
    for(int i=0;i<pair_count;i++){
        int index;
        int row;
        int line_count;
        
        row = number_pairs[i][0];
        index = 0;
        line_count = 0;
        while(line_count < row-1){
            if(text[index] == '\n'){
                line_count++;
            }
            index++;
        }
        index += number_pairs[i][1]-1;
        decrypted_text[i] = text[index];
    }
    decrypted_text[pair_count] = '\0';
}