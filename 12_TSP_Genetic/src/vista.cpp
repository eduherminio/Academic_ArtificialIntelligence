#include "../header/vista.h"

#include <sstream>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>


void Vista::inicializar()
{
  render_window.create(sf::VideoMode(ancho,alto),"TSP Genetic Algorithms");
  gui.setWindow(render_window);
  canvas.inicializa(offset_x,offset_y,ancho-ancho_panel,alto);
  panel.inicializa(ancho_panel,alto,ancho-ancho_panel,0);
  gui.add(panel.boton_cargar);
  gui.add(panel.boton_ejecutar);
  gui.add(panel.boton_detener);
  gui.add(panel.distancia_optima);
  gui.add(panel.mejor_distancia);
  gui.add(panel.iteracion);
  panel.boton_cargar->connect("pressed",    &Observador<Evento_Vista>::notifica,observador,Evento_Vista::cargar);
  panel.boton_ejecutar->connect("pressed",  &Observador<Evento_Vista>::notifica,observador,Evento_Vista::ejecutar);
  panel.boton_detener->connect("pressed",   &Observador<Evento_Vista>::notifica,observador,Evento_Vista::detener);
}

void Vista::ejecutar(unsigned anc,unsigned alt,unsigned anc_panel)
{
  ancho=anc;
  alto=alt;
  ancho_panel=anc_panel;
  inicializar();
  observador.notifica(Evento_Vista::iniciar_programa);
  while(render_window.isOpen())
  {
    procesa_eventos();
    render();
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
      observador.notifica(Evento_Vista::finalizar_programa);
      render_window.close();
      break;
      default:
      break;
    }
    gui.handleEvent(event);
  }
}

void Vista::render()
{
  render_window.clear(sf::Color::White);
  render_window.draw(panel);
  std::lock_guard<std::mutex>lock(barrera_render);    //Bloqueamos actualizacion ruta y texto
  gui.draw();  //Dibuja botones y texto
  render_window.draw(canvas); //Dibuja codigo
  render_window.display();
}
