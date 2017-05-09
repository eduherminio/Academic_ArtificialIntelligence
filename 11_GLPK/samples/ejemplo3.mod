/* Problema no acotado */

/* Variables */
var x1 >=0;
var x2 >=0;

/* Funcion objetivo */
maximize objetivo : 4*x1 +2*x2;

/* Restricciones */
s.t. rest1: 3*x1 + 6*x2 >=18;
s.t. rest2: x1 -2*x2 <= 4;

solve;
end;
