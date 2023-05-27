#ifndef HEADER_H
#define HEADER_H

//Save input parameter
    //void save_input_code(char input_code[],  int argc, char *argv[]);
    void save_input(char input_code[], int *thread_count, int *pair_count);

//Check whether the character order is correct, exit if not  
    void check_character_order(char *input_code);

//Sort input parameters into pairs
    void create_pairs(char *input_code, int **number_pairs);

//Count characters in a given text file
    void count_chars_in_text_file(int *text_char_count);

//Save given text file
    void save_text(char *text);

//Decrypt input code sequentially
    void decrypt_code_sequential(int pair_count, int **number_pairs, char *text, char *decrypted_text);

//Decrypt input code with POSIX
    int thread_count;
    typedef struct ThreadStruct{
        char *text;
        char *decrypted_text;
        int **number_pairs;
        int *pairs_per_thread;
        int index;
    } ThreadStruct;

    void decrypt_code_POSIX(int pair_count, int **number_pairs, char *text, char *decrypted_text, int thread_count);

//Decrypt input code with OMP
    void decrypt_code_OMP(int pair_count, int **number_pairs, char *text, char *decrypted_text, int thread_count);

#endif