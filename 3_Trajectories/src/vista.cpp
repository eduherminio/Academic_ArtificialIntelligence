#include "../header/vista.h"
#include <iostream>
#include <sstream>
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

Vista::Vista(unsigned filas,unsigned columnas,unsigned tam_casilla):filas(filas),columnas(columnas),tam_casilla(tam_casilla),
rejilla(Rejilla(filas,columnas,tam_casilla)),
desplazamiento_diagonal_habilitado(false), existe_casilla_inicial(true), existe_casilla_final(true)
{

}

void Vista::ejecutar()
{
  render_window.create(sf::VideoMode(columnas*tam_casilla,filas*tam_casilla),"Trajectory planification");

  carga_mensajes(filas*tam_casilla);
  while(render_window.isOpen())
  {
    procesa_eventos();
    render();
  }
}


void Vista::carga_mensajes(int alto)
{
  //Load font
  font.loadFromFile("../resources/sansation.ttf");

  const auto green = sf::Color(0, 140, 0);

  //set up texts
  texto_num_movimientos.setPosition(20.f, alto - 110.f);
  texto_num_movimientos.setScale(0.5f, 0.5f);
  texto_num_movimientos.setFont(font);
  texto_num_movimientos.setFillColor(green);

  texto_tiempo.setPosition(20.f, alto - 90.f);
  texto_tiempo.setScale(0.5f, 0.5f);
  texto_tiempo.setFont(font);
  texto_tiempo.setFillColor(green);

  texto_trayectoria_encontrada.setPosition(20.f, alto - 50.f);
  texto_trayectoria_encontrada.setScale(0.5f, 0.5f);
  texto_trayectoria_encontrada.setFont(font);
  texto_trayectoria_encontrada.setFillColor(green);

  noCasillaText.setPosition(20.f, alto - 30.f);
  noCasillaText.setScale(0.7f, 0.7f);
  noCasillaText.setFont(font);
  noCasillaText.setFillColor(sf::Color::Red);
}

std::pair<unsigned,unsigned> Vista::pos_casilla_inicial()
{
  return(rejilla.pos_casilla_inicial());
}
std::pair<unsigned,unsigned> Vista::pos_casilla_final()
{
  return(rejilla.pos_casilla_final());
}
std::vector<std::pair<unsigned,unsigned>> Vista::pos_muros()
{
  return (rejilla.pos_muros());
}
void Vista::dibuja_trayectoria(const std::vector<std::pair<unsigned,unsigned>>& solucion)
{
  for (auto pos:solucion)
  {
    sf::Vector2f posicion{static_cast<float>(pos.second*tam_casilla),static_cast<float>(pos.first*tam_casilla)};
    if (rejilla.get_tipo_casilla(posicion) == Tipo_casilla::vacia)
    rejilla.set_tipo_casilla(posicion, Tipo_casilla::trayectoria);
  }
}

void Vista::procesa_eventos()
{
  sf::Event event;
  while (render_window.pollEvent(event))
  {
    switch (event.type)
    {
      case sf::Event::Closed:
      render_window.close();
      break;
      case sf::Event::MouseButtonPressed:
      procesa_eventos_raton();
      break;
      case sf::Event::KeyPressed:
      procesa_eventos_teclado(event.key.code);
      break;
      default:
      break;
    }
  }
}

void Vista::procesa_eventos_teclado(sf::Keyboard::Key& key)
{
  switch (key)
  {
    case sf::Keyboard::S:
    if(existe_casilla_inicial && existe_casilla_final)
    {
      rejilla.borra_trayectoria();
      solveTime.restart();
      observador.notifica(Evento_Vista::EJECUTAR);
    }
    else
    {
      noCasillaText.setString("Start/final square are missing");
    }
    break;
    case sf::Keyboard::C:
    rejilla.borra_trayectoria();
    break;
    case sf::Keyboard::R:
    rejilla.crea_rejilla_aleatorio();
    default:
    break;
  }
}

void Vista::procesa_eventos_raton()
{
  auto mousePos = sf::Mouse::getPosition(render_window);
  sf::Vector2f mousePosition(mousePos.x, mousePos.y);

  auto casilla = rejilla.get_tipo_casilla(mousePosition);
  if(existe_casilla_inicial==false)
  {
    if(casilla==Tipo_casilla::fin)
    {
      existe_casilla_final = false;
      noCasillaText.setString("Final square is missing");
    }
    else
    noCasillaText.setString("");
    rejilla.set_tipo_casilla(mousePosition,Tipo_casilla::inicio);
    existe_casilla_inicial = true;
  }
  else if(existe_casilla_final==false)
  {
    if(casilla==Tipo_casilla::inicio)
    {
      existe_casilla_inicial = false;
      noCasillaText.setString("Start square is missing");
    }
    else
    noCasillaText.setString("");
    rejilla.set_tipo_casilla(mousePosition,Tipo_casilla::fin);
    existe_casilla_final = true;
  }
  else
  {
    switch (casilla)
    {
      case Tipo_casilla::muro:
      rejilla.set_tipo_casilla(mousePosition, Tipo_casilla::vacia);
      break;
      case Tipo_casilla::vacia:
      rejilla.set_tipo_casilla(mousePosition, Tipo_casilla::muro);
      break;
      case Tipo_casilla::trayectoria:
      rejilla.set_tipo_casilla(mousePosition, Tipo_casilla::muro);
      break;
      case Tipo_casilla::inicio:
      rejilla.set_tipo_casilla(mousePosition, Tipo_casilla::vacia);
      existe_casilla_inicial = false;
      noCasillaText.setString("Start square is missing");
      break;
      case Tipo_casilla::fin:
      rejilla.set_tipo_casilla(mousePosition, Tipo_casilla::vacia);
      existe_casilla_final = false;
      noCasillaText.setString("Final square is missing");
      default:
      break;
    }
  }
}

void Vista::render()
{
  render_window.clear();

  render_window.draw(rejilla);
  render_window.draw(texto_num_movimientos);
  render_window.draw(texto_tiempo);
  render_window.draw(texto_desplazamiento_en_diagonal);
  render_window.draw(texto_trayectoria_encontrada);
  render_window.draw(noCasillaText);

  render_window.display();
}

void Vista::trayectoria_encontrada(const std::vector<std::pair<unsigned,unsigned>>& solucion,const unsigned num_movimientos)
{

  texto_tiempo.setString("Resolve time: " +
  parche::to_string(solveTime.getElapsedTime().asMilliseconds()) +
  " ms");
  texto_num_movimientos.setString("Finally, " +
  parche::to_string(num_movimientos)+" nodes were expanded");
  if(!solucion.empty())
  {
    texto_trayectoria_encontrada.setString("");
    dibuja_trayectoria(solucion);
  }
  else
  {
    texto_trayectoria_encontrada.setString("Not trajectory has been found");
  }
}
