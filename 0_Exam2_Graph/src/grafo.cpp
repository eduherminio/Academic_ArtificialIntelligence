#include "../header/grafo.h"

namespace grafo
{
  vector<Nodo> Inicializa_grafo() {
    vector<Nodo> lista_nodos;
    //Introduccion manual de los nodos
    string nombre;
    //Resto de declaraciones

    //Nodo S
    nombre="S";
    //Se "cargan" el resto de miembros del nodo
    //lista_nodos.push_back({nombre,//Resto de miembros del Nodo}); //Se almacena Nodo S
    ////////////////////////////////////

    return lista_nodos;
  }

  grafo::vector<Nodo> Nodo_grafo::lista_nodos=Inicializa_grafo();

  std::vector<Nodo_grafo> Nodo_grafo::expandir() const  {                     // To complete (choose 1)   -> CHOSEN
    std::vector<grafo::Nodo_grafo> v_hijos;
    for(auto& nodo:lista_nodos)
    {
      if(this->get_nombre()==nodo.nombre)
      {
        for(int i=0; i< nodo.hijos.size(); ++i)
        {
          auto hijo= lista_nodos.at(nodo.hijos.at(i));
          string nombre= hijo.nombre;

          // push_back el que coincida con el nombre del hijo
          for(auto& nodo2:lista_nodos)
          {
            if(nodo2.nombre== nombre)
            v_hijos.push_back({nodo2.nombre});
          }
        }
      }
    }
    return v_hijos;
  }

  double heuristica(const Nodo_grafo& nodo1, const Nodo_grafo& nodo2) {       // To complete (choose 1)
    //nodo2 en heuristica() no se utiliza pues se conoce de antemano
    //Se mantiene como argumento para que la interfaz sea id�ntica al resto de problemas de busqueda

  }

  double coste_operador(const Nodo_grafo& nodo1, const Nodo_grafo& nodo2) {   // To complete (choose 1)
    //

  }

}
