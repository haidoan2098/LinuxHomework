#include <stdio.h>
#include <unistd.h>     // For fork() 
#include <stdlib.h>     // exit(), EXIT_FAILURE
#include <sys/types.h>  // For pid_t 

int main(int argc, char const *argv[]) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE); 
    }

    if (pid == 0) {     // Đây là tiến trình con
        for (int i = 0; i < 10; i++) {
            printf("This is Child Process, Parent PID = %d\n", getppid());
            sleep(1);
        }
    } else {    // Đây là tiến trình cha 
        printf("This is Parent Process, Parent PID = %d\n", getpid());
        exit(EXIT_SUCCESS);
    }
    

    return 0;
}
