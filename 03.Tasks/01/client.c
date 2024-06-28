#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUF_SIZE 1024
#define ADDRESS "192.168.1.9" // Задайте нужный адрес здесь

void *receive_messages(void *socket_desc) {
    int sock = *(int *)socket_desc;
    char buffer[BUF_SIZE];
    int bytes_received;

    while ((bytes_received = recv(sock, buffer, BUF_SIZE, 0)) > 0) {
        buffer[bytes_received] = '\0';
        printf("%s\n", buffer);
    }

    if (bytes_received == 0) {
        printf("Server disconnected\n");
    } else {
        perror("recv failed");
    }

    close(sock);
    pthread_exit(NULL);
}

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char message[BUF_SIZE];
    pthread_t recv_thread;

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    // Set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, ADDRESS, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server at %s\n", ADDRESS);

    // Create a thread to receive messages
    if (pthread_create(&recv_thread, NULL, receive_messages, (void *)&sock) != 0) {
        perror("Could not create receive thread");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Send messages to server
    while (fgets(message, BUF_SIZE, stdin) != NULL) {
        if (send(sock, message, strlen(message), 0) < 0) {
            perror("Send failed");
            break;
        }
    }

    // Close the socket and exit
    close(sock);
    pthread_join(recv_thread, NULL);

    return 0;
}
