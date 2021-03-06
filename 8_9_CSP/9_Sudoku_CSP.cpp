#include "header/sudoku.h"
#include "header/cronometro.h"

int main()
{
  sudoku::Sudoku sud1("../sudoku_samples/sudoku1.txt");

  Cronometro<std::milli> crono;

  crono.inicio();

  // if(sud1.resolver(csp::Seleccion_variable::mrv, csp::Algoritmo::bt))
  if(sud1.resolver(csp::Seleccion_variable::mrv, csp::Algoritmo::fc_ac1))
  // if(sud1.resolver(csp::Seleccion_variable::estatica,csp::Algoritmo::bt))
  {
    std::cout<<std::endl<<"Solution:"<<std::endl;
    sudoku::imprime_solucion(sud1.get_solucion());
    std::cout<<"\nVisited nodes= "<<sud1.get_nodos_expandidos()<<std::endl;
  }

  crono.fin();

  std::cout<<"Time spent: "<<crono<<" ms."<<std::endl;
  std::cout<<std::endl;

  return 0;
}
