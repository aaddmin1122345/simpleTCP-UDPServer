#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 65533
#define BUFFER_SIZE 2048

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[BUFFER_SIZE];
    int recv_len;

    // 创建 UDP 套接字
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址结构
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET; // IPv4 地址族
    server_addr.sin_addr.s_addr = INADDR_ANY; // 使用 INADDR_ANY 表示接收所有网卡的连接
    server_addr.sin_port = htons(PORT); // 端口号，需要使用 htons() 转换为网络字节顺序

    // 绑定套接字到服务器地址
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("The server is ready to receive\n");

    while (1) {
        // 接收数据
        client_len = sizeof(client_addr);
        recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &client_len);
        if (recv_len < 0) {
            perror("recvfrom failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        buffer[recv_len] = '\0';
        printf("Received: %s\n", buffer);

        // 如果接收到 "exit"，退出循环
        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        // 转换为大写
        for (int i = 0; buffer[i] != '\0'; ++i) {
            buffer[i] = toupper(buffer[i]);
        }

        // 发送大写后的数据
        if (sendto(sockfd, buffer, recv_len, 0, (struct sockaddr*)&client_addr, client_len) < 0) {
            perror("sendto failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
    }

    close(sockfd);
    return 0;
}
