#!/bin/bash

ROWS=10

field () {
    gseq $ROWS | awk '{print rand() * $0}' | gsort -R
}

gpaste -d, <(field) <(field) <(field) <(field) <(field)

# Check how column deals with a jacked record on the end
echo '123123123123123123123123123123,123,123,123,123'
