#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PROC_FILE "/proc/partb_21CS10016_21CS30037"

int main()
{
    // try to write to the proc file without opening it
    int fd = open(PROC_FILE, O_RDWR);
    // if (fd == -1)
    // {
    //     perror("Error opening proc file");
    //     exit(EXIT_FAILURE);
    // }

    close(fd);

    // Initialize the set with its capacity
    char capacity = 5;
    if (write(fd, &capacity, 1) != 1)
    {
        perror("Error writing capacity");
        close(fd);
        exit(EXIT_FAILURE);
    }

    //close the file descriptor
    close(fd);
}