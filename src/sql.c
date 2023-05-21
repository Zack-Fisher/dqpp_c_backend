#include "sql.h"
#include "main.h"

#include <stdio.h>

sqlite3* init_db() {
    sqlite3* db;
    sqlite3** ppdb = &db;
    if (sqlite3_open("test.db", ppdb)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }
    return db;
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void exec_wrapper(sqlite3 *db, char* command) {
    // errors is just on the stack, so we shouldn't stack overflow since the library handles the stack memory?
    char* response;
    sqlite3_exec(db, command, callback, 0, &response);

    #ifdef DEBUG
        printf("exec_wrapper: %s\n", command);
    #endif

    if (response != NULL) {
        fprintf(stderr, "SQL response: %s\n", response);
        sqlite3_free(response);
    }
}

