/* ASSIGN, Assignment Problem */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* The assignment problem is one of the fundamental combinatorial
   optimization problems.

   In its most general form, the problem is as follows:

   There are a number of agents and a number of tasks. Any agent can be
   assigned to perform any task, incurring some cost that may vary
   depending on the agent-task assignment. It is required to perform all
   tasks by assigning exactly one agent to each task in such a way that
   the total cost of the assignment is minimized.

   (From Wikipedia, the free encyclopedia.) */

/* Modificado para la asignatura INTELIGENCIA ARTIFICIAL APLICADA
por FELIX MIGUEL TRESPADERNE EN 2016 */

/* Numero de agentes */
param num_agentes, integer, > 0;

/* Numero de tareas */
param num_tareas:=num_agentes;

/* Agentes*/
set Agentes := 1..num_agentes;

/* Tareas */
set Tareas := 1..num_tareas;

/* Coste de asignar la tarea j al agente i */
param coste{i in Agentes, j in Tareas}, >= 0;

/* x[i,j] = 1 significa qye la tarea j ha sido asignada al agente i */
var x{i in Agentes, j in Tareas}, binary;     # Matriz

/* El objetivo es lograr la asignacion mas economca */
minimize obj: sum{i in Agentes, j in Tareas} coste[i,j] * x[i,j];

/* Cada agente debe realizar una unica tarea */
s.t. restriccion_1{i in Agentes}: sum{j in Tareas} x[i,j] = 1;    # (i en agentes) restricciones: para i=1, 2, .. Agentes  || # i fija

/* Cada tarea debe asignarse a un unico agente */
s.t. restriccion_2{j in Tareas}: sum{i in Agentes} x[i,j] = 1;    # j fija

solve;

printf "\n";
printf "Agente  Tarea       Coste\n";
printf{i in Agentes} "%5d %5d %10g\n", i, sum{j in Tareas} j * x[i,j],
   sum{j in Tareas} coste[i,j] * x[i,j];
printf "----------------------\n";
printf "     Total: %10g\n", sum{i in Agentes, j in Tareas} coste[i,j] * x[i,j];
printf "\n";

data;

/* These data correspond to an example from [Christofides]. */

/* Optimal solution is 76 */

param num_agentes := 8;


param coste :
          1  2  3  4  5  6  7  8 :=
      1  13 21 20 12  8 26 22 11
      2  12 36 25 41 40 11  4  8
      3  35 32 13 36 26 21 13 37
      4  34 54  7  8 12 22 11 40
      5  21  6 45 18 24 34 12 48
      6  42 19 39 15 14 16 28 46
      7  16 34 38  3 34 40 22 24
      8  26 20  5 17 45 31 37 43 ;

end;
