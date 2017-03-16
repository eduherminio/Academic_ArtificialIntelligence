#include "header/grafo.h"
#include <iostream>

int main()
{
  grafo::Nodo_grafo nodo_inicial("S");
  std::cout<<"I work"<<std::endl;
  //Ejemplo para ver si se han introducido bien los nodos vecinos de S
  auto hijos=nodo_inicial.expandir();
  for(auto&x:hijos)
  std::cout<<x.get_nombre()<<"\n";

  return 0;
}
