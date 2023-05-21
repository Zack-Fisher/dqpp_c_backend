#pragma once

#include <sqlite3.h>

sqlite3* init_db();
void exec_wrapper(sqlite3 *db, char* command);
