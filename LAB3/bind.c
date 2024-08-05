#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // For struct sockaddr_in
#include <arpa/inet.h>  // For htons and inet_addr
#include <stdio.h>

int main()
{
    int sockfd, b1;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("socket=%d\n", sockfd);
    if (sockfd != -1)
    {
        printf("Socket is created successfully\n");
    }
    else
    {
        printf("Socket is not created\n");
    }

    struct sockaddr_in sender; // Declare a sender structure

    // Populating the structure
    sender.sin_family = AF_INET;
    sender.sin_port = htons(8080);
    sender.sin_addr.s_addr = inet_addr("127.0.0.1");

    b1 = bind(sockfd, (const struct sockaddr *)&sender, sizeof(sender));
    printf("Bind value = %d\n", b1);
    return 0;
}
