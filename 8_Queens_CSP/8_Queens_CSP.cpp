#include "header/reinas.h"
#include "header/problema_csp.h"
#include "header/cronometro.h"
int main()
{
  reinas::Reinas reinas(20);
  Cronometro<std::milli> crono;

  crono.inicio();
  if(reinas.resolver(csp::Seleccion_variable::aleatoria, csp::Algoritmo::bt))
  // if(reinas.resolver(csp::Seleccion_variable::estatica, csp::Algoritmo::bt))
  // if(reinas.resolver(csp::Seleccion_variable::estatica, csp::Algoritmo::fc)) // or if(reinas.resolver()) // due to default parameters of bool resolver()
  {
    std::cout<<"SOLUCION"<<std::endl;
    reinas::imprime_solucion(reinas.get_solucion());
    std::cout<<"\nNODOS VISITADOS= "<<reinas.get_nodos_expandidos()<<std::endl;
  }
  crono.fin();
  std::cout<<"Tiempo empleado: "<<crono<<" ms."<<std::endl;
  std::cout<<std::endl;

  return 0;
}
