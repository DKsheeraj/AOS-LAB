#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/uaccess.h>

asmlinkage long sys_gettaskinfo(pid_t pid, char __user *buffer) {
    struct task_struct *task;
    char info[256];
    long state;
    unsigned long start_time;
    int normal_prio;

    task = find_task_by_vpid(pid);
    if (!task)
        return -ESRCH;

    state = task->state;
    start_time = task->start_time;
    normal_prio = task->normal_prio;

    snprintf(info, sizeof(info), "%ld %lu %d", state, start_time, normal_prio);

    if (copy_to_user(buffer, info, strlen(info) + 1))
        return -EFAULT;

    return 0;
}
