# Mochila

param capacidad, integer, > 0;
param num_items, integer, > 0;
set Items:= 1..num_items;

param tam{Items};
param valor{Items};

var x{i in Items}, binary;

maximize obj:
  sum{i in Items} x[i]*valor[i];

  s.t. size:
    sum{i in Items} tam[i]*x[i]<= capacidad;

    #solo contribuyen las que valgan uno


solve;

display{i in Items} x[i]*valor[i];
display{i in Items: x[i]=1 }: x[i];
printf "\n";
printf obj;
printf "\n";

data;

param num_items:=4;
param capacidad:=10;
param tam:=
1 4
2 7
3 5
4 3;

param valor:=
1 40
2 42
3 25
4 12;
