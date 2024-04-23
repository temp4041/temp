#!/bin/bash

# Task (a): Display OS version, release number, kernel version
echo "Operating System: $(uname -s)"
echo "Release Number: $(uname -r)"
echo "Kernel Version: $(uname -v)"

# Task (b): Display current logged in user and login name
echo "Current Logged-in User: $(whoami)"
echo "Login Name: $(logname)"

