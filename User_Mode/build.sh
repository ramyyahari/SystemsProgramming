#!/bin/bash


as86 -o ts.o ts.s
bcc -c -ansi t.c int.c queue.c wait.c kernel.c
ld86 -d -o mtx ts.o t.o queue.c int.o wait.o kernel.o mtxlib /usr/lib/bcc/libc.a

echo "done!"
