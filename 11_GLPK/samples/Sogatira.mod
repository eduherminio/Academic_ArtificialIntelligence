/*Parametros*/
param num_items,integer;
set Items:=1..num_items;
set equipos:=1..2;
param pesos{Items}, >0;

/*Variables*/
var x{i in Items,j in 1..2}, binary;

var peso_maximo >= 0;
var peso_minimo >= 0;
minimize objetivo: peso_maximo-peso_minimo;

s.t. una_persona_un_equipo{i in Items}: sum{j in 1..2} x[i,j] = 1;
s.t. diferencia_maxima_1_persona_1:sum{i in Items} (x[i,2]-x[i,1])<=1;
s.t. diferencia_maxima_1_persona_2:sum{i in Items} (x[i,1]-x[i,2])<=1;

s.t. pesos_1{j in 1..2}: sum{i in Items} pesos[i]*x[i,j] <= peso_maximo;
s.t. pesos_2{j in 1..2}: sum{i in Items} pesos[i]*x[i,j] >= peso_minimo;

solve;

printf "La solucion es:\n";
printf "Equipo 1:\n";
printf {i in Items: x[i,1]} " %i %i\n", i,pesos[i];
printf "Equipo 2:\n";
printf {i in Items: x[i,2]} " %i %i\n", i,pesos[i];
printf "Peso total en la primera particion:\n";
printf " %i\n", sum{i in Items} (x[i,1]*pesos[i]);
printf "Peso total en la segunda particion:\n";
printf " %i\n", sum{i in Items} (x[i,2]*pesos[i]);
printf "\n";

data;

param num_items := 10;
param pesos :=
 1 771
 2 121
 3 281
 4 854
 5 885
 6 734
 7 486
 8 1003
 9 83
 10 62;
end;