#!/bin/bash
cd /proc
n_cores=`cat cpuinfo | grep processor | wc -l`
let "n_cores++"

# For minimum build times, you want to use a value of N that is one more than the number of cores on the machine
