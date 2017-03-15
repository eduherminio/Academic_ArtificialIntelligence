#ifndef NODO_REVERSI_H_INCLUDED
#define NODO_REVERSI_H_INCLUDED

#include "posicion_reversi.h"

template<class Nodo>
class Nodo_reversi
{
public:
  Nodo_reversi(const Posicion_reversi &pos):posicion(pos)
  {
  }
  Turno get_turno() const
  {
    return(posicion.get_turno());
  }
  bool get_visitado() const
  {
    return visitado;
  }
  void set_visitado()
  {
    visitado=true;
  }
  unsigned get_profundidad() const
  {
    return profundidad;
  }
  int evalua_posicion(const bool es_terminal) const
  {
    return(posicion.evalua_posicion(es_terminal));
  }
  std::vector<std::vector<Turno>> get_tablero() const
  {
    return(posicion.get_tablero());
  }
  int get_padre() const
  {
    return(padre);
  }
  void set_padre(const int valor)
  {
    padre=valor;
  }
  Tipo_tablero get_pasa() const
  {
    return(posicion.get_pasa());
  }
  void set_pasa(const Tipo_tablero valor)
  {
    posicion.set_pasa(valor);
  }
  std::vector<Nodo> expandir() const;
  virtual void set_nodo_inicial()=0;
protected:
  Posicion_reversi posicion;
  bool visitado;
  unsigned profundidad;
  int padre;             //-1 el nodo raiz
};

class Nodo_reversi_minimax: public Nodo_reversi<Nodo_reversi_minimax>
{
public:
  Nodo_reversi_minimax(const Posicion_reversi &pos):Nodo_reversi(pos)
  {
  }
  void set_nodo_inicial();
  void set_minimax(const int valor)
  {
    minimax=valor;
  }
  int get_minimax() const
  {
    return(minimax);
  }
private:
  int minimax;
};

class Nodo_reversi_alpha_beta: public Nodo_reversi<Nodo_reversi_alpha_beta>
{
public:
  Nodo_reversi_alpha_beta(const Posicion_reversi &pos):Nodo_reversi(pos)
  {
  }
  void set_nodo_inicial();
  void set_alpha(const int valor)
  {
    alpha=valor;
  }
  void set_alpha_o_beta(const int valor)
  {
    if(get_turno()==Turno::humano)
    // if(get_turno()==Turno::ordenador)
    {
      alpha=valor;
    }
    else  {
      beta=valor;
    }
  }
  void set_beta(const int valor)
  {
    beta=valor;
  }
  int get_alpha() const
  {
    return(alpha);
  }
  int get_beta() const
  {
    return(beta);
  }
private:
  int alpha;
  int beta;
};

template<class Nodo>
std::vector<Nodo> Nodo_reversi<Nodo>::expandir() const
{
  std::vector<Nodo>lista_hijos;
  for(auto &jugada:posicion.calcula_jugadas())
  {
    Nodo hijo(posicion);          //Crea un hijo con la misma posici�n del padre
    hijo.posicion.actualiza_tablero(jugada);      //y actualiza el tablero con la jugada
    hijo.set_pasa(Tipo_tablero::no_pasa);
    hijo.visitado=false;
    hijo.posicion.set_turno(posicion.get_turno_contrario());
    hijo.profundidad=profundidad+1;
    lista_hijos.push_back(hijo);
  }
  if(!lista_hijos.size())
  {
    Nodo hijo(posicion);              //Crea un hijo con la misma posici�n del padre
    hijo.visitado=false;
    hijo.posicion.set_turno(posicion.get_turno_contrario());
    hijo.profundidad=profundidad+1;
    if(posicion.get_pasa()==Tipo_tablero::no_pasa)    //Tablero en pasa
    {
      hijo.set_pasa(Tipo_tablero::pasa);
    }
    else
    {
      hijo.set_pasa(Tipo_tablero::terminal);  //Posicion terminal
    }
    lista_hijos.push_back(hijo);
  }
  return lista_hijos;
}

#endif // NODO_REVERSI_H_INCLUDED
