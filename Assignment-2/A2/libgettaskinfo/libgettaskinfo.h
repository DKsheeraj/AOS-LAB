#ifndef LIBGETTASKINFO_H
#define LIBGETTASKINFO_H

#include <sys/types.h>

// Structure to hold the task information
struct task_info {
    long state;              // Process state
    unsigned long long start_time; // Process start time
    int normal_prio;        // Process normal priority
};

// Function prototype for the wrapper function
struct task_info* gettaskinfo(pid_t pid);

#endif // LIBGETTASKINFO_H
