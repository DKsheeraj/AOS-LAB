/*
 * CS60038: Advances in Operating Systems Design
 * Assignment 1, Part B: Loadable Kernel Module(LKM) for a Set
 * Members:
 * > 21CS30037 - Datta Ksheeraj
 * > 21CS100 - Bratin Mondal
*/

#include <linux/errno.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ksheeraj and Bratin");
MODULE_DESCRIPTION("LKM for a Set with Max Capacity");
MODULE_VERSION("1.0");

#define PROCFS_NAME "partb_21CS10016_21CS30037"
#define PROCFS_MAX_SIZE 1024

DEFINE_MUTEX(procfs_mutex);

enum process_state {
    PROC_FILE_OPEN,  // File is open but set is not initialized
    PROC_READ        // File is open and set is initialized, ready for reads and writes
};

struct set {
    int *elements;
    int capacity;
    int size;
};

struct process_node {
    pid_t pid;
    struct set *process_set;
    enum process_state state;
    struct process_node *next;
};

static struct proc_dir_entry *proc_file;
static char procfs_buffer[PROCFS_MAX_SIZE];
static size_t procfs_buffer_size = 0;
static struct process_node *process_list = NULL;

// Initialize a set
static struct set *set_init(int capacity) {
    struct set *s = kmalloc(sizeof(struct set), GFP_KERNEL);
    if (!s) {
        printk(KERN_ALERT "E: Memory allocation for set failed\n");
        return NULL;
    }

    s->elements = kmalloc(capacity * sizeof(int), GFP_KERNEL);
    if (!s->elements) {
        printk(KERN_ALERT "E: Memory allocation for set elements failed\n");
        kfree(s);
        return NULL;
    }

    s->capacity = capacity;
    s->size = 0;

    return s;
}

// Deallocate memory for a set
static void set_delete(struct set *s) {
    if (s) {
        kfree(s->elements);
        kfree(s);
    }
}

// Check if an element exists in the set
static int set_contains(struct set *s, int val) {
    for (int i = 0; i < s->size; i++) {
        if (s->elements[i] == val) {
            return 1;
        }
    }
    return 0;
}

// Insert an element into the set
static int set_insert(struct set *s, int val) {
    if (s->size >= s->capacity) {
        printk(KERN_ALERT "E: Set is full\n");
        return -EACCES;
    }
    if (set_contains(s, val)) {
        printk(KERN_ALERT "E: Element already exists in the set\n");
        return -EEXIST;
    }

    s->elements[s->size++] = val;
    return 0;
}

// Read elements from the set
static ssize_t set_read(struct set *s, char __user *buffer, size_t length) {
    size_t bytes_to_copy = min(length, (size_t)(s->size * sizeof(int)));
    if (copy_to_user(buffer, s->elements, bytes_to_copy)) {
        return -EACCES;
    }
    return bytes_to_copy;
}

