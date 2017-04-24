#!/bin/bash
clear
set -e
source filedata.txt
export env_filename=$filename
mkdir -p build && cd build
cmake ..  #&> /dev/null
make #-B
./$filename 5 5  | tee ../$filename.txt



# set -e
#   Any subsequent(*) commands failing makes the shell script to exit.

# source filedata.txt
#   Reads variables from filedata.txt

# &> /dev/null
#   Suppreses output

# 2> file.txt
#   Copies the output to the file, keeping a copy in the 
# echo $filename > filename.txt
#   aux. file to be read by CMakeList.txt

# rm filename.txt
#   deletion of aux. file

# BASEDIR=$(dirname "$0")
#   creates BASEDIR variable to host script directory
