CC = gcc
CFLAGS = -pthread -Wall -Wextra -std=c11

SERVER_SRC = server.c
SERVER_BIN = server

CLIENT_SRC = client.c
CLIENT_BIN = client

all: $(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN): $(SERVER_SRC)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT_BIN): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(SERVER_BIN) $(CLIENT_BIN)

.PHONY: all clean
