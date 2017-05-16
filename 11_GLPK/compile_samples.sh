#!/bin/bash
clear
set -e
mkdir -p samples_sol

glpsol --math samples/ejemplo1.mod 	> samples_sol/ejemplo1.txt
glpsol --math samples/ejemplo2.mod 	> samples_sol/ejemplo2.txt
glpsol --math samples/ejemplo3.mod 	> samples_sol/ejemplo3.txt
glpsol --math samples/ejemplo4.mod 	> samples_sol/ejemplo4.txt
glpsol --math samples/ejemplo51.mod 	> samples_sol/ejemplo51.txt
glpsol --math samples/ejemplo52.mod 	> samples_sol/ejemplo52.txt
glpsol --math samples/ejemplo6.mod	> samples_sol/ejemplo_6.txt
glpsol --math samples/Queens.mod 	> samples_sol/Queens.txt
glpsol --math samples/TSP.mod		> samples_sol/TSP.txt

glpsol --math samples/Knapsack.mod	> samples_sol/Knapsack.txt
glpsol --math samples/Sogatira.mod	> samples_sol/Sogatira.txt
	
#
# Author:      Eduardo Cáceres de la Calle
# Subject:     Inteligencia Artificial
# Degree:      Industrial Electronics and Automatic Control Engineering
# University:  Universidad de Valladolid (UVa) - EII
#
# Code written in 2017.
# Uploaded for educational purposes only.
#
#
