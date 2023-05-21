#!/bin/bash

killall program

make
cd bin || exit
./program "$C_PORT" &
