#!/usr/bin/env bash

g++ -g -Wno-return-type -Wshadow -std=c++17 -D_GLIBCXX_DEBUG -fsanitize=undefined,address -ftrapv $1
python3 $(dirname $(realpath $0))'/cph_to_txt.py' -i temp.txt $1 >/dev/null $2
gdb --quiet -ex='r <temp.txt' a.out
rm temp.txt