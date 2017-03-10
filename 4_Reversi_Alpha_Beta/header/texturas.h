#ifndef TEXTURAS_H_INCLUDED
#define TEXTURAS_H_INCLUDED

#include <SFML/Graphics.hpp>

class Textura
{
public:
  Textura()
  {
    if(!tile1.loadFromFile("../imgs/tile1.jpg")
    || !tile2.loadFromFile("../imgs/tile2.jpg")
    || !piece1.loadFromFile("../imgs/piece1.png")
    || !piece2.loadFromFile("../imgs/piece2.png")
    || !glow.loadFromFile("../imgs/glow.png")
    || !wood.loadFromFile("../imgs/wood.jpg")
    || !button.loadFromFile("../imgs/button.png"))
    {
      exit(1);
    }
    piece1.setSmooth(true);
    piece2.setSmooth(true);
    glow.setSmooth(true);
  }

  const sf::Texture& get_textura_casilla(Tipo_casilla tipo_casilla) const
  {
    switch(tipo_casilla)
    {
      case Tipo_casilla::vacia_tono1:
      return(tile1);
      break;
      case Tipo_casilla::vacia_tono2:
      return(tile2);
      break;
      case Tipo_casilla::humano:
      return(piece1);
      break;
      case Tipo_casilla::ordenador:
      return(piece2);
      break;
      case Tipo_casilla::vacia_posible:
      return(glow);
      break;
      default:
      break;
    }
  }
  const sf::Texture& get_textura_panel() const
  {
    return wood;
  }
  const sf::Texture& get_textura_botones() const
  {
    return button;
  }
private:
  sf::Texture tile1;
  sf::Texture tile2;
  sf::Texture piece1;
  sf::Texture piece2;
  sf::Texture glow;
  sf::Texture wood;
  sf::Texture button;
};

#endif // TEXTURAS_H_INCLUDED
