#include <stdio.h>
#include <unistd.h>

int main()
{
    execl("./child", "xin_chao", NULL);
    printf ("I am parent\n");
    return 0;
}