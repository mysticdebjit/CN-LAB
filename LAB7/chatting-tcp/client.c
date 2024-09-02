#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];
    ssize_t bytes_read;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(50000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0) {
        printf("Connected to the server successfully\n");
        while (1) {
            printf("Client: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            send(sockfd, buffer, strlen(buffer), 0);

            if (strcmp(buffer, "exit") == 0) {
                printf("Client has disconnected.\n");
                break;
            }

            memset(buffer, 0, sizeof(buffer));
            bytes_read = recv(sockfd, buffer, sizeof(buffer), 0);
            if (bytes_read <= 0) {
                perror("Receive failed");
                break;
            }

            printf("Server: %s\n", buffer);

            if (strcmp(buffer, "exit") == 0) {
                printf("Server has disconnected.\n");
                break;
            }
        }
    } else {
        perror("Connection failed");
        close(sockfd);
        return 1;
    }

    close(sockfd);

    return 0;
}
