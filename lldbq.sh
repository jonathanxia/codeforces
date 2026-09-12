#!/usr/bin/env bash

# /usr/bin/g++ can be an Xcode clang older than the installed SDK headers;
# prefer the Command Line Tools clang with its matching SDK when present.
if [ -x /Library/Developer/CommandLineTools/usr/bin/clang++ ] && [ -d /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk ]; then
    CXX="/Library/Developer/CommandLineTools/usr/bin/clang++ -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk"
else
    CXX="g++"
fi

$CXX -g -Wno-return-type -Wshadow -O0 -std=c++17 -D_GLIBCXX_DEBUG \
    -fsanitize=undefined,address -ftrapv -DDEBUG \
    -I "$(dirname "$(realpath "$0")")" "$1"

python3 "$(dirname "$(realpath "$0")")/cph_to_txt.py" -i temp.txt "$1" >/dev/null "$2"

# run under LLDB, feeding temp.txt to stdin; remains interactive after run
lldb ./a.out -o "process launch -i temp.txt"

# clean up after you exit lldb
rm temp.txt
