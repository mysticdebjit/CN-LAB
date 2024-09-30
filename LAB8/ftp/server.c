#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    int sockfd, newsockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[1024];
    ssize_t bytes_received, bytes_read;
    FILE *file;

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
    else {
        printf("Server is listening on Port 50000\n");
    }

    newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_len);
    if (newsockfd == -1) {
        perror("Client connection failed");
    } else {
        printf("Client connected\n");
        file = fopen("received_file.txt", "w");
        if (file == NULL) {
            perror("File open failed");
        } else {
            printf("File Recieved Successfully\n");
            while ((bytes_received = recv(newsockfd, buffer, sizeof(buffer), 0)) > 0) {
                fwrite(buffer, sizeof(char), bytes_received, file);
            }
            fclose(file);

            char *ack_msg = "Server: File received successfully!";
            send(newsockfd, ack_msg, strlen(ack_msg), 0);

            file = fopen("received_file.txt", "r");
            if (file == NULL) {
                perror("File open failed to resend");
            } else {
                printf("File resent successfully\n");
                while ((bytes_read = fread(buffer, sizeof(char), sizeof(buffer), file)) > 0) {
                    send(newsockfd, buffer, bytes_read, 0);
                }
                fclose(file);
                shutdown(newsockfd, SHUT_WR);
            }
        }
    }

    close(newsockfd);
    close(sockfd);

    return 0;
}

