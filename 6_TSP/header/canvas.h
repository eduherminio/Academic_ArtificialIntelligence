#ifndef VISUALIZACION_H
#define VISUALIZACION_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Canvas:public sf::Drawable
{
public:
  Canvas()
  {

  }

  void inicializa(unsigned o_x,unsigned o_y,unsigned anc,unsigned alt)
  {
    offset_x=o_x;
    offset_y=o_y;
    ancho=anc;
    alto=alt;

    marco=sf::RectangleShape(sf::Vector2f(ancho-4,alto-4));
    marco.setPosition(sf::Vector2f(2,2));
    marco.setOutlineThickness(2);
    marco.setOutlineColor(sf::Color(0,0,255));
  }
  void set_coordenadas(std::vector<std::pair<unsigned,unsigned>> const & coor)
  {
    coordenadas=std::vector<std::pair<unsigned,unsigned>>(coor);
    set_puntos();
  }
  void set_recorrido(std::vector<unsigned> const &ind);
  void set_recorrido_optimo(std::vector<unsigned> const &ind)
  {
    set_recorrido(ind);
    recorrido_optimo=recorrido;
  }
  void set_puntos();

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
  unsigned offset_x,offset_y;
  unsigned ancho,alto;
  std::vector<std::pair<unsigned,unsigned>> coordenadas; //Coordenadas de las ciudades normalizadas a las dimensiones del CANVAS
  std::vector<sf::CircleShape> puntos;
  sf::RectangleShape marco;
  sf::VertexArray recorrido;
  sf::VertexArray recorrido_optimo;

};

#endif  // VISUALIZACION_H
