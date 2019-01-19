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
	tgui::Theme::Ptr theme = std::make_shared<tgui::Theme>("../resources/Black.txt");
	boton_cargar = tgui::Button::Ptr(theme->load("button"));
	boton_cargar->setText("LOAD TSP");
	boton_cargar->setSize(ancho - 20, 40);
	boton_cargar->setPosition(pos_x + 10, 15);
	boton_cargar->setTextSize(25);
	boton_cargar->hide();
	boton_ejecutar = tgui::Button::Ptr(theme->load("button"));
	boton_ejecutar->setText("CALCULATE");
	boton_ejecutar->setSize(ancho - 20, 40);
	boton_ejecutar->setPosition(pos_x + 10, 60);
	boton_ejecutar->setTextSize(25);
	boton_ejecutar->hide();
	boton_detener = tgui::Button::Ptr(theme->load("button"));
	boton_detener->setText("STOP");
	boton_detener->setSize(ancho - 20, 40);
	boton_detener->setPosition(pos_x + 10, 105);
	boton_detener->setTextSize(25);
	boton_detener->hide();

	distancia_optima = tgui::Label::Ptr(theme->load("label"));
	distancia_optima->setPosition(pos_x + 10, 150);
	distancia_optima->setTextSize(18);

	iteracion = tgui::Label::Ptr(theme->load("label"));
	iteracion->setPosition(pos_x + 10, 170);
	iteracion->setTextSize(18);

	mejor_distancia = tgui::Label::Ptr(theme->load("label"));
	mejor_distancia->setPosition(pos_x + 10, 190);
	mejor_distancia->setTextSize(18);

	marco = sf::RectangleShape(sf::Vector2f(ancho, alto));
	marco.setPosition(sf::Vector2f(pos_x, pos_y));
	marco.setFillColor(sf::Color(128, 128, 128));
}
