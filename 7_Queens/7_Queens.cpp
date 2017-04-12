#include "header/nodo_reinas.h"
#include "header/problema_csp.h"
#include <iostream>

int main()
{
  const unsigned dimension= 8;
  const size_t iteraciones_max= 1000;
  //Opciones de tipo de Nodo
  //Nodo sin set
  nodo_reinas::Nodo_reinas nodo_inicial(dimension, {}); //Vector vacio inicial
  //Nodo con set
  nodo_reinas::Nodo_reinas_set nodo_inicial_set(dimension, {}); //Vector vacio inicial

  problema_csp::Problema_csp<nodo_reinas::Nodo_reinas>      problema(nodo_inicial);
  problema_csp::Problema_csp<nodo_reinas::Nodo_reinas_set>  problema_set(nodo_inicial_set);


  size_t iteraciones;

  //PROFUNDIDAD SIN SET
  if(problema.profundidad())
  {
    std::cout<<"\nPROFUNDIDAD SIN SET\n";
    nodo_reinas::imprime_posicion(problema.get_solucion(), problema.get_nodos_expandidos());
  }

  //PROFUNDIDAD CON SET
  if(problema_set.profundidad())
  {
    std::cout<<"\nPROFUNDIDAD CON SET\n";
    nodo_reinas::imprime_posicion(problema_set.get_solucion(), problema.get_nodos_expandidos());
  }

  iteraciones=iteraciones_max;

  //LAS_VEGAS_EXPANDIR SIN SET
  if(problema.las_vegas_expandir(iteraciones))
  {
    std::cout<<"\nLAS_VEGAS_EXPANDIR SIN SET\n";
    nodo_reinas::imprime_posicion(problema.get_solucion(), problema.get_nodos_expandidos());
  }
  std::cout<<"Numero de iteraciones: "<<iteraciones<<std::endl;

  //LAS_VEGAS_EXPANDIR CON SET
  iteraciones=iteraciones_max;
  if(problema_set.las_vegas_expandir(iteraciones))
  {
    std::cout<<"\nLAS_VEGAS_EXPANDIR CON SET\n";
    nodo_reinas::imprime_posicion(problema_set.get_solucion(), problema.get_nodos_expandidos());
  }
  std::cout<<"Numero de iteraciones: "<<iteraciones<<std::endl;

  //LAS_VEGAS_SUCESOR_ALEATORIO SIN SET
  iteraciones=iteraciones_max;
  if(problema.las_vegas_sucesor_aleatorio(iteraciones))
  {
    std::cout<<"\nLAS VEGAS SUCESOR ALEATORIO SIN SET\n";
    nodo_reinas::imprime_posicion(problema.get_solucion(), problema.get_nodos_expandidos());
  }
  std::cout<<"Numero de iteraciones: "<<iteraciones<<std::endl;

  //LAS_VEGAS_SUCESOR_ALEATORIO CON SET
  iteraciones=iteraciones_max;
  if(problema_set.las_vegas_sucesor_aleatorio(iteraciones))
  {
    std::cout<<"\nLAS VEGAS SUCESOR ALEATORIO CON SET\n";
    nodo_reinas::imprime_posicion(problema_set.get_solucion(), problema.get_nodos_expandidos());
  }
  std::cout<<"Numero de iteraciones: "<<iteraciones<<std::endl;
  return 0;
}
