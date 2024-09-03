#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include "libgettaskinfo.h"

// Define the system call number for `gettaskinfo`
#define __NR_gettaskinfo 441

// #define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...) // No-op
#endif

struct task_info* gettaskinfo(pid_t pid) {
    char buffer[256];
    struct task_info *info;
    long ret;

    DEBUG_PRINT("Making syscall gettaskinfo with PID: %d\n", pid);

    // Make the system call
    ret = syscall(__NR_gettaskinfo, pid, buffer);

    // Check for system call errors
    if (ret < 0) {
        DEBUG_PRINT("System call failed with error number %d: %s\n", errno, strerror(errno));
        return NULL;
    }

    DEBUG_PRINT("System call succeeded. Buffer received: %s\n", buffer);

    // Allocate memory for the task_info structure
    info = malloc(sizeof(struct task_info));
    if (!info) {
        DEBUG_PRINT("Memory allocation failed\n");
        errno = ENOMEM;  // Memory allocation failure
        return NULL;
    }

    // Parse the buffer to populate the task_info structure
    char *state_str, *start_time_str, *normal_prio_str;

    // Tokenize the buffer based on spaces
    state_str = strtok(buffer, " ");
    start_time_str = strtok(NULL, " ");
    normal_prio_str = strtok(NULL, " ");

    if (state_str && start_time_str && normal_prio_str) {
        info->state = strtol(state_str, NULL, 10);
        info->start_time = strtoull(start_time_str, NULL, 10);
        info->normal_prio = strtol(normal_prio_str, NULL, 10);

        DEBUG_PRINT("Parsed info: state=%ld, start_time=%llu, normal_prio=%d\n",
                    info->state, info->start_time, info->normal_prio);
    } else {
        DEBUG_PRINT("Failed to parse buffer. Tokenized items: state_str=%s, start_time_str=%s, normal_prio_str=%s\n",
                    state_str, start_time_str, normal_prio_str);
        free(info);
        return NULL;
    }

    return info;
}
