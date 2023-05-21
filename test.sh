#!/bin/bash

if [ -z "$1" ]; then
    TEST_PORT=5002
else
    TEST_PORT=$1
fi

# Array of data to send in the POST requests
# needs to be double quotes, no dangling commas
# dumb
data=(
    '
{"spell": "fireball"}
    '
)

headers="Content-Type: application/json"

# Endpoint URL
url="http://localhost:$TEST_PORT/battle/spell"

# Iterate over each data item and send a POST request
for item in "${data[@]}"; do
    # -H headers, -d data, -X POST request type then do all that to the url endpoint.
    curl -X POST -H "$headers" -d "$item" "$url"
done
