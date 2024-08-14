/*
 * CS60038: Advances in Operating Systems Design
 * Assignment 1, Part B: Loadable Kernel Module(LKM) for a Set
 * Members:
 * > 21CS30037 - Datta Ksheeraj
 * > 21CS10016 - Bratin Mondal
 */

// Header files
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

#define PROCFS_NAME "partb_21CS10016_21CS30037" // Name of the proc file
#define PROCFS_MAX_SIZE 1024                    // Max size of the proc file

DEFINE_MUTEX(procfs_mutex); // Mutex for synchronization

/**
 * Enum to represent the state of a process
 *
 * PROC_FILE_OPEN: File is open but set is not initialized
 * PROC_READ: File is open and set is initialized, ready for reads and writes
 */
enum process_state
{
    PROC_FILE_OPEN,
    PROC_READ
};

/**
 * Struct to represent a set
 *
 * elements: Array of elements in the set
 * capacity: Maximum capacity of the set
 * size: Number of elements in the set
 */
struct set
{
    int *elements;
    int capacity;
    int size;
};

/**
 * Struct to represent a process node
 *
 * pid: Process ID
 * process_set: Set associated with the process
 * process_state: State of the process
 * next: Pointer to the next process node (Linked list)
 */
struct process_node
{
    pid_t pid;
    struct set *process_set;
    enum process_state state;
    struct process_node *next;
};

static struct proc_dir_entry *proc_file;         // Pointer to the proc file
static char procfs_buffer[PROCFS_MAX_SIZE];      // Buffer to store data read from the proc file
static size_t procfs_buffer_size = 0;            // Size of the data read from the proc file
static struct process_node *process_list = NULL; // Pointer to the head of the process list

/**
 * set_init: Initialize a set
 *
 * @param capacity: Maximum capacity of the set
 * @return Pointer to the set
 */
static struct set *set_init(int capacity)
{
    struct set *s = kmalloc(sizeof(struct set), GFP_KERNEL); // Allocate memory for the set
    if (!s)
    {
        printk(KERN_ALERT "E: Memory allocation for set failed\n");
        return NULL;
    }

    s->elements = kmalloc(capacity * sizeof(int), GFP_KERNEL); // Allocate memory for the elements
    if (!s->elements)
    {
        printk(KERN_ALERT "E: Memory allocation for set elements failed\n");
        kfree(s);
        return NULL;
    }

    s->capacity = capacity; // Set the capacity
    s->size = 0;            // Initialize the size to 0

    return s; // Return the set
}

/**
 * set_delete: Delete a set
 *
 * @param s: Pointer to the set
 * @return void
 */
static void set_delete(struct set *s)
{
    if (s)
    {
        if (s->elements)
        {
            kfree(s->elements); // Free the memory allocated for the elements
        }
        kfree(s); // Free the memory allocated for the set
    }
}

/**
 * set_contains: Check if an element is present in the set
 *
 * @param s: Pointer to the set
 * @param val: Value to check
 * @return 1 if the element is present, 0 otherwise
 */
