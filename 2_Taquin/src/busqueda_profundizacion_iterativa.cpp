#include "../header/problema_busqueda_taquin.h"
#include <iostream>

namespace taquin
{
  bool Problema_busqueda_taquin::profundizacion_iterativa(size_t limite)
  {
    size_t contador_nodos=0;
    for(size_t i=0; i!=limite; ++i)
    {
      std::cout<<"Profundidad actual: "<<i<<"\n";
      auto salida=profundidad(i);
      contador_nodos+=nodos_expandidos;
      if(salida)
      {
        nodos_expandidos=contador_nodos;
        return true;
      }
    }
    return false;
  }
}
