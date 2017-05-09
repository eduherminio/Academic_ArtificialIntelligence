/* QUEENS, a classic combinatorial optimization problem */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* The Queens Problem is to place as many queens as possible on the 8x8
   (or more generally, nxn) chess board in a way that they do not fight
   each other. This problem is probably as old as the chess game itself,
   and thus its origin is not known, but it is known that Gauss studied
   this problem. */

/*Modificado para la asignatura INTELIGENCIA ARTIFICIAL APLICADA
por FELIX MIGUEL TRESPADERNE EN 2017*/

/* Tamanho del tablero */
param n, integer, > 0, default 8;

set Filas:=1..n;
set Columnas:=1..n;
set Diagonal_45:=1-n..n-1;
set Diagonal_135:=2..2*n;

/* x[i,j] = 1 significa una reina en el escaque [i,j] */
var x{i in Filas,j in Columnas}, binary;

/*Podriamos haber declarado
var x{1..n,1..n}, binary;
*/

/* Una y solo una reina en cada fila */
s.t. horizontal{i in Filas}: sum{j in Columnas} x[i,j] = 1;

/* Una y solo una reina en cada columna */
s.t. vertical{j in Columnas}: sum{i in Filas} x[i,j] = 1;

/* Como mucho una reina en cada diagonal */
s.t. diagonal_45{k in Diagonal_45}: sum{i in Filas, j in Columnas: i-j == k} x[i,j] <= 1;
s.t. diagonal_135{k in Diagonal_135}: sum{i in Filas, j in Columnas: i+j == k} x[i,j] <= 1;
# coge solo las i, j que complien que i-j=k

/* Colocar tantas reinas como sea posible*/
/* Podriamos no poner la funcion objetivo*/
maximize obj: sum{i in Filas, j in Columnas} x[i,j]; #realmente sobra, las propias restricciones guian al algoritmo


/* solve the problem */
solve;

/* and print its optimal solution */
for {i in Filas}
{  for {j in Columnas} printf " %s", if x[i,j] then "Q" else ".";
   printf("\n");
}

end;
