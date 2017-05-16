#!/bin/bash
clear
set -e

glpsol --math Empaquetado_Balanceado_1.mod

read -rsp $'---> Press any key to continue <---\n' -n 1 key

glpsol --math Empaquetado_Balanceado_2.mod


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
