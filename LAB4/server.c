#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main() {
    int sockfd;
    char buf[100];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed\n");
        return 1;
    } else {
        printf("Socket created successfully\n");
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (const struct sockaddr *)&server, sizeof(server)) == -1) {
        printf("Bind failed\n");
        return 1;
    } else {
        printf("Bind successful\n");
    }

    int recv_len = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&client, &len);
    if (recv_len == -1) {
        printf("Receiving failed\n");
    } else {
        buf[recv_len] = '\0'; 
        printf("Received message: %s\n", buf);
    }

    return 0;
}
