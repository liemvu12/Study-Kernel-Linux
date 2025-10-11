#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child: Hello!\n");
        _exit(42); 
    } else {
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Parent: child exited with code %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}
