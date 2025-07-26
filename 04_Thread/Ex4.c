#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int globalValue; 

pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

void *reader(void *arg) {
    while (1) {
        pthread_rwlock_rdlock(&rwlock);     // Khóa đọc 

        printf("Reader %d read data = %d\n", *(int *)arg, globalValue);

        pthread_rwlock_unlock(&rwlock);
        sleep(5);                  // Đọc xong thì ngủ 1s để thread khác đọc
    }

    return NULL;
}

void *writer(void *arg) {   
    while (1) {
        pthread_rwlock_wrlock(&rwlock);     // Khóa ghi 

        globalValue++;
        printf("Writer %d write data = %d\n", *(int *)arg, globalValue);

        pthread_rwlock_unlock(&rwlock);
        sleep(6);                  // Viết xong thì ngủ 5s để thread khác viết 
    }

    return NULL; 
}

int main(int argc, char const *argv[]) {
    pthread_t r[5], w[2]; 
    int r_ids[5] = {0, 1, 2, 3, 4}; 
    int w_ids[2] = {0, 1}; 

    for (int i = 0; i < 5; i++) {
        pthread_create(&r[i], NULL, reader, &r_ids[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_create(&w[i], NULL, writer, &w_ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(r[i], NULL);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(w[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);        // Huy RWLock

    return 0;
}
