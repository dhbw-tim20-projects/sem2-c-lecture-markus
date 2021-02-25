#!/bin/bash

gcc -c helloworldtxt.c
gcc -c helloworld.c -I.

gcc -o helloworld helloworld.o helloworldtxt.o
