#!/bin/bash

g++ -g ./Counter/code/main.cpp ./Counter/lib/timer.h -o ./Counter/bin/Counter_debug -std=c++17 -pthread

./Counter/bin/Counter_debug