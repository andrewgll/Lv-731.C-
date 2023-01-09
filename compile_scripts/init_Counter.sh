#!/bin/bash

g++ -O2 ./Counter/code/main.cpp ./Counter/lib/timer.h -o ./Counter/bin/Counter -std=c++17 -pthread

./Counter/bin/Counter