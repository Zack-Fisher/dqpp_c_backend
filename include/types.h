#pragma once

#include "sql.h"

#include "gamestate.h"

typedef struct {
    char* mime_type;
    char* request_line;
    char* body;
    char* method;
    char* url;
} Request;

// the global state of our server that'll we'll manage close to main and pass around through functions.
typedef struct {
    int port;
    sqlite3* db;
} State;

typedef struct {
    int id;
    int sockfd;
    // every client carries around state with their socket session.
    // once the session is closed, the state is destroyed.
    // save this in the DB somehow?
    GameState* state;
} Client;

State* mk_state(int port);