// Find a process node by PID
static struct process_node *process_find(pid_t pid) {
    struct process_node *curr = process_list;
    while (curr) {
        if (curr->pid == pid) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

// Insert a process node
static struct process_node *process_insert(pid_t pid) {
    struct process_node *node = kmalloc(sizeof(struct process_node), GFP_KERNEL);
    if (!node) {
        return NULL;
    }

    node->pid = pid;
    node->process_set = NULL;
    node->state = PROC_FILE_OPEN;
    node->next = process_list;
    process_list = node;

    return node;
}

// Delete a process node
static int process_delete(pid_t pid) {
    struct process_node *curr = process_list;
    struct process_node *previous = NULL;

    while (curr) {
        if (curr->pid == pid) {
            if (previous) {
                previous->next = curr->next;
            } else {
                process_list = curr->next;
            }

            if (curr->process_set) {
                set_delete(curr->process_set);
            }

            kfree(curr);
            return 0;
        }

        previous = curr;
        curr = curr->next;
    }
    return -EACCES;
}

// Handle write operations
static ssize_t handle_write(struct process_node *node) {
    size_t capacity;
    int value, ret_val;

    if (node->state == PROC_FILE_OPEN) {
        if (procfs_buffer_size != 1) {
            printk(KERN_ALERT "E: Capacity buffer size must be 1 byte\n");
            return -EINVAL;
        }

        capacity = (size_t)procfs_buffer[0];
        if (capacity < 1 || capacity > 100) {
            printk(KERN_ALERT "E: Capacity must be between 1 and 100\n");
            return -EINVAL;
        }

        node->process_set = set_init(capacity);
        if (!node->process_set) {
            printk(KERN_ALERT "E: Could not initialize set for process %d\n", node->pid);
            return -ENOMEM;
        }

        node->state = PROC_READ;
        printk(KERN_INFO "I: Set initialized for process %d\n", node->pid);
    } else if (node->state == PROC_READ) {
        if (procfs_buffer_size != sizeof(int)) {
            printk(KERN_ALERT "E: Value buffer size must be 4 bytes\n");
            return -EINVAL;
        }

        value = *((int *)procfs_buffer);

        ret_val = set_insert(node->process_set, value);
        if (ret_val < 0) {
            printk(KERN_ALERT "E: Could not insert value %d in set for process %d\n", value, node->pid);
            return -EACCES;
        }

        printk(KERN_INFO "I: Value %d inserted in set for process %d\n", value, node->pid);
    }

    return procfs_buffer_size;
}

static void process_list_delete(void)
{
    struct process_node *node = process_list;
    struct process_node *next = NULL;
    while(curr){
        next = curr->next;
        if (curr->process_set) {
            set_delete(curr->process_set);
        }
        kfree(curr);
        curr = next;
    }
    process_list = NULL;
}

static ssize_t procfile_write(struct file *filep, const char __user *buffer, size_t length, loff_t *offset) {
    pid_t pid;
    int ret_val;
    struct process_node *node;

    mutex_lock(&procfs_mutex);

    pid = current->pid;
    printk(KERN_INFO "I: Process %d writing to the file\n", pid);
    ret_val = 0;

    node = process_find(pid);
    if (!node) {
        printk(KERN_ALERT "E: Process %d does not have the process file open\n", pid);
        ret_val = -EACCES;
    } else {
        if (buffer == NULL || length == 0) {
            printk(KERN_ALERT "E: No data to write\n");
            ret_val = -EINVAL;
        } else {
            procfs_buffer_size = min(length, (size_t)PROCFS_MAX_SIZE);

            if (copy_from_user(procfs_buffer, buffer, procfs_buffer_size)) {
                printk(KERN_ALERT "E: Could not copy data from user\n");
                ret_val = -EFAULT;
            } else {
                ret_val = handle_write(node);
            }
        }
    }

    mutex_unlock(&procfs_mutex);

    return ret_val;
}

static ssize_t procfile_read(struct file *filep, char __user *buffer, size_t length, loff_t *offset) {
    pid_t pid;
    ssize_t ret_val;

    mutex_lock(&procfs_mutex);

    pid = current->pid;
    printk(KERN_INFO "I: Process %d reading from the file\n", pid);
    ret_val = 0;

    struct process_node *node = process_find(pid);
    if (!node) {
        printk(KERN_ALERT "E: Process %d does not have the process file open\n", pid);
        ret_val = -EACCES;
    } else {
        if (node->state == PROC_FILE_OPEN) {
            printk(KERN_ALERT "E: Set not initialized yet\n");
            ret_val = -EACCES;
        } else if (!node->process_set) {
            printk(KERN_ALERT "E: Set not initialized\n");
            ret_val = -EACCES;
        } else {
            ret_val = set_read(node->process_set, buffer, length);
            if (ret_val < 0) {
                printk(KERN_ALERT "E: Could not read data from set\n");
            }
        }
    }

    mutex_unlock(&procfs_mutex);

    return ret_val;
}

static int procfile_open(struct inode *inode, struct file *file) {
    pid_t pid;
    int ret_val;
    struct process_node *node;

    mutex_lock(&procfs_mutex);

    pid = current->pid;
    printk(KERN_INFO "I: Process %d opening the file\n", pid);
    ret_val = 0;

    node = process_find(pid);
    if (node) {
        printk(KERN_ALERT "E: Process %d already has the process file open\n", pid);
        ret_val = -EACCES;
    } else {
        node = process_insert(pid);
        if (!node) {
            printk(KERN_ALERT "E: Could not allocate memory for process %d\n", pid);
            ret_val = -ENOMEM;
        }else{
            printk(KERN_INFO "I: Process %d has the process file open\n", pid);
        }
    }

    mutex_unlock(&procfs_mutex);

    return ret_val;
}

static int procfile_release(struct inode *inode, struct file *file) {
    pid_t pid;
    int ret_val;

    mutex_lock(&procfs_mutex);

    pid = current->pid;
    printk(KERN_INFO "I: Process %d closing the file\n", pid);
    ret_val = 0;

    struct process_node *node = process_find(pid);
    if (!node) {
        printk(KERN_ALERT "E: Process %d does not have the process file open\n", pid);
        ret_val = -EACCES;
    } else {
        ret_val = process_delete(pid);
        printk(KERN_INFO "I: Process %d has the process file closed\n", pid);
    }

    

    mutex_unlock(&procfs_mutex);

    return ret_val;
}

static const struct proc_ops proc_fops = {
    .proc_open = procfile_open,
    .proc_read = procfile_read,
    .proc_write = procfile_write,
    .proc_release = procfile_release,
};

static int __init lkm_init(void) {
    printk(KERN_INFO "I: LKM for partb_21CS10016_21CS30037 loaded\n");

    proc_file = proc_create(PROCFS_NAME, 0666, NULL, &proc_fops);
    if (!proc_file) {
        printk(KERN_ALERT "E: Could not create process file\n");
        return -ENOENT;
    }

    printk(KERN_INFO "I: /proc/%s created\n", PROCFS_NAME);
    return 0;
}

static void __exit lkm_exit(void) {
    struct process_node *node = process_list;
    while (node) {
        struct process_node *temp = node;
        node = node->next;

        if (temp->process_set) {
            set_delete(temp->process_set);
        }
        kfree(temp);
    }

    remove_proc_entry(PROCFS_NAME, NULL);
    printk(KERN_INFO "I: LKM for partb_set unloaded\n");
}

module_init(lkm_init);
module_exit(lkm_exit);
