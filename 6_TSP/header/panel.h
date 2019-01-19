#ifndef PANEL_H_INCLUDED
#define PANEL_H_INCLUDED

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Panel :public sf::Drawable
{
public:
	Panel()
	{

	}
	void inicializa(unsigned anc, unsigned alt, unsigned px, unsigned py);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	tgui::Button::Ptr boton_cargar;
	tgui::Button::Ptr boton_ejecutar;
	tgui::Button::Ptr boton_detener;
	tgui::Label::Ptr distancia_optima;
	tgui::Label::Ptr mejor_distancia;
	tgui::Label::Ptr iteracion;
private:
	unsigned ancho;
	unsigned alto;
	unsigned pos_x;
	unsigned pos_y;
	sf::RectangleShape marco;

	tgui::ShowAnimationType hide_animation = tgui::ShowAnimationType::Scale;
	sf::Time hide_time = sf::Time::Zero;
};


#endif // PANEL_H_INCLUDED
