#include <stdio.h>
#include <pthread.h>      


void *getTID(void *arg) {
    printf("Thread with ID = %lu, running\n", (unsigned long)pthread_self()); 
}

int main(int argc, char const *argv[]) {
    pthread_t tidA, tidB; 

    pthread_create(&tidA, NULL, getTID, NULL); 
    pthread_create(&tidB, NULL, getTID, NULL);

    pthread_join(tidA, NULL);
    pthread_join(tidB, NULL); 

    printf("Main thread done!\n");

    return 0;
}
