//FELIX MIGUEL TRESPADERNE
//INTELIGENCIA ARTIFICIAL APLICADA AÑO 2017
//Inspirado en Simulated Annealing Methods, seccion 10.9 del libro
//NUMERICAL RECIPES IN C


#include "../header/recocido_simulado_tsp.h"

void Recocido_simulado_TSP::inicializacion(const int& num_ciudades)
{
	// DONE: Initialization, sintonizing algorithm parameters
	num_descensos = 50 * num_ciudades;
	num_permutaciones = 100 * num_ciudades;
	num_exitos_maximo = 0.4*num_permutaciones;
	temperatura = 10 * num_ciudades;
	factor_descenso = 0.99;
	set_v_lookup_table();
}

// Calcula una ruta mediante recocido simulado
void Recocido_simulado_TSP::ejecutar(ruta::Ruta& ruta, int& num_ciudades)
{
	inicializacion(num_ciudades);

	std::cout << std::endl << "Optimizing" << std::endl << "(...)" << std::endl;

	std::mt19937 rng;
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	rng.seed(seed);
	std::uniform_real_distribution<double> aleatorio_0_a_1(0, 1);

	ruta.inicializa_recorrido();
	auto distancia_actual = ruta.get_distancia_actual();
	mejor_distancia = distancia_actual;
	iteracion_actual = 0;
	mejor_recorrido = ruta.get_recorrido();

	observador.notifica(Evento_Modelo::nuevo_recorrido);

	abortar = false;
	for (; iteracion_actual < num_descensos; ++iteracion_actual)   // Algoritmo que itera entre las temperaturas
	{
		unsigned num_exitos = 0;
		for (unsigned j = 0; j < num_permutaciones; j++)           // Permutaciones para cada una de las temperaturas (copia del artículo de original recipes del campus)
		{
			if (abortar)   // Señal del hilo de la vista para que se detenga el algoritmo
			{
				return;
			}
			ruta.crea_recorrido_vecino();                     // Crea un recorrido que se le parezca -> recorrido provisional

			auto distancia_provisional = ruta.get_distancia_provisional();
			auto incremento = distancia_actual - distancia_provisional;   // incremento > 0 -> mejora


			// DONE: Hacer una LUT para la funcion exp(incremento/temperatura)
			double actual = (double)incremento / temperatura;
			size_t index = std::abs(round(1000 * (actual)));
			if (index > 9999 && incremento <= 0)
				continue;
			// if(incremento>0 || aleatorio_0_a_1(rng) < exp(incremento/temperatura))             //DECISON METROPOLIS
			if (incremento > 0 || (aleatorio_0_a_1(rng) < v_lookup_table2[index] && incremento > 0))   // KEY-> incremento !=0
			{
				// if(incremento<0){
				//   std::cout<<index<<std::endl;
				//   std::cout<<v_lookup_table2[index]<<" "<<exp(incremento/temperatura)<<std::endl;
				// }

				ruta.actualiza_ruta();  // Actualizamos la ruta actual
				distancia_actual = distancia_provisional;

				if (distancia_actual < mejor_distancia)        // Nofitica el controlador para que actualice la vista
				{  //Notificamos al Controlador
					mejor_distancia = distancia_actual;
					mejor_recorrido = ruta.get_recorrido();
					observador.notifica(Evento_Modelo::nuevo_recorrido);
				}
				if (++num_exitos > num_exitos_maximo)        // Si, para una temperatura, muchos exitos -> sistema muy caliente (acepto cualquier cosa) -> corto el bucle interno y enfrío la temperatura
					break;
			}
		}
		if (num_exitos == 0)                                 // Si, para una temperatura, ningún éxito -> Fin del algoritmo ()
			break;
		temperatura *= factor_descenso;
		if (temperatura == 0)
			break;

		// std::cout<<"Temp: "<<temperatura<<" exitos: "<<num_exitos<<std::endl;
	}
	std::cout << std::endl << "**END**" << std::endl;
}

void Recocido_simulado_TSP::set_v_lookup_table()
{
	v_lookup_table.push_back(exp(0));
	v_lookup_table2[0] = exp(0);
	for (int i = 1; i < 10000; ++i)
	{
		double exponent = -(double)i / 1000;         // [-0.001, -9.999];
		v_lookup_table.push_back(exp(exponent));
		v_lookup_table2[i] = exp(exponent);
	}
	// for(int i=0; i<10000; ++i)
	//   std::cout<<v_lookup_table2[i]<<" ";
}
