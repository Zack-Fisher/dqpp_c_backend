// define allocators (constructors!!!) and deallocators for complex types.

#include "types.h"
#include "sql.h"
#include <stdlib.h>

State* mk_state(int port) {
    State* state = malloc(sizeof(State));

    state->port = port;
    state->db = init_db();
    
    return state;
}
