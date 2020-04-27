#!/bin/bash
./dlc -e bits.c
if [ $? == 0 ]
then
    make btest
    ./btest
fi