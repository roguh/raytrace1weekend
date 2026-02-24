#!/usr/bin/env bash
NAME="$(echo "$1" | sed 's/\.[^.]*$//')"
set -x
make view FILE="$NAME"
