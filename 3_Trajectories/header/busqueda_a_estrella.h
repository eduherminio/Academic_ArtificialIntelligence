#include <unordered_map>
#include <queue>
namespace problema_busqueda
{
  template <typename T>
  bool Problema_busqueda<T>::a_estrella()
  {
    struct Nodo_prioridad {
      size_t indice_en_lista;
      decltype(nodo_inicial.tipo_dato_coste()) coste_estimado;
      bool operator <(const Nodo_prioridad &nodo) const
      {
        return nodo.coste_estimado<coste_estimado;
      }
    };
    struct Nodo {
      T nodo;
      size_t padre;
      decltype(nodo_inicial.tipo_dato_coste()) coste_actual;
      bool visitado= false;   // extra var
    };

    solucion.clear();
    // Contenedores
    std::priority_queue<Nodo_prioridad> lista_prioridad;
    std::vector<Nodo> lista; //{nodo,padre,coste_actual}

    //std::unordered_map<decltype(nodo_inicial.get_clave()),decltype(nodo_inicial.tipo_dato_coste())>claves;    // Si guardáramos el coste del nodo en vez de su posición en la lista
    std::unordered_map<decltype(nodo_inicial.get_clave()), size_t> claves; //{clave, puesto}

    lista.push_back({nodo_inicial,0,0});
    claves[nodo_inicial.get_clave()]=0;

    lista_prioridad.push({0,heuristica(nodo_inicial,nodo_objetivo)});

    bool exito=false;
    nodos_expandidos=0;
    size_t iter_lista=0;

    while(exito==false && !lista_prioridad.empty())
    {
      iter_lista=  lista_prioridad.top().indice_en_lista;
      lista_prioridad.pop();

      exito= lista[iter_lista].nodo== nodo_objetivo;

      if(exito== false)
      {
        if(lista[iter_lista].visitado== false)  {     // No contamos las re-expansiones
          lista[iter_lista].visitado= true;
          ++nodos_expandidos;
        }

        auto v_hijos= lista[iter_lista].nodo.expandir();

        for(auto & hijo:v_hijos)
        {
          auto clave_hijo=hijo.get_clave();

        // Comprobamos si el coste de un nodo repetido es menor que el original, y sie s así sustituimos ese coste en el nodo de la lsita y actualizamos la lista de propridad
          typename std::unordered_map <decltype(nodo_inicial.get_clave()), size_t>::iterator it= claves.find (clave_hijo);

          if(it==claves.end())  {  // No repetido
            Nodo newNodo {
              hijo,
              iter_lista,
              lista[iter_lista].coste_actual + coste_operador(hijo, nodo_objetivo),
              false
            };
            lista.push_back(newNodo); // Queda en la pos lista.size()-1

            Nodo_prioridad newNodo_prioridad {
              lista.size()-1,
              newNodo.coste_actual + heuristica(hijo, nodo_objetivo)
            };
            lista_prioridad.push(newNodo_prioridad);

            claves[clave_hijo]= lista.size()-1;

          }
          else if (lista[it->second].coste_actual > (lista[iter_lista].coste_actual + coste_operador(hijo, nodo_objetivo)) ) {    // Repetido, pero el nuevo con menor coste
            // TO-DO: Add a new nodo, not change the existing one
            lista[it->second].padre= iter_lista;
            lista[it->second].coste_actual= lista[iter_lista].coste_actual + coste_operador(hijo, nodo_objetivo);
            lista_prioridad.push({it->second, lista[it->second].coste_actual + heuristica(hijo, nodo_objetivo)}); // flotará automáticamente antes que su homólogo de mayor coste
          }
        }
      }
    }

    if(exito)
    {
      while(iter_lista!=0)
      {
        solucion.push_back(lista[iter_lista].nodo);
        iter_lista=lista[iter_lista].padre;
      }
      solucion.push_back(lista[iter_lista].nodo);
    }
    return exito;
  }
}
