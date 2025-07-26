#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> 
#include <time.h>
#include <unistd.h>


int data[10];                
int data_ready = 0;     // chưa có data 

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; 

void *Producer(void *arg) {
    pthread_mutex_lock(&lock); 

    for (int i = 0; i < 10; i++) {
        data[i] = rand() % 100;
    }
    sleep(2); // Giả lập đang tạo data 

    data_ready = 1;     // Báo có data rồi 

    pthread_cond_signal(&cond);     // Đánh thức thằng kia dậy nhận
    pthread_mutex_unlock(&lock);

    return NULL;
}

void *Consummer(void *arg) {
    pthread_mutex_lock(&lock); 
    while (data_ready == 0) {
        pthread_cond_wait(&cond, &lock);  // Ngủ và nhả lock
    }

    printf("Have data\n");
    // Có data rồi 
    for (int i = 0; i < 10; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    data_ready = 0;

    pthread_mutex_unlock(&lock);
    return NULL; 
}

int main(int argc, char const *argv[]) {
    srand(time(NULL));  // Thiết lập seed

    pthread_t tidCon, tidPro; 

    pthread_create(&tidCon, NULL, Consummer, NULL); 
    pthread_create(&tidPro, NULL, Producer, NULL); 

    pthread_join(tidCon, NULL); 
    pthread_join(tidPro, NULL); 

    return 0;
}
