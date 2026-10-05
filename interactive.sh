#!/usr/bin/env bash

exec_dir=$(dirname "$(realpath "$0")")
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT

compile() {
    g++ -g -Wno-return-type -Wshadow -O0 -std=c++17 -D_GLIBCXX_DEBUG -fsanitize=undefined,address -ftrapv -DDEBUG -I "$exec_dir" -o "$2" "$1"
}

compile "$1" "$tmp/temp1"
compile "$2" "$tmp/temp2"
compile "$exec_dir/interactive.cpp" "$tmp/temp3"
"$tmp/temp3" "$tmp/temp1" "$tmp/temp2"
