#include "../header/vista.h"
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>

namespace parche
{
  template <typename T> std::string to_string(const T& n)
  {
    std::ostringstream stm;
    stm<<n;
    return stm.str();
  }
}
void delay(int seconds)
{
  clock_t temp;
  temp = clock () + seconds * CLOCKS_PER_SEC;
  while (clock() < temp) {}
}

static inline std::string int2Str(int x)
{
  std::stringstream type;
  type << x;
  return type.str();
}

void Vista::set_texto_puntuacion(unsigned blancas,unsigned negras)
{
  panel.set_string_puntuacion("White:   "+int2Str(negras)+"\nBlack:    "+int2Str(blancas));
}
void Vista::set_texto_turno(const std::string& texto)
{
  panel.set_string_turno(texto);
  panel.color_string_turno_blanco();
}
void Vista::ejecutar()
{
  panel.inicializa(ancho,alto,ancho_panel);
  panel.set_textura_panel(textura.get_textura_panel());
  panel.set_textura_botones(textura.get_textura_botones());

  render_window.create(sf::VideoMode(ancho,alto), "Reversi");
  render_window.setFramerateLimit(30);

  render();
  while(render_window.isOpen())
  {
    procesa_eventos();
  }
}

void Vista::procesa_eventos()
{
  sf::Event event;

  while(render_window.pollEvent(event))
  {
    switch(event.type)
    {
      case sf::Event::Closed:
      render_window.close();
      break;
      case sf::Event::MouseButtonPressed:
      if (event.mouseButton.button == sf::Mouse::Left)
      {
        procesa_eventos_raton();
      }
      break;
      default:
      break;
    }
  }
}
void Vista::procesa_eventos_raton()
{
  auto posicion = sf::Mouse::getPosition(render_window);
  if(jugando_humano && rejilla.indice_casilla(posicion,fila_pulsada,columna_pulsada))
  {
    observador.notifica(Evento_vista::casilla);
  }
  else if(panel.boton_ordenador_pulsado(posicion))
  {
    jugando_humano=true;
    observador.notifica(Evento_vista::ordenador);
    panel.set_string_final("");
    render();

  }
  else if(panel.boton_manual_pulsado(posicion))
  {
    jugando_humano=true;
    observador.notifica(Evento_vista::manual);
    panel.set_string_final("");
    render();
  }
}

void Vista::fin_juego(const std::string& texto)
{
  panel.set_string_final(texto);
  panel.set_string_turno("");
  jugando_humano=false;
}
void Vista::render()
{
  render_window.clear();
  render_window.draw(rejilla);
  render_window.draw(panel);
  render_window.display();
}
