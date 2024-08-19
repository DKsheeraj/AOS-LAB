/*
Testcase - 7: Try to write in uninitialized memory

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
using namespace std;

#define PROC_FILE "/proc/partb_21CS10016_21CS30037"

int main()
{
    int fd = open(PROC_FILE, O_RDWR, 0666);

    int x=16;
    int ret=write(fd,&x,sizeof(int));
    if(ret<0)
    {
        perror("write");
        printf("TEST CASE 1 PASSED\n");
    }
    else
    {
        printf("TEST CASE 1 FAILED\n");
    }
}