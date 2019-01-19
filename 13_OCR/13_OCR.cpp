#include "./header/controlador.h"

int main()
{
	Vista vista;

	Mnist mnist;
	Knn<std::vector<uint8_t>, uint8_t> knn;

	controlador::Controlador c(vista, knn, mnist);
	c.ejecutar();
}
