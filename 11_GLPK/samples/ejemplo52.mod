# Se protege al usuario de equivocarse restringiendo los valores de los parámetros

/* Parametros */
param n, integer, >= 1;             # Numero de items
param p, integer, >= 1, <n;         # De los cuales seleccionamos p
set Items:={1..n};                  # El conjunto de items, numerados del 1 al n
param coste{Items} >=0;             # Coste de los items

/* Variables */
var x{Items} binary;

/* Funcion objetivo */

minimize Coste_Total: sum{i in Items} coste[i]*x[i];

/* Restricciones */

s.t. justo_p_items: sum{i in Items} x[i] = p;

/* Resolver */
solve;

/* Mostrando resultados */


display{i in Items: x[i]=1 }: x[i];     /* Los x[i] con valor 1 */
display Coste_Total;

/*Datos */
data;
param n:=10;
param p:=6;
param coste:=
1 3
2 2
3 6
4 3
5 9
6 5
7 8
8 1
9 2
10 6;
end;
