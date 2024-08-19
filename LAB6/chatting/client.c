#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define STOP_MESSAGE "stop"

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IP addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported\n");
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed\n");
        return -1;
    }

    printf("Connected to the server. Start chatting...\n");

    while (1) {
        printf("Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline

        send(sock, buffer, strlen(buffer), 0);

        // Check for stop message
        if (strncmp(buffer, STOP_MESSAGE, strlen(STOP_MESSAGE)) == 0) {
            printf("You have left the chat.\n");
            break;
        }

        memset(buffer, 0, BUFFER_SIZE);
        int valread = read(sock, buffer, BUFFER_SIZE);
        if (valread < 0) {
            perror("Read failed");
            close(sock);
            exit(EXIT_FAILURE);
        }

        printf("Server: %s\n", buffer);

        // Check for stop message
        if (strncmp(buffer, STOP_MESSAGE, strlen(STOP_MESSAGE)) == 0) {
            printf("Server has left the chat.\n");
            break;
        }
    }

    close(sock);
    return 0;
}
