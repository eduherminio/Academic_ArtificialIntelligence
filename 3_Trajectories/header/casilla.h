#ifndef CASILLA_H_INCLUDED
#define CASILLA_H_INCLUDED

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

enum class Tipo_casilla {inicio,fin,trayectoria,vacia,muro};

class Casilla: public sf::Drawable, public sf::Transformable
{
  sf::RectangleShape rect;
  Tipo_casilla tipo_casilla;

  static sf::Color color_casilla(Tipo_casilla) ;
public:
  explicit Casilla(sf::Rect<unsigned> rect,Tipo_casilla tipo_casilla=Tipo_casilla::vacia); //Por defecto, vacia
  Casilla();

  void set_tipo(Tipo_casilla);

  Tipo_casilla get_tipo() const;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif // CASILLA_H_INCLUDED
