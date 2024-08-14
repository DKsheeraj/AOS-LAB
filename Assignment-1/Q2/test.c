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

    // Read will return all the values in the set
    int read_values[length];
    if (read(fd, read_values, sizeof(read_values)) != sizeof(read_values)) {
        perror("Error reading values from set");
        close(fd);
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < length; i++) {
        printf("Read value %d from the set\n", read_values[i]);
    }

    close(fd);
}

int main() {
    // seed the random number generator
    srand(getpid());
    int *values;

    int length = rand() % 10 + 5;

    values = (int *)malloc(length * sizeof(int));
    if (values == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < length; i++) {
        // generate a new random value
        values[i] = rand() % 100;
        while(1)
        {
            int flag = 0;
            for(int j = 0; j < i; j++)
            {
                if(values[j] == values[i])
                {
                    flag = 1;
                    break;
                }
            }
            if(flag == 1)
            {
                values[i] = rand() % 100;
            }
            else
            {
                break;
            }
        }
    }

    // int values[] = {1, 2, 3, 4, 5};
    // int length = 5;

    // print the values
    printf("Values: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", values[i]);
    }

    printf("Starting test for LKM set module...\n");
    test_set(values, length);
    printf("Test completed.\n");

    return 0;
}
