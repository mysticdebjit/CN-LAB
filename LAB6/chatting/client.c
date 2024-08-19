#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main() {
    int sockfd;
    char buf[1024];
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd != -1) {
        printf("Socket is created successfully\n");
    } else {
        printf("Socket is not created\n");
        return 1;
    }

    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(server_addr);

    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(8081);
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sockfd, (const struct sockaddr *)&client_addr, sizeof(client_addr)) == -1) {
        printf("Client bind failed\n");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); 
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (1) {
        printf("Client: ");
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0'; 

        if (sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&server_addr, addr_len) == -1) {
            printf("Error in sending\n");
        } else {
            printf("Message sent successfully\n");
        }

        if (strcmp(buf, "stop") == 0) {
            printf("You have left the chat.\n");
            break;
        }

        int recv_len = recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);
        if (recv_len == -1) {
            printf("Error in receiving\n");
        } else {
            buf[recv_len] = '\0'; 
            printf("Server: %s\n", buf);
        }

        if (strcmp(buf, "stop") == 0) {
            printf("Server has left the chat.\n");
            break;
        }
    }

    return 0;
}

