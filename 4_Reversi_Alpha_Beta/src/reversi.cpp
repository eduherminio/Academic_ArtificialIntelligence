#include "../header/reversi.h"
#include <cstddef>
#include <iostream>

void Reversi::inicializar()
{
  for(unsigned i = 0; i < filas; i++)
  {
    for(unsigned j = 0; j < columnas; j++)
    {
      posicion.set_tablero(i,j,Turno::vacia);
    }
  }
  posicion.set_tablero((filas/2)-1,(columnas/2)-1,Turno::humano);
  posicion.set_tablero((filas/2),(columnas/2),Turno::humano);
  posicion.set_tablero((filas/2)-1,(columnas/2),Turno::ordenador);
  posicion.set_tablero((filas/2),(columnas/2)-1,Turno::ordenador);
  posicion.set_turno(Turno::humano);
  posicion.set_pasa(Tipo_tablero::no_pasa);
  jugadas_validas_humano=posicion.calcula_jugadas();
  heuristica=0;
  algoritmo=Algoritmo::minimax;
  // TO-CHECK
  profundidad_maxima=5;
}

void Reversi::ejecuta_movimiento(const unsigned fil,const unsigned col)
{
  auto jugadas_validas=posicion.calcula_jugadas();
  if(!jugadas_validas.empty())
  {
    if(turno_humano())
    {
      for(auto &jugada:jugadas_validas)
      {
        if(jugada.x==fil &&jugada.y==col) //La casilla (fil,col)es una de las jugadas validas
        {
          posicion.actualiza_tablero(jugada);
          posicion.set_turno(Turno::ordenador);
          posicion.set_pasa(Tipo_tablero::no_pasa);
        }
      }
    }
    else
    {
      for(auto &jugada:jugadas_validas)
      {
        if(jugada.x==fil &&jugada.y==col) //La casilla (fil,col)es una de las jugadas validas
        {
          posicion.actualiza_tablero(jugada);
          posicion.set_turno(Turno::humano);
          posicion.set_pasa(Tipo_tablero::no_pasa);
        }
      }
    }
  }
  else
  {
    if(posicion.get_pasa()==Tipo_tablero::no_pasa)
    {
      posicion.set_pasa(Tipo_tablero::pasa);
      if(turno_humano())
      posicion.set_turno(Turno::humano);
      else
      posicion.set_turno(Turno::ordenador);
    }
    else
    {
      posicion.set_pasa(Tipo_tablero::terminal);
    }
  }
}

void Reversi::ejecuta_movimiento()
{
  do
  {
    if(algoritmo==Algoritmo::minimax)
    {
      heuristica=estrategia_minimax();
    }
    else if(algoritmo==Algoritmo::alpha_beta)
    {
      heuristica=estrategia_alpha_beta();
    }
    posicion.set_turno(Turno::humano);
    jugadas_validas_humano=posicion.calcula_jugadas();
    if(!jugadas_validas_humano.size())                        //Tablero en pasa para humano
    {
      if(posicion.get_pasa()==Tipo_tablero::no_pasa)
      {
        posicion.set_pasa(Tipo_tablero::pasa);
        posicion.set_turno(Turno::ordenador);
      }
      else
      {
        posicion.set_pasa(Tipo_tablero::terminal);
      }
    }
  }
  while(turno_ordenador());
}

int Reversi::estrategia_alpha_beta()
{
  //TO-DO

  //A completar por el alumno

  //return(valor_alpha);  // sirve para visualizar en la consola
}

int Reversi::estrategia_minimax()
{
  std::vector<Nodo_reversi_minimax> lista;
  Nodo_reversi_minimax nodo_inicial(posicion);
  nodo_inicial.set_nodo_inicial();
  lista.push_back(nodo_inicial);
  auto valor_minimax=lista[0].get_minimax(); //valor final para MAX

  while(!lista.empty())
  {
    if(!lista.back().get_visitado())
    {
      lista.back().set_visitado();
      if(lista.back().get_pasa()==Tipo_tablero::terminal)  //Posici�n terminal: pasan los dos
      {
        lista.back().set_minimax(lista.back().evalua_posicion(true));
      }
      else if(lista.back().get_profundidad()==profundidad_maxima)  //Suspensi�n
      {
        lista.back().set_minimax(lista.back().evalua_posicion(false));
      }
      else
      {
        auto tam_lista=lista.size();
        auto minimax_actual=lista.back().get_minimax();
        for(auto &hijo:lista.back().expandir())
        {
          hijo.set_padre(tam_lista-1);
          hijo.set_minimax(-minimax_actual);
          lista.push_back(hijo);
        }
      }
    }
    else     // TO-CHECK: visitado?
    {
      //          actualiza minimax padre
      auto padre=lista.back().get_padre();
      if(padre>=0)
      {
        auto minimax_hijo=lista.back().get_minimax();
        auto minimax_padre=lista[padre].get_minimax();
        if(lista.back().get_turno()==Turno::ordenador) //El padre es humano: nodo MIN
        {
          if(minimax_hijo<minimax_padre)
          {
            lista[padre].set_minimax(minimax_hijo);
          }
        }
        else  //El padre es ordenador: nodo MAX
        {
          if(minimax_hijo>minimax_padre)
          {
            lista[padre].set_minimax(minimax_hijo);
            if(padre==0) //Mejoramos la puntuacion del nodo raiz
            {
              posicion.set_tablero(lista.back().get_tablero());
              posicion.set_pasa(lista.back().get_pasa());
              valor_minimax=minimax_hijo;
            }
          }
        }
      }
      lista.pop_back();  //Eliminamos el nodo actual
    }
  }
  return(valor_minimax);
}
