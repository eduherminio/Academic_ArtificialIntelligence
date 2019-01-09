#include "../header/rejilla.h"
#include <stdexcept>
#include <iostream>

Rejilla::Rejilla(unsigned filas, unsigned columnas, unsigned tam_casilla) :
	filas(filas), columnas(columnas), tam_casilla(tam_casilla), ancho(columnas*tam_casilla), alto(filas*tam_casilla)
{
	for (auto y = 0u; y <= alto; y += tam_casilla)
	{
		for (auto x = 0u; x < ancho; x += tam_casilla)
		{
			Casilla t(sf::Rect<unsigned>(x, y, tam_casilla, tam_casilla));
			casillas.push_back(t);
		}
	}
	//Fija por defecto la inicial y la final en los vertices superior izquierda e inferior derecha respectivamente
	casillas[0].set_tipo(Tipo_casilla::inicio);
	casillas[filas*columnas - 1].set_tipo(Tipo_casilla::fin);
}

Rejilla::Rejilla(const Rejilla& rejilla) = default;

Rejilla& Rejilla::operator=(const Rejilla& other) = default;

inline int Rejilla::indice_casilla(sf::Vector2f posicion) const
{
	auto col = static_cast<int>(posicion.x) / tam_casilla;
	auto fil = static_cast<int>(posicion.y) / tam_casilla;

	return (fil*columnas + col);
}

void Rejilla::borra_rejilla()
{
	for (auto& casilla : casillas)
	{
		casilla.set_tipo(Tipo_casilla::vacia);
	}
}

Rejilla::Rejilla() = default;

void Rejilla::set_tipo_casilla(sf::Vector2f posicion, Tipo_casilla tipo_casilla)
{
	casillas[indice_casilla(posicion)].set_tipo(tipo_casilla);
}

void Rejilla::borra_trayectoria()
{
	for (auto& casilla : casillas)
	{
		if (casilla.get_tipo() == Tipo_casilla::trayectoria)
			casilla.set_tipo(Tipo_casilla::vacia);
	}
}

Tipo_casilla Rejilla::get_tipo_casilla(sf::Vector2f posicion) const
{
	return(casillas[indice_casilla(posicion)].get_tipo());
}

bool Rejilla::es_fuera_limites(sf::Vector2f posicion) const
{
	return posicion.y < 0 || posicion.y >= alto || posicion.x < 0 || posicion.x >= ancho;
}

bool Rejilla::es_muro(sf::Vector2f posicion) const
{
	return(casillas[indice_casilla(posicion)].get_tipo() == Tipo_casilla::muro);
}

const Casilla& Rejilla::get_casilla_inicial() const
{
	for (const auto& casilla : casillas)
	{
		if (casilla.get_tipo() == Tipo_casilla::inicio)
		{
			return casilla;
		}
	}
	throw std::out_of_range("No start square\n");
}
const Casilla& Rejilla::get_casilla_final() const
{
	for (const auto& casilla : casillas)
	{
		if (casilla.get_tipo() == Tipo_casilla::fin)
		{
			return casilla;
		}
	}
	throw std::out_of_range("No final square\n");
}

std::pair<unsigned, unsigned> Rejilla::pos_casilla_inicial() const
{
	unsigned indice = 0;
	for (const auto& casilla : casillas)
	{
		if (casilla.get_tipo() == Tipo_casilla::inicio)
		{
			unsigned fil = indice / columnas;
			unsigned col = indice % columnas;
			return { fil,col };
		}
		++indice;
	}
	throw std::out_of_range("No start square\n");
}
std::pair<unsigned, unsigned> Rejilla::pos_casilla_final() const
{
	unsigned indice = 0;
	for (const auto& casilla : casillas)
	{
		if (casilla.get_tipo() == Tipo_casilla::fin)
		{
			unsigned fil = indice / columnas;
			unsigned col = indice % columnas;
			return { fil,col };
		}
		++indice;
	}
	throw std::out_of_range("No hay casilla final\n");
}

std::vector<std::pair<unsigned, unsigned>> Rejilla::pos_muros() const
{
	std::vector<std::pair<unsigned, unsigned>> muros;

	unsigned indice = 0;
	for (const auto& casilla : casillas)
	{
		if (casilla.get_tipo() == Tipo_casilla::muro)
		{
			unsigned fil = indice / columnas;
			unsigned col = indice % columnas;
			muros.push_back({ fil,col });
		}
		++indice;
	}
	return muros;
}


void Rejilla::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	for (const auto& casilla : casillas)
		target.draw(casilla);
}


void Rejilla::crea_rejilla_aleatorio()
{
	static std::mt19937 engine(std::random_device{}());
	std::uniform_int_distribution<> distr(0, (casillas.size() / 2));
	std::uniform_int_distribution<> distr_fil(0, filas - 1);
	std::uniform_int_distribution<> distr_col(0, columnas - 1);

	borra_rejilla();

	auto num_casillas_muro = distr(engine);
	for (auto i = 0; i < num_casillas_muro; ++i)
	{
		auto indice = distr_col(engine) + distr_fil(engine)*columnas;
		if (casillas[indice].get_tipo() != Tipo_casilla::inicio && casillas[indice].get_tipo() != Tipo_casilla::fin)
		{
			casillas[indice].set_tipo(Tipo_casilla::muro);
		}
	}

	//Fija aleatoriamente el inicio y el final
	int indice1, indice2;
	do
	{
		indice1 = distr_col(engine) + distr_fil(engine)*columnas;
		indice2 = distr_col(engine) + distr_fil(engine)*columnas;
	} while (indice1 == indice2);

	casillas[indice1].set_tipo(Tipo_casilla::inicio);
	casillas[indice2].set_tipo(Tipo_casilla::fin);
}
