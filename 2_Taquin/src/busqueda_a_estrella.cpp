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
//
// Para sustituirlos, el método que se ha utilizado es:
// - re-escribir los campos padre y coste_actual del Nodo originalmente almacenado en la lista.
// Introducir un nuevo Nodo_prioridad en lista_prioridad, que anulará al antiguo por tener menos coste_estimado

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
      bool visitado=false;
    };

    solucion.clear();
    // Contenedores
    std::priority_queue<Nodo_prioridad> lista_prioridad;
    std::vector<Nodo> lista; // {nodo, padre, coste_actual}
    std::unordered_map<std::string,size_t>claves; //{clave, puesto}

    //Inicializacion
    lista.push_back({nodo_inicial,0,0});
    claves[nodo_inicial.get_clave()]=0;
    lista_prioridad.push({0,heuristica(nodo_inicial,nodo_objetivo)}); // heuriscica nos da la heurística del num. mov. mínimo estimados (implemententado con la distancia de Manhattan)

    bool exito= false;
    nodos_expandidos= 0;
    size_t iter_lista=0;  // indice a expandir en vector<Nodo> lista

    // auto var_heuristica= 99999;
    while(exito==false && !lista_prioridad.empty())
    {
      iter_lista=  lista_prioridad.top().indice_en_lista;
      lista_prioridad.pop();

      exito= lista[iter_lista].nodo== nodo_objetivo;

    //   // Useful for checking if the solution
    //   if(heuristica(lista[iter_lista].nodo, nodo_objetivo) < var_heuristica)  {
    //     var_heuristica= heuristica(lista[iter_lista].nodo, nodo_objetivo);
    //     std::cout<<"Heur: "<< var_heuristica<<std::endl;
    // }

      if(exito== false)
      {
        if(lista[iter_lista].visitado== false)  {     // No contamos las re-expansiones
          lista[iter_lista].visitado= true;
          ++nodos_expandidos;
        }
        // else  { // needs making Nodo_taquin private members public.
        //   // for(uint8_t i=0; i< lista[iter_lista].nodo.posicion.size(); i++)
        //   // {
        //   //   std::cout<<static_cast<unsigned>(lista[iter_lista].nodo.posicion[i])<<" ";
        //   // }
        //   // std::cout<<std::endl;
        //   std::cout<<"****Sustitucion de nodo repetido*****"<<std::endl;
        // }

        auto v_hijos= lista[iter_lista].nodo.expandir();

        for(auto & hijo:v_hijos)
        {
          auto clave_hijo=hijo.get_clave();

        // No comprueba si el coste de un nodo repetido es menor que el ya existente, lo descarta directamente
          // if(claves.count(clave_hijo)==0)
          // {
          //   Nodo newNodo {
          //     hijo,
          //     iter_lista,
          //     lista[iter_lista].coste_actual + coste_operador(hijo, nodo_objetivo)
          //   };
          //   lista.push_back(newNodo); // Queda en la pos lista.size()-1
          //
          //   Nodo_prioridad newNodo_prioridad {
          //     lista.size()-1,
          //     newNodo.coste_actual + heuristica(hijo, nodo_objetivo)
          //   };
          //   lista_prioridad.push(newNodo_prioridad);
          //
          //   claves[clave_hijo]= lista.size()-1;
          // }

        // Comprobamos si el coste de un nodo repetido es menor que el original, y sie s así sustituimos ese coste en el nodo de la lsita y actualizamos la lista de propridad
          std::unordered_map<std::string,size_t>::iterator it= claves.find (clave_hijo);

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

            // std::cout<<lista[it->second].coste_actual<<" "<<lista[iter_lista].coste_actual + coste_operador(hijo, nodo_objetivo)<<std::endl;

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
} // end of namespace taquin
