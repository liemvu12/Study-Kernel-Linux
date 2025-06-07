#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FILE_PATH "output.txt"

pthread_mutex_t file_mutex;

void safe_write_to_file(const char *msg) {
    pthread_mutex_lock(&file_mutex);

    int fp = open(FILE_PATH, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fp < 0) {
        perror("open");
        pthread_mutex_unlock(&file_mutex);
        return;
    }

    ssize_t size = write(fp, msg, sizeof(msg));
    if (size != sizeof(msg)){
        perror ("write");
    }
    close(fp);

    pthread_mutex_unlock(&file_mutex);
}

struct thread_arg {
    const char *msg;
    int count;
};

void* thread_func(void *arg) {
    struct thread_arg *targ = (struct thread_arg*)arg;
    for (int i = 0; i < targ->count; i++) {
        safe_write_to_file(targ->msg);
        usleep(100000); 
    }
    return NULL;
}

int main() {
    pthread_t tid1, tid2;

    pthread_mutex_init(&file_mutex, NULL);

    struct thread_arg arg1 = { "Thread1\n", 5 };
    struct thread_arg arg2 = { "Thread2\n", 5 };

    pthread_create(&tid1, NULL, thread_func, &arg1);
    pthread_create(&tid2, NULL, thread_func, &arg2);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_mutex_destroy(&file_mutex);

    printf("Finished writing to file: %s\n", FILE_PATH);
    return 0;
}
