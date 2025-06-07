#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#define KEY_P 25
#define ESC 1

int main()
{
    struct input_event ev;
    int fd = open("/dev/input/event2", O_RDONLY);
    if( fd < 0){
        perror ("Khong the mo file");
        return 0;
    } 

    while (1){
        ssize_t bytes = read(fd, &ev, sizeof(ev));
        if(bytes == sizeof(ev)){
            if(ev.code == KEY_P && ev.value == 0) { printf("Da click nut P.\n");}
            if(ev.code == ESC) { 
                printf("Da Out.\n");
                break;
                }
        }
    }
    close(fd);
}
