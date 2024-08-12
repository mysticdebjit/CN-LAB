#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main() {
    int sockfd;
    char buf[100];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd != -1) {
        printf("Socket is created successfully\n");
    } else {
        printf("Socket creation failed\n");
        return 1;
    }

    // Populating the server structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); // Server port
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address and port
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        printf("Bind failed\n");
        return 1;
    }

    while (1) {
        // Receive message from the client
        int recv_len = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &addr_len);
        if (recv_len == -1) {
            printf("Receiving failed\n");
        } else {
            buf[recv_len] = '\0'; // Null-terminate the received data
            printf("Client: %s\n", buf);
        }

        // Send a response to the client
        printf("Server: Enter a message: ");
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0'; // Remove trailing newline

        if (sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&client_addr, addr_len) == -1) {
            printf("Error in sending\n");
        }
    }

    return 0;
}
