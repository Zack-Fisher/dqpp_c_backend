#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
#include "pthread.h"
#include "parsing.h"

#include "types.h"
#include "sql.h"
#include "route.h"
#include "main.h"

#define BUF_SIZE 1024
void handle_request(Client* client) {
    char buffer[BUF_SIZE];
    memset(buffer, 0, BUF_SIZE);
    // poll the user socket
    read(client->sockfd, buffer, BUF_SIZE);

    if (strlen(buffer) == 0)
        return;

    Request* request = parse_headers(buffer);
    
    char* response = handle_routing(client, request);

    free_request(request);

    write(client->sockfd, response, strlen(response));
}

void* handle_connection(void* socket_desc) {
    int new_socket = *(int*)socket_desc;

    Client* client = malloc(sizeof(Client));

    client->sockfd = new_socket;
    // generate random ID for the client
    client->id = rand() % 10000000;
    client->state = (GameState*)malloc(sizeof(GameState));

    // loop with the client data until the connection is closed
    for (;;) {
        handle_request(client);
    }

    close(new_socket);
    free(socket_desc);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    //seed
    srand(time(NULL));

    State* state = mk_state(atoi(argv[1]));


    // test out creating some tables and grabbing some data
    sqlite3* db = init_db();
    exec_wrapper(db, "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT NOT NULL, age INTEGER NOT NULL);");
    exec_wrapper(db, "INSERT INTO users (name, age) VALUES ('John', 30);");
    exec_wrapper(db, "INSERT INTO users (name, age) VALUES ('Jane', 25);");
    exec_wrapper(db, "INSERT INTO users (name, age) VALUES ('Bob', 40);");
    exec_wrapper(db, "INSERT INTO users (name, age) VALUES ('Alice', 35);");
    exec_wrapper(db, "SELECT * FROM users;");
    sqlite3_close(db);


    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    
    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Attach socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(state->port);
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while(1) {
        printf("\nWaiting for a connection...\n");
        
        int *new_sock = malloc(sizeof(void*));
        // block the thread until there's a new connection on the server file descriptor created from the bound socket.
        *new_sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (*new_sock < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_connection, (void*)new_sock) < 0) {
            perror("could not create thread");
            return 1;
        }
    }

    return 0;
}
