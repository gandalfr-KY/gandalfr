#!/bin/bash

START_DIR="."
EXTENSION=".hpp"

format_file() {
    echo "Formatting $1"
    clang-format -i $1

    if [[ "$(tail -c1 $1)" != "" ]]
    then
        echo "" >> $1
    fi
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
