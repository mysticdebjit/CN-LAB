#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    int sockfd, newsockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[1024];
    ssize_t bytes_read;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(50000);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(sockfd);
        return 1;
    }

    if (listen(sockfd, 5) == -1) {
        perror("Listening failed");
        close(sockfd);
        return 1;
    }

    printf("Server is listening on port 50000\n");

    newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_len);
    if (newsockfd == -1) {
        perror("Client connection failed");
    } else {
        printf("Client connected successfully\n");
        while (1) {
            memset(buffer, 0, sizeof(buffer));
            bytes_read = recv(newsockfd, buffer, sizeof(buffer), 0);
            if (bytes_read <= 0) {
                perror("Receive failed");
                break;
            }

            printf("Client: %s\n", buffer);

            if (strcmp(buffer, "exit") == 0) {
                printf("Client has disconnected.\n");
                break;
            }

            printf("Server: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            send(newsockfd, buffer, strlen(buffer), 0);

            if (strcmp(buffer, "exit") == 0) {
                printf("Server has disconnected.\n");
                break;
            }
        }
    }

    close(newsockfd);
    close(sockfd);

    return 0;
}
