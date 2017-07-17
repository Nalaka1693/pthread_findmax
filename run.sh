#!/usr/bin/env bash
gcc -o pthrd pthrd.c -lpthread
./pthrd
#var=$(./pthrd) && echo var
