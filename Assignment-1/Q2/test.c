#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PROC_FILE "/proc/partb_21CS10016_21CS30037"

void test_set(int *values, int length) {
    int fd = open(PROC_FILE, O_RDWR);
    if (fd == -1) {
        perror("Error opening proc file");
        exit(EXIT_FAILURE);
    }

    // Initialize the set with its capacity
    char capacity = (char)length;
    if (write(fd, &capacity, 1) != 1) {
        perror("Error writing capacity");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Set initialized with capacity: %d\n", length);

    // Insert values into the set
    for (int i = 0; i < length; i++) {
        if (write(fd, &values[i], sizeof(int)) != sizeof(int)) {
            perror("Error writing value to set");
            close(fd);
            exit(EXIT_FAILURE);
        }
        printf("Inserted value %d into the set\n", values[i]);
    }

    // Read values back from the set
    int out;
    for (int i = 0; i < length; i++) {
        if (read(fd, &out, sizeof(int)) != sizeof(int)) {
            perror("Error reading value from set");
            close(fd);
            exit(EXIT_FAILURE);
        }
        printf("Read value %d from the set\n", out);
    }

    close(fd);
}

int main() {
    int values[] = {10, 20, 30, 40, 50};
    int length = sizeof(values) / sizeof(values[0]);

    printf("Starting test for LKM set module...\n");
    test_set(values, length);
    printf("Test completed.\n");

    return 0;
}
