#include "../header/canvas.h"

void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(marco);
	for (const auto& punto : puntos)
		target.draw(punto);

	target.draw(recorrido);

}
void Canvas::set_recorrido(const std::vector<unsigned> &nuevo_recorrido)
{
	if (!nuevo_recorrido.empty()) //Se ha cargado un recorrido
	{
		recorrido = sf::VertexArray(sf::LineStrip);
		unsigned indice;
		for (size_t i = 0; i != nuevo_recorrido.size(); ++i)
		{
			indice = nuevo_recorrido.at(i);
			sf::Vertex vertice(sf::Vector2f(coordenadas.at(indice).first, coordenadas.at(indice).second), sf::Color::Black);
			recorrido.append(vertice);
		}
		indice = nuevo_recorrido.at(0);
		sf::Vertex vertice(sf::Vector2f(coordenadas.at(indice).first, coordenadas.at(indice).second), sf::Color::Black);
		recorrido.append(vertice);
	}
}

void Canvas::set_puntos()
{
	puntos.clear();
	if (!coordenadas.empty()) //Se han cargado coordenadas
	{
		sf::CircleShape punto;
		for (auto &p : coordenadas)
		{
			punto.setRadius(2);
			punto.setFillColor(sf::Color::Black);
			punto.setPosition(p.first - 2, p.second - 2);
			puntos.push_back(punto);
		}
	}
}
