#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main() {
    int sockfd, b1;
    char buf[100];
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("socket=%d\n", sockfd);
    if (sockfd != -1) {
        printf("Socket is created successfully\n");
    } else {
        printf("Socket is not created\n");
    }

    struct sockaddr_in sender;

    sender.sin_family = AF_INET;
    sender.sin_port = htons(8080);
    sender.sin_addr.s_addr = inet_addr("127.0.0.1");

    b1 = bind(sockfd, (const struct sockaddr *)&sender, sizeof(sender));
    printf("Bind value = %d\n", b1);
    printf("enter a msh: ");
    scanf("%s", buf);

    struct sockaddr_in client; 
    client.sin_family = AF_INET;
    client.sin_port = htons(8080);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");

    int snd = sendto(sockfd, buf, strlen(buf), 0, (const struct sockaddr *) &client, sizeof(client));
    if (snd == -1) {
        printf("Error");
    } else {
        printf("Successfully Sent");
    }
    
    return 0;
}
