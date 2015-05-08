#!/bin/bash

gpaste -d, <(gseq 1000 | gsort -R) <(gseq 1000 | gsort -R) <(gseq 1000 | gsort -R)
