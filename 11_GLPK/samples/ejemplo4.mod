/* Variables */
var x1 >=0;
var x4 >=0;
var x2 integer >= 0;
var x3 >=0,integer;
/* Válidas las dos formas para forzar que sean enteras */

/* Funcion objetivo */
maximize objetivo : -3*x1 -2*x2+10;

/* Restricciones */
s.t. rest1: x1 - 2*x2 + x3 = 2.5;
s.t. rest2: 2*x1 + x2 +x4 >= 1.5;

solve;

display x1,x2,x3,x4;
display objetivo;
end;
