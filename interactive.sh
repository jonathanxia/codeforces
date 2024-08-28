#!/usr/bin/env bash

exec_dir=$(dirname $(realpath $0))

compile() {
    g++ -g -Wno-return-type -Wshadow -O0 -std=c++17 -D_GLIBCXX_DEBUG -fsanitize=undefined,address -ftrapv -DDEBUG -I $exec_dir -o $2 $1
}

compile $1 temp1
compile $2 temp2
compile $exec_dir'/interactive.cpp' temp3
$exec_dir'/temp3' $exec_dir'/temp1' $exec_dir'/temp2'

rm temp1 temp2 temp3