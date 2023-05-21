#!/bin/bash

killall program

TEST_PORT=5002

make
cd bin || exit
./program "$TEST_PORT" &
