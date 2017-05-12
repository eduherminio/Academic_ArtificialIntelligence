#!/bin/bash
clear
set -e

./compile_queens.sh

read -rsp $'---> Press any key to continue <---\n' -n 1 key

./compile_sudoku.sh


# set -e
#   Any subsequent(*) commands failing makes the shell script to exit.

# source filedata.txt
#   Reads variables from filedata.txt

# mkdir -p
#   creates a folder only if it doesn't exist

# &> /dev/null
#   Suppreses output

# | tee ../$filename.txt
#   Copies the output to a file

# make -j N
#   For minimum build times, you want to use a value of N that is one more than the number of cores on the machine


#
# Author:      Eduardo Cáceres de la Calle
# Subject:     Inteligencia Artificial
# Degree:      Industrial Electronics and Automatic Control Engineering
# University:  Universidad de Valladolid (UVa) - EII
#
# Code written in 2017.
# Uploaded for educational purposes only.
#
#_queens
