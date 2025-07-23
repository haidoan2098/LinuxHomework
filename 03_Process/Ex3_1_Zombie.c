#include <stdio.h>
#include <stdlib.h>      // For exit(), EXIT_FAILURE
#include <unistd.h>      // For fork(), sleep()
#include <sys/types.h>   // For pid_t


int main(int argc, char const *argv[]) {
    pid_t pid = fork();     // Tạo tiến trình con

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE); 
    }

    // Đây là tiến trình con
    if (pid == 0) { 
        exit(EXIT_SUCCESS); 
    } else {    // Đây là tiến trình cha
        sleep(100);
    }

    return 0;
}
