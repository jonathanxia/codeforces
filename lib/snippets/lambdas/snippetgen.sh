#! /usr/bin/bash

while (($#))
do
    cp "$1.h" "$1.txt"
    shift;
done
