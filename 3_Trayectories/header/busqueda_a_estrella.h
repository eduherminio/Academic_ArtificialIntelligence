#include <unordered_map>
#include <queue>
namespace problema_busqueda
{
  template <typename T>
  bool Problema_busqueda<T>::a_estrella()
  {
    struct Nodo_prioridad
    {
      size_t indice;
      decltype(nodo_inicial.tipo_dato_coste()) coste_estimado;
      bool operator <(const Nodo_prioridad &nodo) const
      {
        return nodo.coste_estimado<coste_estimado;
      }
    };
    struct Nodo
    {
      T nodo;
      size_t padre;
      decltype(nodo_inicial.tipo_dato_coste()) coste_actual;
    };

    solucion.clear();
    std::priority_queue<Nodo_prioridad> lista_prioridad;
    std::vector<Nodo> lista; //{nodo,padre,coste_actual}
    lista.push_back({nodo_inicial,0,0});

    //En la tabla Hash guardamos el valor del coste actual del nodo
    std::unordered_map<decltype(nodo_inicial.get_clave()),decltype(nodo_inicial.tipo_dato_coste())>claves;
    claves[nodo_inicial.get_clave()]=0;
    lista_prioridad.push({0,heuristica(nodo_inicial,nodo_objetivo)});

    bool exito=false;
    nodos_expandidos=0;
    size_t indice;
    while(exito==false && !lista_prioridad.empty())
    {
      //A completar
    }

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
