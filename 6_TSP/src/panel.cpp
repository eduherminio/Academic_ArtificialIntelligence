#include "../header/panel.h"

void Panel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(marco);
}

void Panel::inicializa(unsigned anc, unsigned alt, unsigned px, unsigned py)
{
	ancho = anc;
	alto = alt;
	pos_x = px;
	pos_y = py;

	std::string root_path =
#if _MSC_VER && !__INTEL_COMPILER
		"./";
#else
		"../";
#endif

	tgui::Theme theme(root_path + "resources/Black.txt");
	boton_cargar = tgui::Button::create("LOAD TSP");
	boton_cargar->setRenderer(theme.getRenderer("button"));
	boton_cargar->setSize(ancho - 20, 40);
	boton_cargar->setPosition(pos_x + 10, 15);
	boton_cargar->setTextSize(25);
	boton_cargar->hideWithEffect(hide_animation, hide_time);
	boton_ejecutar = tgui::Button::create("CALCULATE");
	boton_ejecutar->setRenderer(theme.getRenderer("button"));
	boton_ejecutar->setSize(ancho - 20, 40);
	boton_ejecutar->setPosition(pos_x + 10, 60);
	boton_ejecutar->setTextSize(25);
	boton_ejecutar->hideWithEffect(hide_animation, hide_time);
	boton_detener = tgui::Button::create("STOP");
	boton_detener->setRenderer(theme.getRenderer("button"));
	boton_detener->setSize(ancho - 20, 40);
	boton_detener->setPosition(pos_x + 10, 105);
	boton_detener->setTextSize(25);
	boton_detener->hideWithEffect(hide_animation, hide_time);

	distancia_optima = tgui::Label::create();
	distancia_optima->setRenderer(theme.getRenderer("label"));
	distancia_optima->setPosition(pos_x + 10, 150);
	distancia_optima->setTextSize(18);

	iteracion = tgui::Label::create();
	iteracion->setRenderer(theme.getRenderer("label"));
	iteracion->setPosition(pos_x + 10, 170);
	iteracion->setTextSize(18);

	mejor_distancia = tgui::Label::create();
	mejor_distancia->setRenderer(theme.getRenderer("label"));
	mejor_distancia->setPosition(pos_x + 10, 190);
	mejor_distancia->setTextSize(18);

	marco = sf::RectangleShape(sf::Vector2f(ancho, alto));
	marco.setPosition(sf::Vector2f(pos_x, pos_y));
	marco.setFillColor(sf::Color(128, 128, 128));
}
