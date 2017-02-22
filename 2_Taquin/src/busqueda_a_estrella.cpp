#include "../header/problema_busqueda_taquin.h"
#include <unordered_map>
#include <queue>
#include <iostream>

//
//   Unordered_map en vez de set:  guardo tanto la clave del nodo, como el indice de la posición en la lista del nodo.
//   para que, si encuentro un nodo repetido, evaluar si su coste es menor para añadirle en vez de directamente no hacerlo
//
//           *̣------------\               camino 2
//             \ 100       \ 75 -> sustituye al otro ya existente
// camino 1    \           \
//             *-----------\
//             |
//             |   100
//             1*

namespace taquin
{
  bool Problema_busqueda_taquin::a_estrella()
  {
      //
      // Una forma de tener ordenados los nodos de tal manera que el primero sea el de menor valores
      // se almacenan en std::priority_queue, que garantiza que el primer el elemento (y solo el primero) sea el de menor valor
      //   Ver PDF de montículo binario
      // Cuando tomo el primer valor que está en la cola de proridad, necesito saber el indice que tiene ese nodo en la cola real
      // El menor define el método de ordenador de los nodos de la cola de prioridad (porque podrían ordenarse por índice, etc.)
      //

    struct Nodo_prioridad {
      size_t indice_en_lista; // indice del nodo en vector<Nodo> lista
      size_t coste_estimado;
      bool operator <(const Nodo_prioridad &nodo) const     // el const no te deja modificar los miembros privados de la clase
      {
        return nodo.coste_estimado<coste_estimado;
      }
    };

    struct Nodo {
      Nodo_taquin nodo;
      size_t padre;
      size_t coste_actual;  // coste hasta el nodo actual
    };

    solucion.clear();
    // Contenerdores
    std::priority_queue<Nodo_prioridad> lista_prioridad;
    std::vector<Nodo> lista; // {nodo, padre, coste_actual}
    std::unordered_map<std::string,size_t>claves;

    //Inicializacion
    lista.push_back({nodo_inicial,0,0});
    claves[nodo_inicial.get_clave()]=0;
    lista_prioridad.push({0,heuristica(nodo_inicial,nodo_objetivo)}); // heuriscica nos da la heurística del num. mov. mínimo estimados (implemententado con la distancia de Manhattan)

    bool exito= false;
    nodos_expandidos= 0;
    size_t iter_lista;  // indice a expandir en vector<Nodo> lista

    while(exito==false && !lista_prioridad.empty())
    {
      ++nodos_expandidos;

      iter_lista=  lista_prioridad.top().indice_en_lista;
      lista_prioridad.pop();
      exito= lista[iter_lista].nodo== nodo_objetivo;

      if(exito== false)
      {
        auto v_hijos= lista[iter_lista].nodo.expandir();

        for(auto & hijo:v_hijos)
        {
          auto clave_hijo=hijo.get_clave();
          if(claves.count(clave_hijo)==0) // No está -> añado //TO-CHECK
          {
            Nodo newNodo {
              hijo,
              iter_lista,
              lista[iter_lista].coste_actual + coste_operador(hijo, nodo_objetivo)
            };
            lista.push_back(newNodo); // Queda en la pos lista.size()-1

            Nodo_prioridad newNodo_prioridad {
              lista.size()-1,
              newNodo.coste_actual + heuristica(hijo, nodo_objetivo)
            };
            lista_prioridad.push(newNodo_prioridad);

            claves[clave_hijo]= lista.size()-1;

            auto coste_heur= heuristica(hijo, nodo_objetivo);
            // std::cout<<"Coste heuristico: "<<coste_heur<<std::endl;
            // std::cout<<"Coste actual: "<<newNodo.coste_actual<<std::endl;
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
} // end of namespace taquin
