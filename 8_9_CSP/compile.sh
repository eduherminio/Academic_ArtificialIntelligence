#!/bin/bash
clear
set -e
../system_info.sh
source filedata_queens.txt
export env_filename=$filename_queens
source filedata_sudoku.txt
export env_filename=$filename_sudoku
mkdir -p build && cd build
cmake ..  #&> /dev/nulls
make -j$n_cores #-B
echo 8_Queens_CSP:
./$filename_queens #| tee ./$filename.txt
echo 9_Sudoku_CSP:
./$filename_sudoku #| tee ./$filename.txt


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
