/*
Mismo numero a los dos lados de la soga, pesos más equilibrados posibles
*/

param a;
param b;
param c:=a*b;

var d;
var e;
var f= a*b;

param n_personas > 0, integer;
set set_personas:=1..n_personas;

param pesos{set_personas};

var in_izquierda{i in set_personas}, binary;
var in_derecha{i in set_personas}, binary;



#var peso_izquierda= sum{i in set_personas} pesos[i]*in_izquierda[i];
#var peso_derecha:= sum{i in set_personas} pesos[i] * in_derecha[i];

minimize  dif_peso:
  sum{i in set_personas} (pesos[i] * in_izquierda[i]) - sum{i in set_personas} (pesos[i] * in_derecha[i]);

s.t. positivo:
  sum{i in set_personas} pesos[i] * in_izquierda[i] - sum{i in set_personas} pesos[i] * in_derecha[i] >= 0;

s.t. todos_asignados:
  sum{i in set_personas} in_izquierda[i] +   sum{i in set_personas} in_derecha[i]= n_personas;

s.t. no_omnipresencia:
  sum{i in set_personas} (1*in_izquierda[i] * 1*in_derecha[i])= 0;

solve;

printf dif_peso;

printf "\n";
display{i in set_personas: in_izquierda[i]=1 }: in_izquierda[i];
printf "\n";
display{i in set_personas: in_izquierda[i]=1 }: in_izquierda[i]*pesos[i];
printf "\n";
display{i in set_personas: in_izquierda[i]=1 }: in_derecha[i];
printf "\n";
display{i in set_personas: in_derecha[i]=1 }: in_derecha[i]*pesos[i];
printf "\n";

data;

param n_personas:= 4;

param pesos:=
1 1
2 2
3 3
4 4;
