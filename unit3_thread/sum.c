#include <stdio.h>
#include <pthread.h>

int is_printf = 0;

void *get_usrer_input(void *arg)
{
    printf("Show result ? (1- yes/ 0 -no)\n");
    scanf("%d", &is_printf);
    return NULL;
}

int main()
{
    int sum = 0;
    int n = 10000;
    pthread_t thread_id;

    pthread_create(&thread_id, NULL, get_usrer_input, NULL);
    for(int i =0; i< n; i++) sum = sum + i;
    pthread_join(thread_id, NULL);
    if(is_printf){
        printf("sum: %d .\n", sum);
    }
}