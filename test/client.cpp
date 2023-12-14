
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

int main() {
    int socket_fd;
    struct sockaddr_in server_addr;
    char *message = "Hello, Server!";

    // 創建 socket
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    memset(&server_addr, '0', sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // 將 IP 轉換為適當的格式
    if(inet_pton(AF_INET, "192.168.0.10", &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return -1;
    }

    // 連線到伺服器
    if (connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }

    // 發送訊息給伺服器
    send(socket_fd, message, strlen(message), 0);
    printf("Message sent to server: %s\n", message);

    close(socket_fd);
    return 0;
}
