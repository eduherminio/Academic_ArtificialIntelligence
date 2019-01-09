// Unsolved problem:
// AL hacer pop_back(), el nodo se borra y no hay manera de marcarlo como visitado para que no se vuelva a visitar

#include "../include/taquin.h"
#include <iostream>

namespace taquin
{

  void copia_posicion(const unsigned origen[],unsigned destino[]) {
    for(auto i=0; i<9; ++i)
      destino[i]=origen[i];
  }

  void Taquin::set_objetivo(const unsigned v[]) {
    copia_posicion(v,posicion_objetivo);
  }

  void Taquin::set_inicial(const unsigned v[])  {
    copia_posicion(v,posicion_inicial);
  }

  bool Taquin::prueba_meta(const unsigned v1[],const unsigned v2[]) {
    size_t i=0;

    while(i<9)
    {
      if(v1[i]!=v2[i])
      return false;
      ++i;
    }
    return true;
  }

  void Taquin::inicializar_lista()  {
    exito=false;
    struct Nodo_Taquin nodo_inicial;

    for(int i=0; i<9; ++i)
    {
        nodo_inicial.posicion[i]=posicion_inicial[i];
        if(posicion_inicial[i]==0)
            nodo_inicial.pos_cas_vac=i;
    }

    nodo_inicial.padre=-1;
    nodo_inicial.profundidad=0;
    nodo_inicial.visitado=false;  // true??

    lista.clear();                  //Borramos la lista de nodos
    lista.push_back(nodo_inicial);
  }


  void Taquin::expandir(const size_t indice)  {
    // Te dice qu� nodos son tus hijos
    static const unsigned matriz_expansion[9][5]= {{2,1,7,0,0},{3,0,2,8,0},{2,1,3,0,0},{3,2,4,8,0},{2,3,5,0,0},{3,4,6,8,0},{2,5,7,0,0},{3,0,6,8,0},{4,1,3,5,7}};
    // filas: numero de casilla
    // columnas: nodos hijo
    //  0 | 1 | 2
    //  7 | 8 | 3
    //  6 | 5 | 4
    //
    //
    struct Nodo_Taquin hijo;
    // Caracteristicas comunes a cualquier hijo que pueda existir:
    hijo.profundidad=lista[indice].profundidad+1;
    hijo.padre=indice;
    hijo.visitado=false; //Este campo no es necesario en la B�squeda en Amplitud

    auto num_hijos=matriz_expansion[lista[indice].pos_cas_vac][0];
    for(unsigned i=0; i<num_hijos; i++)
    {
      hijo.pos_cas_vac=matriz_expansion[lista[indice].pos_cas_vac][i+1];

      copia_posicion(lista[indice].posicion,hijo.posicion);

      hijo.posicion[lista[indice].pos_cas_vac]=lista[indice].posicion[hijo.pos_cas_vac];
      // Reemplaza el contenido de  # # posición del hijo correspondiente a la que su padre tenía vacía (casilla que se intercambia con el cero)
      //  con el contenido de       * * (casilla del padre donde pasará a estar el cero del hijo)
      // *8*| 0 | 2
      //  7 | 1 | 3
      //  6 | 5 | 4

      //  0 |#8#| 2
      //  7 | 1 | 3
      //  6 | 5 | 4

      hijo.posicion[hijo.pos_cas_vac]=0;

      if(!repetido(hijo,indice))
        lista.push_back(hijo);
    }
  }

  void Taquin::amplitud() {
    size_t indice=0;
    inicializar_lista();    // turns exito false

    while(exito==false && indice<lista.size())
    {
        exito=prueba_meta(lista[indice].posicion,posicion_objetivo);

        if(exito==false){
            expandir(indice);
            indice++;
        }
    }
    if(exito)
        indice_objetivo=indice;

  }