static int set_contains(struct set *s, int val)
{
    int i;
    for (i = 0; i < s->size; i++)
    {
        if (s->elements[i] == val)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * set_insert: Insert an element into the set
 *
 * @param s: Pointer to the set
 * @param val: Value to insert
 * @return 0 on success, -EACCES if the set is full, -EEXIST if the element already exists
 */
static int set_insert(struct set *s, int val)
{
    int i;
    if (s->size >= s->capacity) // Check if the set is full
    {
        printk(KERN_ALERT "E: Set is full\n");
        return -EACCES;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (set_contains(s, val)) // Check if the element already exists in the set
    {
        printk(KERN_ALERT "E: Element already exists in the set\n"); // Element already exists ( Is it a error? )
        return -EEXIST;                                              // ( Should we return an error? )
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Insert the element in sorted order
    i = s->size - 1;
    while (i >= 0 && s->elements[i] > val)
    {
        s->elements[i + 1] = s->elements[i];
        i--;
    }
    s->elements[i + 1] = val;
    s->size++; // Increment the size of the set
    return 0;
}

/**
 * set_read: Read the elements of the set
 *
 * @param s: Pointer to the set
 * @param buffer: Buffer to store the elements
 * @param length: Length of the buffer
 * @return Number of bytes copied
 */
static ssize_t set_read(struct set *s, char __user *buffer, size_t length)
{
    size_t bytes_to_copy = min(length, (size_t)(s->size * sizeof(int)));
    if (copy_to_user(buffer, s->elements, bytes_to_copy))
    {
        return -EACCES;
    }
    return bytes_to_copy;
}

/**
 * process_find: Find a process node
 *
 * @param pid: Process ID
 * @return Pointer to the process node if found, NULL otherwise
 */

static struct process_node *process_find(pid_t pid)
{
    struct process_node *curr = process_list;
    while (curr)
    {
        if (curr->pid == pid)
        {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

/**
 * process_insert: Insert a process node
 *
 * @param pid: Process ID
 * @return Pointer to the process node
 */
static struct process_node *process_insert(pid_t pid)
{
    struct process_node *node = kmalloc(sizeof(struct process_node), GFP_KERNEL);
    if (!node)
    {
        return NULL;
    }

    node->pid = pid;
    node->process_set = NULL;
    node->state = PROC_FILE_OPEN;
    node->next = process_list;
    process_list = node;

    return node;
}

/**
 * process_delete: Delete a process node
 *
 * @param pid: Process ID
 * @return 0 on success, -EACCES if the process node is not found
 */
static int process_delete(pid_t pid)
{
    struct process_node *curr = process_list;
    struct process_node *previous = NULL;

    while (curr)
    {
        if (curr->pid == pid)
        {
            if (previous)
            {
                previous->next = curr->next;
            }
            else
            {
                process_list = curr->next;
            }

            if (curr->process_set)
            {
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

/**
 * handle_write: Handle write operations on the proc file
 *
 * @param node: Pointer to the process node
 * @return Number of bytes written
 */
static ssize_t handle_write(struct process_node *node)
{
    size_t capacity;
    int value, ret_val;

    if (node->state == PROC_FILE_OPEN) // If the set is not initialized yet
    {
        if (procfs_buffer_size != 1) // Check if the capacity buffer size is 1 byte
        {
            printk(KERN_ALERT "E: Capacity buffer size must be 1 byte\n");
            return -EINVAL;
        }

        capacity = (size_t)procfs_buffer[0];
        if (capacity < 1 || capacity > 100) // Check if the capacity is between 1 and 100
        {
            printk(KERN_ALERT "E: Capacity must be between 1 and 100\n");
            return -EINVAL;
        }

        node->process_set = set_init(capacity); // Initialize the set
        if (!node->process_set)
        {
            printk(KERN_ALERT "E: Could not initialize set for process %d\n", node->pid);
            return -ENOMEM;
        }

        node->state = PROC_READ; // Set the state to PROC_READ
        printk(KERN_INFO "I: Set initialized for process %d with capacity %lu\n", node->pid, capacity);
    }
    else if (node->state == PROC_READ) // If the set is initialized
    {
        if (procfs_buffer_size != sizeof(int)) // Check if the value buffer size is 4 bytes
        {
            printk(KERN_ALERT "E: Value buffer size must be 4 bytes\n");
            return -EINVAL;
        }

        value = *((int *)procfs_buffer);

        ret_val = set_insert(node->process_set, value); // Insert the value into the set
        if (ret_val < 0)
        {
            printk(KERN_ALERT "E: Could not insert value %d in set for process %d\n", value, node->pid);
            return -EACCES;
        }

        printk(KERN_INFO "I: Value %d inserted in set for process %d\n", value, node->pid);
    }

    return procfs_buffer_size; // Return the number of bytes written
}

/**
 * procfile_write: Write operation on the proc file
 *
 * @param filep: Pointer to the file
 * @param buffer: Buffer to write
 * @param length: Length of the buffer
 * @param offset: Offset
 * @return Number of bytes written
 */
static ssize_t procfile_write(struct file *filep, const char __user *buffer, size_t length, loff_t *offset)
{
    pid_t pid;
    int ret_val;
    struct process_node *node;

    mutex_lock(&procfs_mutex); // Lock the mutex

    pid = current->pid;
    printk(KERN_INFO "I: Process %d writing to the file\n", pid);
    ret_val = 0;

    node = process_find(pid); // Find the process node
    if (!node)
    {
        printk(KERN_ALERT "E: Process %d does not have the process file open\n", pid);
        ret_val = -EACCES;
    }
    else
    {
        if (buffer == NULL || length == 0) // Check if the buffer is empty
        {
            printk(KERN_ALERT "E: No data to write\n");
            ret_val = -EINVAL;
        }
        else
        {
            procfs_buffer_size = min(length, (size_t)PROCFS_MAX_SIZE); // Set the buffer size

            if (copy_from_user(procfs_buffer, buffer, procfs_buffer_size)) // Copy data from user space
            {
                printk(KERN_ALERT "E: Could not copy data from user\n");
                ret_val = -EFAULT;
            }
            else
            {
                ret_val = handle_write(node); // Handle the write operation
            }
        }
    }

    mutex_unlock(&procfs_mutex); // Unlock the mutex

    return ret_val; // Return the number of bytes written
}

/**
 * procfile_read: Read operation on the proc file
 *
 * @param filep: Pointer to the file
 * @param buffer: Buffer to read
 * @param length: Length of the buffer
 * @param offset: Offset
 * @return Number of bytes read
 */
static ssize_t procfile_read(struct file *filep, char __user *buffer, size_t length, loff_t *offset)
{
    pid_t pid;
    ssize_t ret_val;
    struct process_node *node;

    mutex_lock(&procfs_mutex); // Lock the mutex

    pid = current->pid;
    printk(KERN_INFO "I: Process %d reading from the file\n", pid);
    ret_val = 0;

    node = process_find(pid); // Find the process node
    if (!node)
    {
        printk(KERN_ALERT "E: Process %d does not have the process file open\n", pid);
        ret_val = -EACCES;
    }
    else
    {
        if (node->state == PROC_FILE_OPEN) // Check if the set is not initialized yet
        {
            printk(KERN_ALERT "E: Set not initialized yet\n");
            ret_val = -EACCES;
        }
        else if (!node->process_set) // Check if the set is NULL
        {
            printk(KERN_ALERT "E: Set not initialized\n");
            ret_val = -EACCES;
        }
        else
        {
            ret_val = set_read(node->process_set, buffer, length); // Read the elements of the set
            if (ret_val < 0)
            {
                printk(KERN_ALERT "E: Could not read data from set\n");
            }
        }
    }

    mutex_unlock(&procfs_mutex); // Unlock the mutex

    return ret_val; // Return the number of bytes read
}

/**
 * procfile_open: Open operation on the proc file
 *
 * @param inode: Pointer to the inode
 * @param file: Pointer to the file
 * @return 0 on success, -EACCES if the process already has the file open, -ENOMEM if memory allocation fails
 */
static int procfile_open(struct inode *inode, struct file *file)
{
    pid_t pid;
    int ret_val;
    struct process_node *node;

    mutex_lock(&procfs_mutex); // Lock the mutex

    pid = current->pid;
    printk(KERN_INFO "I: Process %d opening the file\n", pid);
    ret_val = 0;

    node = process_find(pid); // Find the process node
    if (node)                 // Check if the process already has the file open
    {
        printk(KERN_ALERT "E: Process %d already has the process file open\n", pid);
        ret_val = -EACCES;
    }
    else
    {
        node = process_insert(pid); // Insert the process node
        if (!node)
        {
            printk(KERN_ALERT "E: Could not allocate memory for process %d\n", pid);
            ret_val = -ENOMEM;
        }
        else
        {
            printk(KERN_INFO "I: Process %d has the process file open\n", pid);
        }
    }

    mutex_unlock(&procfs_mutex); // Unlock the mutex

    return ret_val; // Return the status
}

/**
 * procfile_release: Release operation on the proc file
 *
 * @param inode: Pointer to the inode
 * @param file: Pointer to the file
 * @return 0 on success, -EACCES if the process does not have the file open
 */
static int procfile_release(struct inode *inode, struct file *file)
{
    pid_t pid;
    int ret_val;
    struct process_node *node;

    mutex_lock(&procfs_mutex); // Lock the mutex

    pid = current->pid;
    printk(KERN_INFO "I: Process %d closing the file\n", pid);
    ret_val = 0;

    node = process_find(pid); // Find the process node
    if (!node)
    {
        printk(KERN_ALERT "E: Process %d does not have the process file open\n", pid);
        ret_val = -EACCES;
    }
    else
    {
        ret_val = process_delete(pid); // Delete the process node
        printk(KERN_INFO "I: Process %d has the process file closed\n", pid);
    }

    mutex_unlock(&procfs_mutex); // Unlock the mutex

    return ret_val; // Return the status
}

/**
 * proc_fops: File operations for the proc file
 * 
 * proc_open: Open operation on the proc file
 * proc_read: Read operation on the proc file
 * proc_write: Write operation on the proc file
 * proc_release: Release operation on the proc file
 */
static const struct proc_ops proc_fops = {
    .proc_open = procfile_open,
    .proc_read = procfile_read,
    .proc_write = procfile_write,
    .proc_release = procfile_release,
};

/**
 * lkm_init: Module initialization function
 *
 * @return 0 on success
 */
static int __init lkm_init(void)
{
    printk(KERN_INFO "I: LKM for partb_21CS10016_21CS30037 loaded\n");

    proc_file = proc_create(PROCFS_NAME, 0666, NULL, &proc_fops); // Create the proc file
    if (!proc_file)
    {
        printk(KERN_ALERT "E: Could not create process file\n");
        return -ENOENT;
    }

    printk(KERN_INFO "I: /proc/%s created\n", PROCFS_NAME);
    return 0;
}

/**
 * process_list_delete: Delete the process list
 */
static void process_list_delete(void)
{
    struct process_node *curr = process_list;
    struct process_node *next = NULL;
    while (curr)
    {
        next = curr->next;
        if (curr->process_set)
        {
            set_delete(curr->process_set);
        }
        kfree(curr);
        curr = next;
    }
    process_list = NULL;
}

/**
 * lkm_exit: Module exit function
 */
static void __exit lkm_exit(void)
{
    process_list_delete();
    remove_proc_entry(PROCFS_NAME, NULL);
    printk(KERN_INFO "I: LKM for partb_set unloaded\n");
}

module_init(lkm_init); // Register the module initialization function
module_exit(lkm_exit); // Register the module exit function