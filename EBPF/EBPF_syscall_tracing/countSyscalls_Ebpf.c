#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "test.txt";

    int fd = open(filename, O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    write(fd, "Hello eBPF\n", 11);

    close(fd);

    for (int i = 0; i < 5; i++) {
        fd = open(filename, O_RDONLY);
        if (fd < 0) {
            perror("open");
            return 1;
        }
        close(fd);
    }

    return 0;
}
