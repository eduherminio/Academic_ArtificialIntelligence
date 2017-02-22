#include "../header/problema_busqueda_taquin.h"
#include <unordered_set>
#include <queue>
#include <iostream>

namespace taquin
{
  bool Problema_busqueda_taquin::profundidad(size_t limite)
  {
    solucion.clear();
    struct Nodo
    {
      Nodo_taquin nodo;
      size_t padre;
      size_t profundidad;
    };
    std::vector<Nodo> lista; //{nodo,padre,profundidad}
    std::unordered_set<std::string>claves;
    lista.push_back({nodo_inicial,0,0});


    size_t indice=0;
    bool exito=false;
    nodos_expandidos=0;
    while(exito==false && lista.size()>0)
    {
      auto clave=lista[indice].nodo.get_clave();
      if(claves.count(clave)==0 && lista[indice].profundidad<=limite)
      {
        //    std::cout<<claves.bucket_count()<<"\n"; //Evolucion del tamanho de la tabla hash
        claves.insert(clave);
        ++nodos_expandidos;

        exito=(lista[indice].nodo==nodo_objetivo); //Prueba de meta

        if(exito==false)
        {
          auto hijos=lista[indice].nodo.expandir();

          for(auto& x:hijos)
          {
            auto clave_hijo=x.get_clave();
            if(claves.count(clave_hijo)==0)
            {
              lista.push_back({x,indice,lista[indice].profundidad+1});
            }
          }
        }
      }
      else    // Tengo que borrar el nodo de la tabla hash al elimintar el nodo, tras eliminarle de la lista, para que si se encuentra con él pueda volver a expandirle si procede
      {
        claves.erase(clave);
        lista.pop_back();
      }
      indice=lista.size()-1;
    }
    solucion.clear();
    if(exito)
    {
      while(indice!=0)
      {
        solucion.push_back(lista[indice].nodo);
        indice=lista[indice].padre;
      }
      solucion.push_back(lista[indice].nodo);
    }
    return exito;
  }
}
