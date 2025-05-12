#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fp;
    char buffer[128];
    while (1)
    {
        fp = open("/tmp/daemon_log.txt", O_CREAT | O_WRONLY, 0644);
        if (fp < 0)
        {
            perror("open");
            return 1;
        }
        time_t now = time(NULL);
        snprintf(buffer, sizeof(buffer), "%s", ctime(&now));
        write(fp, buffer, strlen(buffer));
        close(fp);
        sleep(5);
    }
    return 0;
}
