#ifndef HEADER_H
#define HEADER_H

#define SIZE 22
#define THREAD_COUNT 5

typedef struct Numbers{
    int *elems[5];
    int sizes[5];
}Numbers;

Numbers numbers;

int thread_sum;

void* sum_of_elements(void *arg);

#endif //HEADER_H