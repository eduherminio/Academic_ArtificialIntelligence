#ifndef PANEL_H_INCLUDED
#define PANEL_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Panel:public sf::Drawable
{
public:
  Panel()
  {
  }
  void inicializa(unsigned ancho,unsigned alto,unsigned ancho_panel);
  void set_textura_panel(const sf::Texture& textura)
  {
    //fondo_panel.setTexture(&textura);
  }

  void set_textura_botones(const sf::Texture& textura)
  {
    boton_ordenador.setTexture(&textura);
    boton_manual.setTexture(&textura);
  }
  void set_string_turno(const std::string& texto);
  void set_string_final(const std::string& texto);
  void set_string_puntuacion(const std::string& texto);
  void color_string_turno_blanco();
  void color_string_turno_negro();
  bool boton_ordenador_pulsado(sf::Vector2i posicion) const;
  bool boton_manual_pulsado(sf::Vector2i posicion) const;
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
  sf::RectangleShape fondo_puntuacion;
  sf::RectangleShape boton_ordenador;
  sf::RectangleShape boton_manual;
  sf::RectangleShape fondo_panel;

  sf::Text texto_turno;
  sf::Text texto_final;
  sf::Text texto_puntuacion;
  sf::Text texto_etiqueta_turno;
  sf::Text texto_etiqueta_puntuacion;
  sf::Text texto_boton_ordenador;
  sf::Text texto_boton_manual;
  sf::Font font;
};

#endif // PANEL_H_INCLUDED
