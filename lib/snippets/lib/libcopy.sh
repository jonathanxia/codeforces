#!/usr/bin/bash

cd ../..;

while (($#))
do
    cp "$1.h" "snippets/lib/$1.txt"
    shift;
done

