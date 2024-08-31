#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>

struct taskinfo {
    long state;
    unsigned long start_time;
    int normal_prio;
};

struct taskinfo *gettaskinfo(pid_t pid) {
    char buffer[256];
    struct taskinfo *info;
    long ret;

    ret = syscall(548, pid, buffer);

    if (ret < 0) {
        errno = -ret;
        return NULL;
    }

    info = malloc(sizeof(struct taskinfo));
    if (!info)
        return NULL;

    sscanf(buffer, "%ld %lu %d", &info->state, &info->start_time, &info->normal_prio);
    return info;
}
