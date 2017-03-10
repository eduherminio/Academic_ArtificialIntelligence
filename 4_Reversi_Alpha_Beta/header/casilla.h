#ifndef CASILLA_H_INCLUDED
#define CASILLA_H_INCLUDED

#include "enumeraciones.h"
#include "texturas.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Casilla: public sf::Drawable, public sf::Transformable
{
  sf::RectangleShape rect;
  sf::CircleShape circulo_grande;
  sf::CircleShape circulo_pequenho;
  Tipo_casilla tipo_casilla;
public:
  explicit Casilla(sf::Rect<unsigned> rect);
  Casilla();

  void set_tipo(Tipo_casilla,const Textura&);

  Tipo_casilla get_tipo() const;
  const sf::RectangleShape& get_rectangulo() const
  {
    return rect;
  }
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // CASILLA_H_INCLUDED
