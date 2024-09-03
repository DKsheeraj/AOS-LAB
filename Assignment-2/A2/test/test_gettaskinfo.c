#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "libgettaskinfo.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid_t pid = atoi(argv[1]);
    struct task_info *info = gettaskinfo(pid);

    if (info == NULL) {
        // Print specific error information if gettaskinfo uses errno
        fprintf(stderr, "gettaskinfo failed with error code %d: %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    printf("Process state: %ld\n", info->state);
    printf("Process start time: %llu\n", info->start_time);
    printf("Process normal priority: %d\n", info->normal_prio);

    free(info);
    return EXIT_SUCCESS;
}
