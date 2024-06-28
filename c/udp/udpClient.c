#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_PORT 65533
#define BUFFER_SIZE 2048

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int message_len;
    socklen_t addr_len;

    // 创建 UDP 套接字
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址结构
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("inet_pton failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        // 获取用户输入
        printf("Input lowercase sentence (type 'exit' to quit): ");
        fgets(buffer, BUFFER_SIZE, stdin);
        message_len = strlen(buffer);
        if (buffer[message_len - 1] == '\n') {
            buffer[message_len - 1] = '\0'; // 去掉换行符
            message_len--;
        }

        // 发送数据到服务器
        if (sendto(sockfd, buffer, message_len, 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            perror("sendto failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        // 如果用户输入了 "exit"，退出循环
        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        // 接收来自服务器的响应
        addr_len = sizeof(server_addr);
        int recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&server_addr, &addr_len);
        if (recv_len < 0) {
            perror("recvfrom failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        buffer[recv_len] = '\0';
        printf("From Server: %s\n", buffer);
    }

    // 关闭套接字
    close(sockfd);

    return 0;
}
