#!/bin/bash

START_DIR="."

EXTENSION=".hpp"

format_file() {
    echo "#include \"$1\""
    clang-format -i $1

    if [[ "$(tail -c1 $1)" != $'\n' ]]
    then
        echo "" >> $1
    fi

    sed -i -e :a -e '/^\n*$/{$d;N;};/\n$/ba' $1
}

scan_dir() {
    for entry in "$1"/*
    do
        if [[ -d "$entry" ]]; then
            scan_dir "$entry"
        elif [[ -f "$entry" ]]; then
            if [[ "$entry" == *$EXTENSION ]]; then
                format_file "$entry"
            fi
        fi
    done
}

scan_dir $START_DIR
