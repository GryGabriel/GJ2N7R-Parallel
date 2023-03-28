#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *second(void *arg)
{
    printf("A számítás elindult a második szálon.\n");
    sleep(4);
    printf("A számítás befejeződött a második szálon.\n");
    return NULL;
}

int main()
{
    pthread_t thread;
    printf("A számítás elindult az első szálon.\n");
    sleep(8);
    printf("A számítás befejeződött az első szálon.\n");
    pthread_create(&thread, NULL, second, NULL);
    pthread_join(thread, NULL);
    return 0;
}
