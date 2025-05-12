#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 4

void *count_odd_numbers(void *arg)
{
    int thread_range = *(int *) arg;

    // sử dụng cấp phát động ở đây do nếu sử dụng biến local thì sau khi hàm kết thúc biến sẽ bị giải phóng hoàn toàn nên không thể trả về -> undefined behavior.
    int *count = malloc(sizeof(int));  
    if (!count) {
        perror("malloc failed");
        pthread_exit(NULL);
    }

    *count = 0;

    for (int i = (thread_range ) * 500000000; i < (thread_range +1 ) * 500000000; i++){
        if (i %2 == 1) (*count) += 1 ;
    }
    return (void *)count;
}

int main()
{
    int sum = 0;
    int *thread_result;
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    for(int i = 0; i < 4; i++){
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, count_odd_numbers, &thread_args[i]);
    }

    for(int i = 0; i < 4; i++){
        pthread_join(threads[i], (void **)&thread_result); 
        sum += *(int *)thread_result;
    }

    printf ("odd number from 0 to 2000000000 is: %d\n", sum);
}