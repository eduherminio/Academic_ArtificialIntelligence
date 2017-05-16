
param num_grupos, integer;
param num_vehiculos, integer;

set Grupos:=1..num_grupos;
set Vehiculos:=1..num_vehiculos;

param pesos    {Grupos};

param capacidad, integer;

################################################################################

var x{i in Grupos, j in Vehiculos}, binary;           # x[i,j]=1: el grupo i ha montado en la furgoneta j
var furgonetas_usadas{Vehiculos}, binary;

minimize objetivo: sum{i in Vehiculos} furgonetas_usadas[i];


s.t. capacidad_vehiculo {j in Vehiculos}: sum{i in Grupos}    x[i,j]*pesos[i] <= capacidad*furgonetas_usadas[j];
s.t. no_omnipresencia   {i in Grupos}:    sum{j in Vehiculos} x[i,j] = 1;

#s.t. nadie_en_tierra:   sum{i in Grupos, j in Vehiculos} x[i,j] = num_vehiculos;       # Not needed
#s.t. numero_furgonetas: sum{i in Vehiculos} furgonetas_usadas[i] <= num_vehiculos;

################################################################################

solve;

display objetivo;

data;

param num_grupos:= 10;
param num_vehiculos:= 10;
param capacidad:=8;
param pesos:=
1 2
2 3
3 4
4 5
5 1
6 2
7 3
8 2
9 1
10 2;   # ->  4
#10 1;  # ->  3
end;
