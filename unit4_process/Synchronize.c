#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();
    if (pid == 0) {
        // Child: chuẩn bị dữ liệu.
        printf("Child: Preparing data...\n");
        sleep(2); // giả lập xử lý.
        _exit(0);
    } else {
        printf("Parent: Waiting for child to finish preparing...\n");
        wait(NULL);
        printf("Parent: Child done. Now sending data!\n");
}

}