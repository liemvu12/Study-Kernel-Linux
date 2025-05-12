#include <stdio.h>
#include <stdlib.h>

// Hàm main chuẩn trong Linux.
int main(int argc, char *argv[], char *envp[]) {
    printf("Number of arguments (argc): %d\n", argc);

    printf("\nArguments (argv):\n");
    for (int i = 0; i < argc; i++) {
        printf("  argv[%d]: %s\n", i, argv[i]);
    }

    printf("\nEnvironment variables (envp):\n");
    for (int i = 0; envp[i] != NULL; i++) {
        printf("  envp[%d]: %s\n", i, envp[i]);
    }

    return 0;
}
