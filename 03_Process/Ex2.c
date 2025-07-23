#include <stdio.h>
#include <unistd.h>     // For fork()
#include <stdlib.h>     // For exit()
#include <sys/types.h>   // For pid_t 


int main(int argc, char const *argv[]) {
    pid_t pid; 

    // Thiết lập biến môi trường 
    setenv("MY_COMMAND", "ls", 1);
    
    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    // Đây là tiến trình con
    if (pid == 0) {
        // Đọc biến môi trường 
        char *cmd = getenv("MY_COMMAND");
        if (cmd == NULL) {
            fprintf(stderr, "Variable not found MY_COMMAND\n");
            exit(EXIT_FAILURE);
        }

        execlp(cmd, cmd, NULL); // Tìm chương trình ls trong PATH, chạy ls với ko đối số 

        // Nếu exec thất bại
        perror("exec failed");
        exit(EXIT_FAILURE);

    } else {  // Đây là tiến trình cha
        wait(NULL);
        printf("child process terminated\n");
    }


    return 0;
}
