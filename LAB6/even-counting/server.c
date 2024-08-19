#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int sockfd;
    char buf[1024];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd != -1) {
        printf("Socket is created successfully\n");
    } else {
        printf("Socket creation failed\n");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        printf("Bind failed\n");
        return 1;
    } else {
        printf("Bind successful\n");
    }

    while (1) {
        int recv_len = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &addr_len);
        if (recv_len == -1) {
            printf("Receiving failed\n");
        } else {
            buf[recv_len] = '\0';
            printf("Received array data: %s\n", buf);

            int n;
            sscanf(buf, "%d", &n);

            int arr[n];
            char *token = strtok(buf, " ");
            token = strtok(NULL, " ");
            for (int i = 0; i < n; i++) {
                arr[i] = atoi(token);
                token = strtok(NULL, " ");
            }

            int even_count = 0;
            for (int i = 0; i < n; i++) {
                if (arr[i] % 2 == 0) {
                    even_count++;
                }
            }

            sprintf(buf, "%d", even_count);
            if (sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&client_addr, addr_len) == -1) {
                printf("Error in sending\n");
            } else {
                printf("Even number count sent back to client\n");
            }
        }
    }

    return 0;
}
