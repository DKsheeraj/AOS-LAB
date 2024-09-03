#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define SYS_gettaskinfo 441  // Use the syscall number assigned

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid_t pid = atoi(argv[1]);
    char buffer[256];
    long ret;

    ret = syscall(SYS_gettaskinfo, pid, buffer);

    if (ret < 0) {
        fprintf(stderr, "syscall failed with error number %d: %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    // Print the contents of the buffer
    long state;
    unsigned long long start_time;
    int normal_prio;
    sscanf(buffer, "%ld %llu %d", &state, &start_time, &normal_prio);

    printf("Process state: %ld\n", state);
    printf("Process start time: %llu\n", start_time);
    printf("Process normal priority: %d\n", normal_prio);

    return EXIT_SUCCESS;
}
