#include "../header/vista.h"
#include <sstream>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>


void Vista::inicializar()
{
	render_window.create(sf::VideoMode(ancho, alto), "MNIST");
	gui.setTarget(render_window);
	crea_controles(ancho, alto);
}

void Vista::crea_controles(unsigned anc, unsigned alt)
{
	tgui::Button::Ptr boton_cargar;
	tgui::Button::Ptr boton_ejecutar;

	tgui::Label::Ptr label_val1;
	tgui::Label::Ptr label_val2;
	tgui::Label::Ptr label_resultado;
	tgui::Label::Ptr label_error;

	tgui::EditBox::Ptr edit_box_val1;
	tgui::EditBox::Ptr edit_box_val2;

	boton_cargar = tgui::Button::create();
	boton_cargar->setText("LOAD MNIST");
	boton_cargar->setSize(anc - 20, 40);
	boton_cargar->setPosition(10, 15);
	boton_cargar->setTextSize(25);
	boton_cargar->hideWithEffect(hide_animation, hide_time);

	boton_ejecutar = tgui::Button::create();
	boton_ejecutar->setText("CLASSIFY");
	boton_ejecutar->setSize(anc - 20, 40);
	boton_ejecutar->setPosition(10, 170);
	boton_ejecutar->setTextSize(25);
	boton_ejecutar->hideWithEffect(hide_animation, hide_time);

	label_error = tgui::Label::create();
	label_error->setSize(anc - 20, 60);
	label_error->setPosition(10, 225);
	label_error->setTextSize(22);
	label_error->hideWithEffect(hide_animation, hide_time);

	label_resultado = tgui::Label::create();
	label_resultado->setSize(anc - 20, 60);
	label_resultado->setPosition(anc - 110, 222);
	label_resultado->setTextSize(40);
	label_resultado->hideWithEffect(hide_animation, hide_time);

	label_val1 = tgui::Label::create();
	label_val1->setSize((anc / 2) + 10, 40);
	label_val1->setPosition(10, 60);
	label_val1->setText("k value");
	label_val1->setTextSize(25);
	label_val1->hideWithEffect(hide_animation, hide_time);

	label_val2 = tgui::Label::create();
	label_val2->setSize((anc / 2) + 10, 40);
	label_val2->setPosition(10, 110);
	label_val2->setText("Pic num. ");
	label_val2->setTextSize(25);
	label_val2->hideWithEffect(hide_animation, hide_time);

	edit_box_val1 = tgui::EditBox::create();
	edit_box_val1->setSize((anc / 2) - 30, 40);
	edit_box_val1->setPosition((anc / 2) + 20, 55);
	edit_box_val1->setAlignment(tgui::EditBox::Alignment::Right);
	edit_box_val1->hideWithEffect(hide_animation, hide_time);

	edit_box_val2 = tgui::EditBox::create();
	edit_box_val2->setSize((anc / 2) - 30, 40);
	edit_box_val2->setPosition((anc / 2) + 20, 105);
	edit_box_val2->setAlignment(tgui::EditBox::Alignment::Right);
	edit_box_val2->hideWithEffect(hide_animation, hide_time);

	//CALLBACKS
	//cambios que afectan al modelo. Informamos al controlador

	boton_cargar->connect("pressed", [this]()
	{
		notifica(Evento_Vista::cargar);
	});
	boton_ejecutar->connect("pressed", [this]()
	{
		notifica(Evento_Vista::ejecutar);
	});

	gui.add(label_val1, "label_val1");
	gui.add(label_val2, "label_val2");
	gui.add(label_error, "label_error");
	gui.add(label_resultado, "label_resultado");

	gui.add(edit_box_val1, "edit_box_val1");
	gui.add(edit_box_val2, "edit_box_val2");

	gui.add(boton_cargar, "boton_cargar");
	gui.add(boton_ejecutar, "boton_ejecutar");
}

unsigned Vista::lee_valor(const std::string& id) const
{
	std::string cadena = gui.get<tgui::EditBox>(id)->getText();
	std::stringstream ss(cadena);
	unsigned valor;
	ss >> valor;
	return valor;
}

void Vista::ejecutar(unsigned anc, unsigned alt)
{
	ancho = anc;
	alto = alt;
	inicializar();
	notifica(Evento_Vista::iniciar_programa);
	while (render_window.isOpen())
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
			notifica(Evento_Vista::finalizar_programa);
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
	gui.draw();  //Dibuja botones y texto
	if (visualiza_imagen)
	{
		render_window.draw(sprite); //Dibuja codigo
	}
	render_window.display();
}
