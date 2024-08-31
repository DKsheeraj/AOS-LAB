#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "libgettaskinfo.h"

int main(int argc, char *argv[]) {
    pid_t pid;
    struct taskinfo *info;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PID>\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid = atoi(argv[1]);
    info = gettaskinfo(pid);

    if (!info) {
        perror("gettaskinfo");
        return EXIT_FAILURE;
    }

    printf("State: %ld\nStart time: %lu\nNormal priority: %d\n",
           info->state, info->start_time, info->normal_prio);

    free(info);
    return EXIT_SUCCESS;
}
