#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define BUF_SIZE 1024
#define IP  "127.0.0.1"

double get_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { perror("socket"); exit(EXIT_FAILURE); }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, IP, &serv_addr.sin_addr) <= 0) {
        perror("inet_pton"); close(sockfd); exit(EXIT_FAILURE);
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect"); close(sockfd); exit(EXIT_FAILURE);
    }

    char buf[BUF_SIZE];
    const char *msg = "START\n";

    double start_time = get_time_ms();

    if (write(sockfd, msg, strlen(msg)) < 0) { perror("write"); close(sockfd); exit(EXIT_FAILURE); }

    ssize_t n = read(sockfd, buf, sizeof(buf)-1);
    if (n <= 0) {
        printf("Server closed connection or read error\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    buf[n] = '\0';

    double end_time = get_time_ms();
    printf("Server response: %s", buf);
    printf("Request handling latency: %.2f ms\n", end_time - start_time);

    close(sockfd);
    return 0;
}
