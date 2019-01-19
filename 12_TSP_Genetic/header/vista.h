#ifndef VISTA_H_INCLUDED
#define VISTA_H_INCLUDED

#include "../header/observador.h"
#include "../header/canvas.h"
#include "../header/panel.h"

#include <mutex>
#include <TGUI/TGUI.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

enum class Evento_Vista { cargar, ejecutar, detener, iniciar_programa, finalizar_programa };
class Vista
{
public:
	Vista()
	{

	}
	void set_coordenadas(std::vector<std::pair<unsigned, unsigned>> const & coor)
	{
		canvas.set_coordenadas(coor);
	}
	void set_recorrido_optimo(std::vector<unsigned> const & ind)
	{
		std::lock_guard<std::mutex>lock(barrera_render);    //Bloqueamos render
		canvas.set_recorrido_optimo(ind);
	}


	void get_rectangulo_canvas(unsigned& x_sup_izq, unsigned& y_sup_izq, unsigned& x_inf_der, unsigned& y_inf_der) const
	{
		x_sup_izq = offset_x;
		y_sup_izq = offset_y;
		x_inf_der = alto - offset_x;
		y_inf_der = ancho - ancho_panel - offset_y;

	}
	std::vector<std::pair<unsigned, unsigned>> pos_muros();
	Observador<Evento_Vista>& get_observador()
	{
		return observador;
	}
	void ejecutar(unsigned anc, unsigned alt, unsigned anc_panel);
	void inicializar();
	void muestra_boton_cargar()
	{
		panel.boton_cargar->show();
	}
	void oculta_boton_cargar()
	{
		panel.boton_cargar->hide();
	}
	void muestra_boton_detener()
	{
		panel.boton_detener->show();
	}
	void oculta_boton_detener()
	{
		panel.boton_detener->hide();
	}
	void muestra_boton_ejecutar()
	{
		panel.boton_ejecutar->show();
	}
	void oculta_boton_ejecutar()
	{
		panel.boton_ejecutar->hide();
	}
	void set_texto_distancia_optima(const std::string&& texto)
	{
		panel.distancia_optima->setText(texto);
	}
	void set_texto_mejor_distancia(const std::string&& texto)
	{
		panel.mejor_distancia->setText(texto);
	}
	void set_texto_iteracion(const std::string&& texto)
	{
		panel.iteracion->setText(texto);
	}
	void actualiza_recorrido(const std::vector<unsigned>& ind, const std::string&& texto1, const std::string&& texto2)
	{
		std::lock_guard<std::mutex>lock(barrera_render);    //Bloqueamos render
		panel.iteracion->setText(texto1);
		panel.mejor_distancia->setText(texto2);
		canvas.set_recorrido(ind);

	}
	void registra_observador(const Evento_Vista& evento, std::function<void()> obs)
	{
		observador.registra_observador(evento, obs);
	}
private:
	unsigned ancho;
	unsigned alto;
	unsigned ancho_panel;
	const unsigned offset_x = 5;
	const unsigned offset_y = 5;
	sf::RenderWindow render_window;
	tgui::Gui gui;
	Canvas canvas;
	Panel panel;
	std::mutex barrera_render;
	void procesa_eventos();
	void render();

	Observador<Evento_Vista> observador;
};

#endif // VISTA_H_INCLUDED
