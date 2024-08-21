/*
Testcase - 10: Threads try to write to parent file descriptor
    - The threads should be able to write to the parent file descriptor

 * > 21CS30037 - Datta Ksheeraj
 * > 21CS10016 - Bratin Mondal
 *
 * Department of Computer Science and Engineering,
 * Indian Institute of Technology Kharagpur
 */

#include <set>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <sys/wait.h>
#include <thread>
using namespace std;

#define PROC_FILE "/proc/partb_21CS10016_21CS30037"

int main()
{
    srand(time(NULL));
    int sz = rand() % 100 + 1;
    int fd = open(PROC_FILE, O_RDWR, 0666);
    if(fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    pid_t pid = gettid();
    printf("Parent PID: %d\n", pid);

    char size=(char)sz;
    int ret=write(fd,&size,sizeof(char));
    if(ret<0)
    {
        perror("write");
        exit(EXIT_FAILURE);
    }

    thread t1([&](){
        pid_t pid = gettid();
        printf("Thread 1 PID: %d\n", pid);
        int x = rand();
        int ret = write(fd, &x, sizeof(int));
        if(ret<0)
        {
            perror("write");
            printf("Thread 1 was not able to write to parent file descriptor\n");
            printf("TEST FAILED\n");
        }
        else if(ret==sizeof(int))
        {
            printf("Thread 1 was able to write to parent file descriptor\n");
            printf("TEST PASSED\n");
        }
        else
        {
            printf("Something went wrong\n");
            printf("TEST FAILED\n");
        }
    });

    thread t2([&](){
        pid_t pid = gettid();
        printf("Thread 2 PID: %d\n", pid);
        int x = rand();
        int ret = write(fd, &x, sizeof(int));
        if(ret<0)
        {
            perror("write");
            printf("Thread 2 was not able to write to parent file descriptor\n");
            printf("TEST FAILED\n");
        }
        else if(ret==sizeof(int))
        {
            printf("Thread 2 was able to write to parent file descriptor\n");
            printf("TEST PASSED\n");
        }
        else
        {
            printf("Something went wrong\n");
            printf("TEST FAILED\n");
        }
    });

    t1.join();
    t2.join();

    close(fd);
    return 0;
}