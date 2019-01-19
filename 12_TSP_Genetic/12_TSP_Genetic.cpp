#include "header/controlador.h"

int main()
{
	Vista vista;

	Genetico_Tsp<ruta::Ruta> genetico_tsp;
	// genetico_tsp.inicializacion(num_individuos,porcentaje_elite,num_generaciones,probabilidad_mutacion,tam_torneo);  // Later, in genetico_tsp.ejecutar() (when we have the number of loaded cities)
	genetico_tsp.set_seleccion(Seleccion::torneo_determinista);
	controlador::Controlador c(vista, genetico_tsp);
	c.ejecutar();
}
