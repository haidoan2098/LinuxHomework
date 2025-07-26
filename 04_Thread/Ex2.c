#include <stdio.h>
#include <pthread.h>

long long counter; 

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


void *increaseValue(void *arg) {
    pthread_mutex_lock(&lock); 
    for (int i = 0; i < 1000000; i++) {
        counter++;
    }
    pthread_mutex_unlock(&lock); 
}


int main(int argc, char const *argv[]) {

    pthread_t tidA, tidB, tidC; 

    pthread_create(&tidA, NULL, increaseValue, &counter); 
    pthread_create(&tidB, NULL, increaseValue, &counter); 
    pthread_create(&tidC, NULL, increaseValue, &counter); 

    pthread_join(tidA, NULL); 
    pthread_join(tidB, NULL); 
    pthread_join(tidC, NULL);

    pthread_mutex_destroy(&lock); 
    
    printf("Final counter = %lld\n", counter);

    return 0;
}
