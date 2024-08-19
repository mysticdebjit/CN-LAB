#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  // For struct sockaddr_in
#include <arpa/inet.h>   // For htons and inet_addr
#include <stdio.h>
#include <string.h>      // For strlen

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

    // Populating the client structure (bind to client address)
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(8081); // Client port
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind client socket
    if (bind(sockfd, (const struct sockaddr *)&client_addr, sizeof(client_addr)) == -1) {
        printf("Client bind failed\n");
        return 1;
    }

    // Populating the server structure (server address)
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); // Server port
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Input array size and elements from the user
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Send the array size and elements to the server
    sprintf(buf, "%d ", n); // Start with the size of the array
    for (int i = 0; i < n; i++) {
        char temp[10];
        sprintf(temp, "%d ", arr[i]);
        strcat(buf, temp);
    }

    if (sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&server_addr, addr_len) == -1) {
        printf("Error in sending\n");
    } else {
        printf("Array sent successfully\n");
    }

    // Receive the response from the server (count of even numbers)
    int recv_len = recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);
    if (recv_len == -1) {
        printf("Error in receiving\n");
    } else {
        buf[recv_len] = '\0'; // Null-terminate the received data
        printf("Server response: Number of even numbers = %s\n", buf);
    }

    return 0;
}
