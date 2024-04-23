#!/bin/bash

# Task (a): Display current shell, home directory, operating system type, current path setting, and current working directory.
echo "Current Shell: $SHELL"
echo "Home Directory: $HOME"
echo "Operating System Type: $(uname -o)"
echo "Current Path Setting: $PATH"
echo "Current Working Directory: $(pwd)"

# Task (b): Display top 10 processes in descending order of memory usage
echo "Top 10 processes by memory usage:"
ps -eo pid,ppid,cmd,%mem,%cpu --sort=-%mem | head -n 11

