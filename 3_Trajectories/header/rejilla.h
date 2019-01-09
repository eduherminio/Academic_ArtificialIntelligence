#ifndef REJILLA_H_INCLUDED
#define REJILLA_H_INCLUDED

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <random>
#include "casilla.h"
#include <vector>
class Rejilla : public sf::Drawable
{
  unsigned filas,columnas;
  unsigned tam_casilla;
  unsigned ancho, alto;
  std::vector<Casilla> casillas;

  inline int indice_casilla(sf::Vector2f posicion) const;
  void borra_rejilla();

public:
  Rejilla(unsigned filas,unsigned columnas,unsigned tam_casilla);
  Rejilla();
  Rejilla(const Rejilla& rejilla);
  Rejilla& operator=(const Rejilla& other);

  std::pair<unsigned,unsigned> pos_casilla_inicial() const;
  std::pair<unsigned,unsigned> pos_casilla_final() const;
  std::vector<std::pair<unsigned,unsigned>> pos_muros() const;
  const Casilla& get_casilla_inicial() const;
  const Casilla& get_casilla_final() const;
  Tipo_casilla get_tipo_casilla(sf::Vector2f posicion) const;
  void set_tipo_casilla(sf::Vector2f posicion, Tipo_casilla tipo_casilla);

  bool es_muro(sf::Vector2f posicion) const;
  bool es_fuera_limites(sf::Vector2f posicion) const;

  void borra_trayectoria();

  void crea_rejilla_aleatorio();
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif // REJILLA_H_INCLUDED
