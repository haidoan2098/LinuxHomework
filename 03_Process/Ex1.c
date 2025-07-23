#include <stdio.h>
#include <stdlib.h>     // For exit()
#include <unistd.h>     // For fork()
#include <sys/types.h>   // For pid_t

int main(int argc, char const *argv[]) {
    pid_t pid = fork();     // Tạo ra tiến trình con 

    if (pid < 0) {
        perror("fork failed");
    }  
    
    if (pid == 0) {     
        // Tiến trình con
        printf("Child process: PID = %d\n", getpid());
        exit(10);   // Kết thúc con, giải phóng tài nguyên, báo cho cha biết với mã là 10 
    } else {        
        // Tiến trình cha
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);

        int status;     // Mã thoát của Process con 
        wait(&status);  // Đợi con kết thúc và giải phóng tài nguyên 

        if (WIFEXITED(status)) {    // Kiểm tra cách con chết như nào 
            // Con đã kết thúc bình thường
            int exit_code = WEXITSTATUS(status);    // Lấy giá trị exit() mà con trả về 
            printf("Child exited with code %d\n", exit_code);
        } else {
            printf("Child did not exit normally\n");
        }
    } 


    return 0;
}
