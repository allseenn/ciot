#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUF_SIZE 1024
#define ADDRESS "192.168.1.9"
#define SOP 0x7E  // Start of Packet
#define EOP 0x7E  // End of Packet
#define ESC 0x7D  // Escape character

void byte_stuffing(const char *input, char *output, int *output_len) {
    int j = 0;
    output[j++] = SOP;

    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == SOP || input[i] == ESC) {
            output[j++] = ESC;
            output[j++] = input[i] ^ 0x20;
        } else {
            output[j++] = input[i];
        }
    }

    output[j++] = EOP;
    *output_len = j;
}

void byte_unstuffing(const char *input, int input_len, char *output) {
    int j = 0;
    for (int i = 1; i < input_len - 1; i++) {  // skip SOP and EOP
        if (input[i] == ESC) {
            output[j++] = input[++i] ^ 0x20;
        } else {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
}

void *receive_messages(void *socket_desc) {
    int sock = *(int *)socket_desc;
    char buffer[BUF_SIZE];
    int bytes_received;

    while ((bytes_received = recv(sock, buffer, BUF_SIZE, 0)) > 0) {
        char unstuffed_message[BUF_SIZE];
        byte_unstuffing(buffer, bytes_received, unstuffed_message);
        printf("%s\n", unstuffed_message);
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

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, ADDRESS, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(sock);
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server at %s\n", ADDRESS);

    if (pthread_create(&recv_thread, NULL, receive_messages, (void *)&sock) != 0) {
        perror("Could not create thread");
        close(sock);
        exit(EXIT_FAILURE);
    }

    while (1) {
        fgets(message, BUF_SIZE, stdin);
        message[strcspn(message, "\n")] = 0;  // Remove newline character

        char stuffed_message[BUF_SIZE * 2];
        int stuffed_len;
        byte_stuffing(message, stuffed_message, &stuffed_len);

        if (send(sock, stuffed_message, stuffed_len, 0) == -1) {
            perror("send failed");
        }
    }

    close(sock);
    pthread_join(recv_thread, NULL);

    return 0;
}
