#!/bin/bash

# カレントディレクトリから開始
START_DIR="."

# ファイル拡張子
EXTENSION=".hpp"

# clang-formatを実行し、必要に応じて末尾に改行を追加する関数
format_file() {
    echo "Formatting $1"
    clang-format -i $1

    # ファイルの最後の文字をチェックし、改行でない場合は追加します。
    if [[ "$(tail -c1 $1)" != "" ]]
    then
        echo "" >> $1
    fi
}

# 指定されたディレクトリを再帰的に走査する関数
scan_dir() {
    for entry in "$1"/*
    do
        if [[ -d "$entry" ]]; then
            # エントリがディレクトリの場合、それを走査します。
            scan_dir "$entry"
        elif [[ -f "$entry" ]]; then
            # エントリがファイルで、.hppで終わる場合、それをフォーマットします。
            if [[ "$entry" == *$EXTENSION ]]; then
                format_file "$entry"
            fi
        fi
    done
}

# 最初のディレクトリを走査します。
scan_dir $START_DIR
