#include <unordered_set>

namespace problema_busqueda
{
  template<typename T>

  bool Problema_busqueda<T>::profundidad(size_t limite)
  {
    solucion.clear();
    struct Nodo
    {
      T nodo;
      size_t padre;
      size_t profundidad;
      bool visitado;
    };
    std::vector<Nodo> lista; //{nodo,padre,profundidad}
    std::unordered_set<decltype(lista[0].nodo.get_clave())> claves;

    lista.push_back({nodo_inicial,0,0,false});
    claves.insert(nodo_inicial.get_clave());

    size_t indice=0;
    bool exito=false;
    nodos_expandidos=0;

    while(exito==false && lista.size()>0)
    {
      // if(claves.count(clave)==0 && lista[indice].profundidad<=limite)
      if(!lista[indice].visitado && lista[indice].profundidad<=limite)
      {
        lista[indice].visitado=true;
        // std::cout<<claves.bucket_count()<<"\n"; //Evolucion del tamanho de la tabla hash
        // claves.insert(clave);
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
              lista.push_back({x,indice,lista[indice].profundidad+1, false});
              claves.insert(clave_hijo);
            }
          }
        }
      }
      else
      {
        claves.erase(lista[indice].nodo.get_clave());
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
