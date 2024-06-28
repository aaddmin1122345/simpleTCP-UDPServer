#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 65534
#define BACKLOG 5 // 允许的连接请求队列长度
#define BUFFER_SIZE 1024

int main() {
    int sockfd, new_sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[BUFFER_SIZE];
    int recv_len;

    // 创建 TCP 套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
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
        exit(EXIT_FAILURE);
    }

    // 监听连接请求
    if (listen(sockfd, BACKLOG) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        // 接受客户端连接请求
        client_len = sizeof(client_addr);
        new_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_len);
        if (new_sockfd < 0) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }

        printf("Accepted connection from %s:%d\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        while (1) {
            // 接收数据
            recv_len = recv(new_sockfd, buffer, sizeof(buffer), 0);
            if (recv_len > 0) {
                buffer[recv_len] = '\0';
                printf("Received: %s\n", buffer);

                // 转换为大写
                for (int i = 0; buffer[i] != '\0'; ++i) {
                    buffer[i] = toupper(buffer[i]);
                }

                // 发送大写后的数据
                if (send(new_sockfd, buffer, strlen(buffer), 0) < 0) {
                    perror("send failed");
                    break;
                }
            } else if (recv_len == 0) {
                printf("Client closed the connection\n");
                break;
            } else {
                perror("recv failed");
                break;
            }
        }

        // 关闭本次连接
        close(new_sockfd);
    }

    close(sockfd);
    return 0;
}
