#ifndef REJILLA_H
#define REJILLA_H

#include "casilla.h"

class Rejilla : public sf::Drawable
{
public:

  Rejilla() = default;
  void set_rejilla(unsigned f,unsigned c,unsigned dim_cas,unsigned hueco_entre_casillas,unsigned hueco_al_borde,const Textura& textura);
  // Traduce de coordenadas pixel del rat�n a coordenadas filas,columnas del tablero
  // Devuelve 0 si las coordenasdas estan fuera de la rejilla
  bool get_fila_columna(unsigned x_pos,unsigned y_pos, unsigned &fila,unsigned &columna) const;

  Tipo_casilla get_tipo_casilla(sf::Vector2f posicion) const;
  void set_tipo_casilla(sf::Vector2i posicion, Tipo_casilla tipo_casilla,const Textura textura);
  void set_tipo_casilla(unsigned fil,unsigned col, Tipo_casilla tipo_casilla,const Textura& textura);
  bool es_fuera_limites(sf::Vector2f posicion) const;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  bool indice_casilla(sf::Vector2i posicion,unsigned &fil,unsigned &col) const;
private:
  unsigned get_ancho() const
  {
    return tam_casilla * columnas;
  }
  unsigned get_alto() const
  {
    return tam_casilla * filas;
  }
  unsigned get_tam_casilla() const
  {
    return tam_casilla;
  }
  // Pinta la casilla en la ventana con color
  void borra_rejilla(const Textura& textura);

  std::vector<Casilla> casillas;

  unsigned filas,columnas;
  unsigned tam_casilla;
  //   unsigned hueco_entre_casillas;
  //   unsigned hueco_al_borde;
};

#endif
