#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/uaccess.h>

SYSCALL_DEFINE2(gettaskinfo, pid_t, pid, char __user *, buffer) {
    struct task_struct *task;
    char info[256];
    int len;

    printk(KERN_INFO "gettaskinfo: Called with PID = %d\n", pid);

    // Find the task by PID
    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (!task) {
        printk(KERN_ERR "gettaskinfo: No task found with PID = %d\n", pid);
        return -ESRCH;
    }

    printk(KERN_INFO "gettaskinfo: Task found. State = %ld, Start time = %llu, Priority = %d\n",
           task->state, task->start_time, task->normal_prio);

    // Extract the required information in space-separated format
    len = snprintf(info, sizeof(info), "%ld %llu %d\n",
                   task->state, task->start_time, task->normal_prio);

    printk(KERN_INFO "gettaskinfo: Info formatted: %s\n", info);

    // Copy the information to the user buffer
    if (copy_to_user(buffer, info, len)) {
        printk(KERN_ERR "gettaskinfo: Failed to copy info to user buffer\n");
        return -EFAULT;
    }

    printk(KERN_INFO "gettaskinfo: Successfully copied info to user buffer\n");

    return 0;
}
