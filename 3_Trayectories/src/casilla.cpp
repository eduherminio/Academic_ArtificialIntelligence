#include "../header/casilla.h"

Casilla::Casilla() = default;

Casilla::Casilla(sf::Rect<unsigned> r, Tipo_casilla tipo_casilla) :
rect(sf::Vector2f(r.width,r.height)), tipo_casilla(tipo_casilla)
{
  rect.setFillColor(color_casilla(tipo_casilla));
  setPosition(r.left, r.top);

  //Fijamos color y ancho bordes casilla
  rect.setOutlineColor(sf::Color(0,0,0));
  rect.setOutlineThickness(1.f);
}

void Casilla::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(rect,states);
}

void Casilla::set_tipo(Tipo_casilla tipo_casilla)
{
  this->tipo_casilla = tipo_casilla;
  rect.setFillColor(color_casilla(tipo_casilla));
}

Tipo_casilla Casilla::get_tipo() const
{
  return tipo_casilla;
}

sf::Color Casilla::color_casilla(Tipo_casilla tipo_casilla)
{
  switch(tipo_casilla)
  {
    case Tipo_casilla::vacia:
    return sf::Color::White;
    case Tipo_casilla::trayectoria:
    return sf::Color(0,76,132); //Azul
    case Tipo_casilla::inicio:
    return sf::Color(200, 50, 50); //Rojo
    case Tipo_casilla::fin:
    return sf::Color(250, 150, 100); //Naranja
    default:
    return sf::Color::Black;
  }
}
