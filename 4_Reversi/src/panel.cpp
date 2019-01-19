#include "../header/panel.h"
#include <iostream>

void Panel::inicializa(unsigned ancho, unsigned alto, unsigned ancho_panel)
{
	//Load font
	std::string root_path =
#if _MSC_VER && !__INTEL_COMPILER
		"./";
#else
		"../";
#endif

	font.loadFromFile(root_path + "resources/sansation.ttf");
	fondo_panel = sf::RectangleShape(sf::Vector2f(ancho_panel, alto));
	fondo_panel.setPosition(ancho - ancho_panel, 0);
	fondo_panel.setFillColor(sf::Color(255, 0, 0, 175));

	fondo_puntuacion = sf::RectangleShape(sf::Vector2f(ancho_panel - 20, 65));
	fondo_puntuacion.setPosition(ancho - ancho_panel + 10, 60);
	fondo_puntuacion.setFillColor(sf::Color(255, 125, 120, 125));

	boton_ordenador = sf::RectangleShape(sf::Vector2f(ancho_panel - 30, 50));
	boton_ordenador.setPosition(ancho - ancho_panel + 15, alto - 120);
	texto_boton_ordenador.setFont(font);
	texto_boton_ordenador.setString("1 player");
	texto_boton_ordenador.setPosition(ancho - ancho_panel + 27, alto - 115);
	texto_boton_ordenador.setFillColor(sf::Color::Black);

	boton_manual = sf::RectangleShape(sf::Vector2f(ancho_panel - 30, 50));
	boton_manual.setPosition(ancho - ancho_panel + 15, alto - 60);
	texto_boton_manual.setFont(font);
	texto_boton_manual.setString("2 players");
	texto_boton_manual.setPosition(ancho - ancho_panel + 27, alto - 55);
	texto_boton_manual.setFillColor(sf::Color::Black);

	texto_etiqueta_turno.setFont(font);
	texto_etiqueta_turno.setString("Current Turn:");
	texto_etiqueta_turno.setCharacterSize(18);
	texto_etiqueta_turno.setPosition(ancho - ancho_panel + 15, 15);
	texto_etiqueta_turno.setFillColor(sf::Color::Blue);
	texto_etiqueta_turno.setStyle(sf::Text::Bold);

	texto_turno.setFont(font);
	texto_turno.setString("WHITE");
	texto_turno.setCharacterSize(20);
	texto_turno.setPosition(ancho - ancho_panel + 15, 35);
	texto_turno.setFillColor(sf::Color::White);
	texto_turno.setStyle(sf::Text::Regular);
	texto_turno.setStyle(sf::Text::Bold);

	texto_etiqueta_puntuacion.setFont(font);
	texto_etiqueta_puntuacion.setString("Score");
	texto_etiqueta_puntuacion.setPosition(ancho - ancho_panel + 15, 60);
	texto_etiqueta_puntuacion.setCharacterSize(20);
	texto_etiqueta_puntuacion.setFillColor(sf::Color::Blue);
	texto_etiqueta_puntuacion.setStyle(sf::Text::Bold);

	texto_puntuacion.setFont(font);
	texto_puntuacion.setString("");
	texto_puntuacion.setCharacterSize(18);
	texto_puntuacion.setPosition(ancho - ancho_panel + 15, 80);


	texto_final.setFont(font);
	texto_puntuacion.setString("");
	texto_final.setPosition(ancho - ancho_panel + 15, 130);
	texto_final.setCharacterSize(35);
	texto_final.setFillColor(sf::Color::Black);
	texto_final.setStyle(sf::Text::Bold);
}

void Panel::set_string_turno(const std::string& texto)
{
	texto_turno.setString(texto);
}
void Panel::set_string_final(const std::string& texto)
{
	texto_final.setString(texto);
}
void Panel::set_string_puntuacion(const std::string& texto)
{
	texto_puntuacion.setString(texto);
}

void Panel::color_string_turno_blanco()
{
	texto_turno.setFillColor(sf::Color::White);
}
void Panel::color_string_turno_negro()
{
	texto_turno.setFillColor(sf::Color::Black);
}
void Panel::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(fondo_panel);
	target.draw(fondo_puntuacion);
	target.draw(boton_ordenador);
	target.draw(boton_manual);

	target.draw(texto_turno);
	target.draw(texto_final);
	target.draw(texto_puntuacion);
	target.draw(texto_etiqueta_turno);
	target.draw(texto_etiqueta_puntuacion);
	target.draw(texto_boton_ordenador);
	target.draw(texto_boton_manual);

}

bool Panel::boton_ordenador_pulsado(sf::Vector2i posicion) const
{
	bool salida = false;

	auto x1 = boton_ordenador.getPosition().x;
	auto y1 = boton_ordenador.getPosition().y;
	auto x2 = x1 + boton_ordenador.getSize().x;
	auto y2 = y1 + boton_ordenador.getSize().y;

	if (posicion.x > x1 && posicion.x<x2 && posicion.y>y1 && posicion.y < y2)
	{
		salida = true;
	}

	return salida;
}
bool Panel::boton_manual_pulsado(sf::Vector2i posicion) const
{
	bool salida = false;

	auto x1 = boton_manual.getPosition().x;
	auto y1 = boton_manual.getPosition().y;
	auto x2 = x1 + boton_ordenador.getSize().x;
	auto y2 = y1 + boton_ordenador.getSize().y;

	if (posicion.x > x1 && posicion.x<x2 && posicion.y>y1 && posicion.y < y2)
	{
		salida = true;
	}

	return salida;
}
