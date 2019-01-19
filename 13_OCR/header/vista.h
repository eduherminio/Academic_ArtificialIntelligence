#ifndef VISTA_H_INCLUDED
#define VISTA_H_INCLUDED

#include "../header/observador.h"
#include <mutex>
#include <TGUI/TGUI.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

enum class Evento_Vista { cargar, ejecutar, detener, iniciar_programa, finalizar_programa };
class Vista :public Observable<Evento_Vista>
{
public:
	Vista()
	{

	}
	void ejecutar(unsigned anc, unsigned alt);
	void inicializar();
	void set_boton_cargar(bool valor)
	{
		if (valor == true)
			gui.get<tgui::Button>("boton_cargar")->show();
		else
			gui.get<tgui::Button>("boton_cargar")->hide();
	}
	void set_boton_ejecutar(bool valor)
	{
		if (valor == true)
			gui.get<tgui::Button>("boton_ejecutar")->show();
		else
			gui.get<tgui::Button>("boton_ejecutar")->hide();
	}
	void oculta_label_error()
	{
		gui.get<tgui::Label>("label_error")->hide();
	}
	void oculta_label_resultado()
	{
		gui.get<tgui::Label>("label_resultado")->hide();
	}
	void muestra_botones_seleccion()
	{
		gui.get<tgui::Label>("label_val1")->show();
		gui.get<tgui::Label>("label_val2")->show();

		gui.get<tgui::EditBox>("edit_box_val1")->show();
		gui.get<tgui::EditBox>("edit_box_val2")->show();

		gui.get<tgui::Button>("boton_ejecutar")->show();
	}

	unsigned k() const
	{
		return(lee_valor("edit_box_val1"));
	}
	unsigned indice() const
	{
		return lee_valor("edit_box_val2");
	}
	void set_imagen(sf::Image&& im)
	{
		imagen = std::move(im);
		texture.loadFromImage(imagen);
		sprite.setTexture(texture);
		sprite.setPosition(90, 230);
	}
	void set_visualiza_imagen(bool valor)
	{
		visualiza_imagen = valor;
	}
	void muestra_error(const std::string& cadena)
	{
		gui.get<tgui::Label>("label_error")->setText(cadena);
		gui.get<tgui::Label>("label_error")->show();
	}
	void muestra_resultado(const unsigned resultado)
	{
		std::stringstream ss;
		ss << resultado;
		gui.get<tgui::Label>("label_resultado")->setText(ss.str());
		gui.get<tgui::Label>("label_resultado")->show();
	}
	void oculta_error()
	{
		gui.get<tgui::Label>("label_error")->hide();
	}
private:
	unsigned ancho;
	unsigned alto;

	sf::RenderWindow render_window;
	tgui::Gui gui;
	void crea_controles(unsigned anc, unsigned alt);

	sf::Image imagen;
	sf::Texture texture;
	sf::Sprite  sprite;
	void procesa_eventos();
	void render();

	bool visualiza_imagen = false;
	unsigned lee_valor(const std::string&) const;
};

#endif // VISTA_H_INCLUDED
