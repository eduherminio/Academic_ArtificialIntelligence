#include "../header/casilla.h"
#include <iostream>

Casilla::Casilla() = default;

Casilla::Casilla(sf::Rect<unsigned> r) :rect(sf::Vector2f(r.width, r.height))
{
	rect.setPosition(r.left, r.top);

	//Fijamos color y ancho bordes casilla
	rect.setOutlineColor(sf::Color(0, 0, 0));
	rect.setOutlineThickness(1.f);

	auto radio = 0.45*r.width;
	circulo_grande.setRadius(radio);
	circulo_grande.setPosition(r.left + 0.05*r.width, r.top + 0.05*r.width);

	radio = 0.2*r.width;
	circulo_pequenho.setRadius(radio);
	circulo_pequenho.setPosition(r.left + 0.3*r.width, r.top + 0.3*r.width);

}

void Casilla::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(rect, states);
	if (tipo_casilla == Tipo_casilla::humano || tipo_casilla == Tipo_casilla::ordenador)
	{
		target.draw(circulo_grande, states);
	}
	else if (tipo_casilla == Tipo_casilla::vacia_posible)
	{
		target.draw(circulo_pequenho, states);
	}


}

void Casilla::set_tipo(Tipo_casilla tipo, const Textura& textura)
{
	if (tipo_casilla != tipo)
	{
		tipo_casilla = tipo;
		if (tipo_casilla == Tipo_casilla::vacia_tono1 || tipo_casilla == Tipo_casilla::vacia_tono2)
			rect.setTexture(&textura.get_textura_casilla(tipo_casilla));
		else if (tipo_casilla == Tipo_casilla::vacia_posible)
			circulo_pequenho.setTexture(&textura.get_textura_casilla(tipo_casilla));
		else
			circulo_grande.setTexture(&textura.get_textura_casilla(tipo_casilla));
	}
}
Tipo_casilla Casilla::get_tipo() const
{
	return tipo_casilla;
}
