#include <netinet/in.h>  // For struct sockaddr_in
#include <arpa/inet.h>   // For htons and inet_addr
#include <stdio.h>
#include <string.h>      // For strlen

int main() {
    int sockfd, b1;
    char buf[100];
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("socket=%d\n", sockfd);
    if (sockfd != -1) {
        printf("Socket is created successfully\n");
    } else {
        printf("Socket is not created\n");
        return 1;
    }

    struct sockaddr_in sender; // Declare a sender structure

    sender.sin_family = AF_INET;
    sender.sin_port = htons(8080);
    sender.sin_addr.s_addr = inet_addr("127.0.0.1");

    b1 = bind(sockfd, (const struct sockaddr *)&sender, sizeof(sender));
    printf("Bind value = %d\n", b1);
    printf("enter a number: ");
    scanf("%s", buf);

    struct sockaddr_in client; // Declare a client structure for sending data
    client.sin_family = AF_INET;
    client.sin_port = htons(8080);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");

    int snd = sendto(sockfd, buf, strlen(buf), 0, (const struct sockaddr *) &client, sizeof(client));
    if (snd == -1) {
        printf("Error in sending\n");
    } else {
        printf("Number sent successfully\n");
    }

    int recv_len = recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);
    if (recv_len == -1) {
        printf("Error in receiving\n");
    } else {
        buf[recv_len] = '\0'; 
        printf("Server response: %s\n", buf);
    }

    return 0;
}
