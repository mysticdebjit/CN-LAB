#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>   

int main() {
    int sockfd;
    char buf[100];
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
    client_addr.sin_port = htons(8081); // Client port
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sockfd, (const struct sockaddr *)&client_addr, sizeof(client_addr)) == -1) {
        printf("Client bind failed\n");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); 
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int num1, num2;
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);

    sprintf(buf, "%d %d", num1, num2); 
    if (sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&server_addr, addr_len) == -1) {
        printf("Error in sending\n");
    } else {
        printf("Numbers sent successfully\n");
    }

    int recv_len = recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);
    if (recv_len == -1) {
        printf("Error in receiving\n");
    } else {
        buf[recv_len] = '\0';
        printf("Server response: The sum is %s\n", buf);
    }

    return 0;
}
