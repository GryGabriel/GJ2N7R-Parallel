#include "../include/header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(){

    printf("\n");

    char input_code[10000];
    int thread_count;

    // int pair_count = argc-1;   
    // int number_pairs[pair_count][2];
    int pair_count;
    int **number_pairs;

    char *text;
    int text_char_count;

    char *decrypted_text;
    char *decrypted_text_POSIX;
    char *decrypted_text_OMP;

    clock_t begin, end;
    double time_spent;


    //Save program parameter
        //save_input_code(input_code, argc, argv);
        pair_count = 0;
        thread_count = 0;
        save_input(input_code, &thread_count, &pair_count); 
    
    //Allocate memory for the number_pairs array after pair_count is calculated
        number_pairs = malloc(pair_count*sizeof(int*));
        for(int i=0;i<pair_count;i++){
            number_pairs[i] = malloc(2*sizeof(int));
        }
            

    //Check parameter's character order. Exit if incorrect  
        check_character_order(input_code);

    //Count characters in a file text
        count_chars_in_text_file(&text_char_count);

    //Allocate memory for text and fill it with the file content
        text = malloc(text_char_count+1*sizeof(char)); //+1 for the terminator
        save_text(text);
    //Create pairs representing letters
        create_pairs(input_code, number_pairs);

    /**
     * Sequential computing
    */

        begin = clock();

        //Allocate memory for the decrypted text
            decrypted_text = malloc(pair_count+1 * sizeof(char)); //+1 for the terminator

        //Decrypt input code
            decrypt_code_sequential(pair_count, number_pairs, text, decrypted_text);

        end = clock();

        time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
        printf("Sequential computing took: %lf seconds\n", time_spent);

    /**
     * End of sequential computing
    */

    /**
     * Multithread POSIX computing
    */

        begin = clock();

        //Allocate memory for the decryptex text POSIX
            decrypted_text_POSIX = malloc(pair_count+1 * sizeof(char)); //+1 for the terminator

        //Decrypt input code 
            decrypt_code_POSIX(pair_count, number_pairs, text, decrypted_text_POSIX, thread_count);

        end = clock();
        time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
        printf("Multithread POSIX computing took: %lf seconds\n", time_spent);

    /**
     * End of multithread POSIX computing
    */

   /**
     * Multithread OMP computing
    */

        begin = clock();

        //Allocate memory for the decryptex text OMP
            decrypted_text_OMP = malloc(pair_count+1 * sizeof(char)); //+1 for the terminator

        //Decrypt input code
            decrypt_code_OMP(pair_count, number_pairs, text, decrypted_text_OMP, thread_count);

        end = clock();
        time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
        printf("Multithread OMP computing took: %lf seconds\n", time_spent);

    /**
     * End of multithread OMP computing
    */



    printf("\n");

    //Free allocated memory
        free(decrypted_text);
        for(int i=0;i<pair_count;i++){
            free(number_pairs[i]);
        }
        free(number_pairs);

    return 0;

}
