# Segunda parte: equilibrar carga de las furgonetas

param num_grupos, integer;
param num_vehiculos, integer;

set Grupos:=1..num_grupos;
set Vehiculos:=1..num_vehiculos;

param pesos    {Grupos};

param capacidad, integer;

################################################################################

var x{i in Grupos, j in Vehiculos}, binary;           # x[i,j]=1: el grupo i ha montado en la furgoneta j

var peso_maximo >= 0, <=capacidad;  # Puede no hacer falta
var peso_minimo >= 0;
minimize objetivo: peso_maximo-peso_minimo;

#s.t. capacidad_vehiculo {j in Vehiculos}: sum{i in Grupos}    x[i,j]*pesos[i] <= capacidad;    # Nos aseguramos poniendo peso_maximo <= capacidad
s.t. no_omnipresencia   {i in Grupos}:    sum{j in Vehiculos} x[i,j] = 1;

s.t. cond_1 {j in Vehiculos}: sum{i in Grupos} pesos[i]*x[i,j] <= peso_maximo;                  # <-- a minimizar
s.t. cond_2 {j in Vehiculos}: sum{i in Grupos} pesos[i]*x[i,j] >= peso_minimo;

################################################################################

solve;

display objetivo;

printf "Peso total en la primera particion:\n";
printf " %i\n", sum{i in Grupos} (x[i,1]*pesos[i]);
printf "Peso total en la primera particion:\n";
printf " %i\n", sum{i in Grupos} (x[i,2]*pesos[i]);
printf "Peso total en la primera particion:\n";
printf " %i\n", sum{i in Grupos} (x[i,3]*pesos[i]);
printf "Peso total en la primera particion:\n";
printf " %i\n", sum{i in Grupos} (x[i,4]*pesos[i]);


data;

param num_grupos:= 10;
param num_vehiculos:= 4;
param capacidad:= 8;
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
