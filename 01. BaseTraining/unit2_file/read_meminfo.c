#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void main()
{
    int fd = open("/proc/meminfo", O_RDONLY);
    if(fd == -1)
    {
        perror ("Khong the mo file");
        return ;
    }else
    {
        char Buff[100];
        read(fd, Buff, sizeof(Buff) - 1);
        int i =0;
        while(Buff[i] != '\n')
        {
            printf("%c",Buff[i]);
            i++;
        }
        printf("\n");
        close (fd); 
    }

}