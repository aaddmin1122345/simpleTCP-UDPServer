#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 65534
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // 创建 TCP 套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址结构
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET; // IPv4 地址族
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 服务器 IP 地址
    server_addr.sin_port = htons(PORT); // 服务器端口号，需要使用 htons() 转换为网络字节顺序

    // 连接服务器
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server on port %d\n", PORT);

    while (1) {
        // 发送数据
        printf("Input lowercase sentence (type 'exit' to quit): ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            perror("fgets error or EOF");
            break;
        }

        // 去除末尾的换行符
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        if (send(sockfd, buffer, strlen(buffer), 0) < 0) {
            perror("send failed");
            break;
        }

        // 接收数据
        int recv_len = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if (recv_len < 0) {
            perror("recv failed");
            break;
        } else if (recv_len == 0) {
            printf("Server closed the connection\n");
            break;
        }

        buffer[recv_len] = '\0';
        printf("From Server: %s\n", buffer);
    }

    // 关闭连接
    close(sockfd);
    return 0;
}
