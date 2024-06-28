#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h> // Добавляем этот заголовок для функции signal и макроса SIGINT

#define PORT 8080
#define BUF_SIZE 1024
#define MAX_CLIENTS 10

typedef struct {
    int socket;
    struct sockaddr_in address;
} client_info;

client_info client_sockets[MAX_CLIENTS];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;
int server_socket;

void send_message_to_all(char *message, int sender_socket) {
    pthread_mutex_lock(&clients_mutex);

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_sockets[i].socket != 0 && client_sockets[i].socket != sender_socket) {
            if (send(client_sockets[i].socket, message, strlen(message), 0) == -1) {
                perror("send");
            }
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

void *handle_client(void *arg) {
    client_info *client = (client_info *)arg;
    int client_socket = client->socket;
    char buffer[BUF_SIZE];
    int bytes_received;

    while ((bytes_received = recv(client_socket, buffer, BUF_SIZE, 0)) > 0) {
        buffer[bytes_received] = '\0';
        char message_with_addr[BUF_SIZE + 50]; // Добавляем место для адреса
        snprintf(message_with_addr, sizeof(message_with_addr), "%s:%d: %s",
                 inet_ntoa(client->address.sin_addr), ntohs(client->address.sin_port), buffer);
        send_message_to_all(message_with_addr, client_socket);
    }

    close(client_socket);

    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_sockets[i].socket == client_socket) {
            client_sockets[i].socket = 0;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);

    free(arg);
    pthread_exit(NULL);
}

void close_server(int sig) {
    printf("Shutting down server...\n");

    // Close all client sockets
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_sockets[i].socket != 0) {
            close(client_sockets[i].socket);
            client_sockets[i].socket = 0;
        }
    }
    pthread_mutex_unlock(&clients_mutex);

    // Close server socket
    close(server_socket);

    exit(0);
}

int main() {
    int new_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    pthread_t tid;

    // Set up signal handler
    signal(SIGINT, close_server);

    // Initialize client sockets array
    for (int i = 0; i < MAX_CLIENTS; i++) {
        client_sockets[i].socket = 0;
    }

    // Create server socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket to address
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 3) < 0) {
        perror("listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len)) < 0) {
            perror("accept failed");
            close(server_socket);
            exit(EXIT_FAILURE);
        }

        printf("New connection accepted from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        pthread_mutex_lock(&clients_mutex);

        int i;
        for (i = 0; i < MAX_CLIENTS; i++) {
            if (client_sockets[i].socket == 0) {
                client_sockets[i].socket = new_socket;
                client_sockets[i].address = client_addr;
                break;
            }
        }

        if (i == MAX_CLIENTS) {
            printf("Max clients reached. Connection rejected.\n");
            close(new_socket);
        } else {
            client_info *new_client = malloc(sizeof(client_info));
            new_client->socket = new_socket;
            new_client->address = client_addr;
            pthread_create(&tid, NULL, handle_client, (void *)new_client);
            pthread_detach(tid);
        }

        pthread_mutex_unlock(&clients_mutex);
    }

    close(server_socket);
    return 0;
}
