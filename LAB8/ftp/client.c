#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

int main(void) {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024], file_name[256];
    ssize_t bytes_read;
    FILE *file;
    DIR *dir;
    struct dirent *entry;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(50000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0) {
        printf("Connected to the server successfully\n");

        printf("Files in the current directory:\n");
        dir = opendir(".");
        if (dir == NULL) {
            perror("Unable to open directory");
            close(sockfd);
            return 1;
        }

        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_REG) {
                printf("%s\n", entry->d_name);
            }
        }
        closedir(dir);

        printf("\nEnter the name of the file to send: ");
        scanf("%s", file_name);

        file = fopen(file_name, "r");
        if (file == NULL) {
            perror("File open failed");
            close(sockfd);
            return 1;
        }

        while ((bytes_read = fread(buffer, sizeof(char), sizeof(buffer), file)) > 0) {
            send(sockfd, buffer, bytes_read, 0);
        }
        fclose(file);
        shutdown(sockfd, SHUT_WR);

        printf("Client: File sent successfully.\n");

        bytes_read = recv(sockfd, buffer, sizeof(buffer), 0);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            printf("%s\n", buffer);
        }

        file = fopen("received_back_file.txt", "w");
        if (file == NULL) {
            perror("File open failed to save received file");
        } else {
            while ((bytes_read = recv(sockfd, buffer, sizeof(buffer), 0)) > 0) {
                fwrite(buffer, sizeof(char), bytes_read, file);
            }
            fclose(file);
            printf("Client: File received back and saved as 'received_back_file.txt'.\n");
        }
    } else {
        perror("Connection failed");
        close(sockfd);
        return 1;
    }

    close(sockfd);

    return 0;
}

