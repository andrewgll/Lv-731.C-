#!/bin/sh
valgrind --tool=memcheck  --leak-check=yes --show-reachable=yes --num-callers=20 ./DynamicList/bin/stringList 