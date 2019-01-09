#ifndef POSICION_REVERSI_H_INCLUDED
#define POSICION_REVERSI_H_INCLUDED

#include "enumeraciones.h"
#include <vector>
#include <cassert>

struct Jugada
{
  unsigned x;
  unsigned y;
  std::vector<unsigned>dir;
};
class Posicion_reversi
{
public:
  Posicion_reversi(const unsigned filas,const unsigned columnas) //Crea una posicion vacia
  {                                                              //Se usa al inicio de la aplicacion
    // Debug error checking
    assert((filas> 3) && (columnas > 3));
    assert(!tablero.size()); //No podemos crear un tablero vacio si ya lo hemos creado previamente

    for(unsigned i=0; i<filas; i++)
    tablero.push_back(std::vector<Turno>(columnas));
    turno=Turno::humano;
    tipo_tablero=Tipo_tablero::no_pasa;
  }
  Posicion_reversi()
  {
  }
  int evalua_posicion(const bool es_terminal) const;
  Turno get_tablero(const unsigned x,const unsigned y) const
  {
    return(tablero[x][y]);
  }
  std::vector<std::vector<Turno>> get_tablero() const
  {
    return(tablero);
  }
  void set_tablero(const unsigned x,const unsigned y,const Turno turno)
  {
    tablero[x][y]=turno;
  }
  void set_tablero(const std::vector<std::vector<Turno>> &tab)
  {
    tablero=tab;
  }
  void set_turno(const Turno valor)
  {
    turno=valor;
  }
  Turno get_turno() const
  {
    return(turno);
  }
  Turno get_turno_contrario() const
  {
    if(turno==Turno::humano)
    return(Turno::ordenador);
    else
    return(Turno::humano);
  }
  unsigned get_filas() const
  {
    return(tablero.size());
  }
  Tipo_tablero get_pasa() const
  {
    return(tipo_tablero);
  }
  void set_pasa(const Tipo_tablero valor)
  {
    tipo_tablero=valor;
  }
  unsigned get_columnas() const
  {
    return(tablero[0].size());
  }
  void actualiza_tablero(const struct Jugada jugada);
  std::vector<Jugada> calcula_jugadas() const;
  void inicializar(const unsigned filas,const unsigned columnas)
  {
    for(unsigned i=0; i<filas; i++)
    tablero.push_back(std::vector<Turno>(columnas));
  }
  void imprime_tablero();
private:
  std::vector<std::vector<Turno>>tablero;
  Turno turno;
  Tipo_tablero tipo_tablero;
  static const int despl[8][2];

  //  6 7 8
  //  4 X 5
  //  1 2 3

};

#endif // POSICION_REVERSI_INCLUDED
