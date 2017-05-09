/* Problema sin solución */

/* Variables */
var x1 >=0;
var x2 >=0;

/* Funcion objetivo */
maximize objetivo : 4*x1 +2*x2;

/* Restricciones */
s.t. rest1: x1 + x2 = 40;
s.t. rest2: x1 + x2 >= 120;

solve;
end;
