#include <stdio.h>
#include <unistd.h>

int main() {
    int pid = fork();  

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        printf("I am the child process. My PID is %d\n", getpid());
    } else {
        // Đây 
        printf("I am the parent process. My PID is %d and my child's PID is %d\n", getpid(), pid);
    }

    return 0;
}