  bool Taquin::funcion(const size_t indice_lista, const size_t limite)  {
      // Te dice qu� nodos son tus hijos
      // static: se define sólo una vez
      static const unsigned matriz_expansion[9][5]= {{2,1,7,0,0},{3,0,2,8,0},{2,1,3,0,0},{3,2,4,8,0},{2,3,5,0,0},{3,4,6,8,0},{2,5,7,0,0},{3,0,6,8,0},{4,1,3,5,7}};

      struct Nodo_Taquin father= lista[indice_lista];

      exito=prueba_meta(father.posicion,posicion_objetivo);
      if(exito)
        return(true);
      std::cout<<"*********"<<indice_lista<<"********"<<std::endl;
      unsigned num_cuadrante=father.pos_cas_vac;
      auto num_hijos= matriz_expansion[num_cuadrante][0];

      // if(father.visitado()== true || num_hijos==0)  // En nuestro problema, siempre existirá un número de hijos
        if(repetido (father, indice_lista) == true || num_hijos==0 || indice_lista>limite )  {
          // lista[indice_lista].visitado= true;  // father.visitado= true, en la lista
          lista.pop_back();


          if(repetido (father, indice_lista) == true)
          std::cout<<"repetido"<<std::endl;
          if(num_hijos=0)
          std::cout<<"sin hijos"<<std::endl;
          if(indice_lista>limite)
          std::cout<<"max. prof"<<std::endl;


          funcion(indice_lista - 1, limite);
      }

      else
      {
        //        A
        //  /  /    \  \
        // B  C     D  F
        // |
        // E
        // |
        // A

        for(int col=1; col<5; col++)  // Va recorriendo AB, AC, AD y AF (máx. 4 hijos)
        {
          if(matriz_expansion[num_cuadrante][col] != 0)
          {
            // Sacable fuera del bucle, al ser comun a todos los hijos
            struct Nodo_Taquin hijo;
            hijo.pos_cas_vac= matriz_expansion[num_cuadrante][col];
            hijo.profundidad=father.profundidad+1;
            hijo.padre=indice_lista;
            // fin del Sacable

            // Intercambio de numeros en el fijo
            copia_posicion(father.posicion,hijo.posicion);
            hijo.posicion[num_cuadrante]= father.posicion[hijo.pos_cas_vac];
            hijo.posicion[hijo.pos_cas_vac]= 0;
            // fin del Intercambio

            if(!repetido(hijo,indice_lista))  {   // A B E ¿A?
              lista.push_back(hijo);
              funcion(indice_lista+1, limite);
            }
          }
        }
        std::cout<<"pop_back"<<std::endl;
        // matriz_expansion[num_cuadrante][0]=0;
        lista.pop_back();
        // [ABE] con E agotado -> [AB];
        // [AB] con B agotado -> [A]
        // funcion(indice_lista - 1)  sale al fin de la función, volviendo a la de nivel superior
    }

  }

  void Taquin::profundidad(size_t limite)  {
    // DONE
    size_t indice_lista=0;
    inicializar_lista();

    bool exito;
    exito= funcion(indice_lista, limite);
    if(!exito)
      std::cout<<"Imposible encontrar solucion"<<std::endl;
    else
      std::cout<<"Habemus solucion"<<std::endl;
  }

  bool Taquin::repetido(const Nodo_Taquin& nodo,size_t indice)  {
    //Estrategia buscar nodos repetidos en ancestros
    // TO-DO
    bool repe=false;  // En amplitud, no se repiten
    /*
    for(int i=0; i<indice; i++){
      for(int j=0; j<9; j++){
        if(nodo[j]!=lista[i].j])
          return false;
      }
    }
    return true;
    */

    return repe;
  }


  void Taquin::solucion() {
    unsigned i,j;
    if(exito==false)
    {
        std::cout<<"No se encontro solucion"<<std::endl;
    }
    else
    {

        unsigned num_posiciones=lista[indice_objetivo].profundidad+1;
        unsigned solucion[num_posiciones][9];
        int indice=indice_objetivo;  //indice tomar� el vaor -1


        for(i=num_posiciones; i--;) //Mucho cuidado con los unsigned cuando decrementamos
        {
            for(j=0; j<9; j++)
            {
                solucion[i][j]=lista[indice].posicion[j];
            }
            indice=lista[indice].padre;
        }
        for(i=0; i<num_posiciones; i++)
        {
            for(j=0; j<9; j++)
            {
                std::cout<<solucion[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
    }
  }
}
