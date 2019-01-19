#include "header/nodo_reinas.h"
#include "header/problema_csp.h"
#include <iostream>
#include <iomanip>

const unsigned dimension = 15;
const size_t iteraciones_max = 1000;
const size_t n_problemas = 1000;

typedef problema_csp::Problema_csp<nodo_reinas::Nodo_reinas>      type_queens_noset;
typedef problema_csp::Problema_csp<nodo_reinas::Nodo_reinas_set>  type_queens_set;
void single_sample(type_queens_noset problema, type_queens_set problema_set);
void multiple_sample(type_queens_noset problema, type_queens_set problema_set);

int main()
{
	nodo_reinas::Nodo_reinas nodo_inicial(dimension, {}); // Nodo sin set, vector vacio inicial
	nodo_reinas::Nodo_reinas_set nodo_inicial_set(dimension, {}); //Nodo con set, vector vacio inicial

	problema_csp::Problema_csp<nodo_reinas::Nodo_reinas>      problema(nodo_inicial);
	problema_csp::Problema_csp<nodo_reinas::Nodo_reinas_set>  problema_set(nodo_inicial_set);


	single_sample(problema, problema_set);    // Showing the position of the queens

	std::cout << "\n\n*************************************************************************" << std::endl;
	std::cout << "*************************************************************************\n\n" << std::endl;

	multiple_sample(problema, problema_set);  // Showing stats after solving n_problemas

	return 0;
}

void single_sample(type_queens_noset problema, type_queens_set problema_set)
{
	size_t iteraciones;

	std::cout << std::endl << "\t\t\t\tComplete example: " << std::endl << std::endl;

	// PROFUNDIDAD SIN SET
	if (problema.profundidad())
	{
		std::cout << "\nPROFUNDIDAD SIN SET\n";
		nodo_reinas::imprime_posicion(problema.get_solucion(), problema.get_nodos_expandidos());
	}

	// PROFUNDIDAD CON SET
	if (problema_set.profundidad())
	{
		std::cout << "\nPROFUNDIDAD CON SET\n";
		nodo_reinas::imprime_posicion(problema_set.get_solucion(), problema.get_nodos_expandidos());
	}

	// LAS_VEGAS_EXPANDIR SIN SET
	iteraciones = iteraciones_max;
	if (problema.las_vegas_expandir(iteraciones))
	{
		std::cout << "\nLAS_VEGAS_EXPANDIR SIN SET\n";
		nodo_reinas::imprime_posicion(problema.get_solucion(), problema.get_nodos_expandidos());
	}
	std::cout << "Numero de iteraciones: " << iteraciones << std::endl;

	// LAS_VEGAS_EXPANDIR CON SET
	iteraciones = iteraciones_max;
	if (problema_set.las_vegas_expandir(iteraciones))
	{
		std::cout << "\nLAS_VEGAS_EXPANDIR CON SET\n";
		nodo_reinas::imprime_posicion(problema_set.get_solucion(), problema.get_nodos_expandidos());
	}
	std::cout << "Numero de iteraciones: " << iteraciones << std::endl;

	// LAS_VEGAS_SUCESOR_ALEATORIO SIN SET
	iteraciones = iteraciones_max;
	if (problema.las_vegas_sucesor_aleatorio(iteraciones))
	{
		std::cout << "\nLAS VEGAS SUCESOR ALEATORIO SIN SET\n";
		nodo_reinas::imprime_posicion(problema.get_solucion(), problema.get_nodos_expandidos());
	}
	std::cout << "Numero de iteraciones: " << iteraciones << std::endl;

	// LAS_VEGAS_SUCESOR_ALEATORIO CON SET
	iteraciones = iteraciones_max;
	if (problema_set.las_vegas_sucesor_aleatorio(iteraciones))
	{
		std::cout << "\nLAS VEGAS SUCESOR ALEATORIO CON SET\n";
		nodo_reinas::imprime_posicion(problema_set.get_solucion(), problema.get_nodos_expandidos());
	}
	std::cout << "Numero de iteraciones: " << iteraciones << std::endl;
}

void multiple_sample(type_queens_noset problema, type_queens_set problema_set)
{
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	double nodos_promedio_profundidad_no_set;
	double nodos_promedio_profundidad_set;
	double nodos_promedio_lasvegas_expandir_no_set;
	double nodos_promedio_lasvegas_expandir_set;
	double nodos_promedio_lasvegas_sucesor_no_set;
	double nodos_promedio_lasvegas_sucesor_set;
	double iteraciones_promedio_expandir_no_set;
	double iteraciones_promedio_expandir_set;
	double iteraciones_promedio_sucesor_no_set;
	double iteraciones_promedio_sucesor_set;

	size_t counter = 0;

	std::cout << "\t\t\t" << std::put_time(&tm, "%d-%m-%Y %H:%M:%S") << std::endl;
	std::cout << "\t\t\tNumber of Queens: " << dimension << std::endl;
	std::cout << "\t\t\tMax. iterations:  " << iteraciones_max << std::endl;
	std::cout << "\tProcessing " << n_problemas << " samples to get statistical results" << std::endl;
	std::cout << "\t\t\t\t(...)" << std::endl << std::endl;

	while (true)
	{
		size_t iteraciones;

		static size_t nodos_expandidos_profundidad_set = 0;
		static size_t nodos_expandidos_profundidad_no_set = 0;
		static size_t nodos_expandidos_lasvegas_expandir_set = 0;
		static size_t nodos_expandidos_lasvegas_expandir_no_set = 0;
		static size_t nodos_expandidos_lasvegas_sucesor_set = 0;
		static size_t nodos_expandidos_lasvegas_sucesor_no_set = 0;

		static size_t iteraciones_expandir_no_set = 0;
		static size_t iteraciones_expandir_set = 0;
		static size_t iteraciones_sucesor_no_set = 0;
		static size_t iteraciones_sucesor_set = 0;

		// PROFUNDIDAD SIN SET
		problema.profundidad();
		nodos_expandidos_profundidad_no_set += problema.get_nodos_expandidos();

		// PROFUNDIDAD CON SET
		problema_set.profundidad();
		nodos_expandidos_profundidad_set += problema.get_nodos_expandidos();

		// LAS_VEGAS_EXPANDIR SIN SET
		iteraciones = iteraciones_max;
		problema.las_vegas_expandir(iteraciones);
		nodos_expandidos_lasvegas_expandir_no_set += problema.get_nodos_expandidos();
		iteraciones_expandir_no_set += iteraciones;

		// LAS_VEGAS_EXPANDIR CON SET
		iteraciones = iteraciones_max;
		problema_set.las_vegas_expandir(iteraciones);
		nodos_expandidos_lasvegas_expandir_set += problema.get_nodos_expandidos();
		iteraciones_expandir_set += iteraciones;

		// LAS_VEGAS_SUCESOR_ALEATORIO SIN SET
		iteraciones = iteraciones_max;
		problema.las_vegas_sucesor_aleatorio(iteraciones);
		nodos_expandidos_lasvegas_sucesor_no_set += problema.get_nodos_expandidos();
		iteraciones_sucesor_no_set += iteraciones;

		// LAS_VEGAS_SUCESOR_ALEATORIO CON SET
		iteraciones = iteraciones_max;
		problema_set.las_vegas_sucesor_aleatorio(iteraciones);
		nodos_expandidos_lasvegas_sucesor_set += problema.get_nodos_expandidos();
		iteraciones_sucesor_set += iteraciones;

		++counter;

		if (counter == n_problemas)
		{
			nodos_promedio_profundidad_no_set = (double)nodos_expandidos_profundidad_no_set / counter;
			nodos_promedio_profundidad_set = (double)nodos_expandidos_profundidad_set / counter;
			nodos_promedio_lasvegas_expandir_no_set = (double)nodos_expandidos_lasvegas_expandir_no_set / counter;
			nodos_promedio_lasvegas_expandir_set = (double)nodos_expandidos_lasvegas_expandir_set / counter;
			nodos_promedio_lasvegas_sucesor_no_set = (double)nodos_expandidos_lasvegas_sucesor_no_set / counter;
			nodos_promedio_lasvegas_sucesor_set = (double)nodos_expandidos_lasvegas_sucesor_set / counter;

			iteraciones_promedio_expandir_no_set = (double)iteraciones_expandir_no_set / counter;
			iteraciones_promedio_expandir_set = (double)iteraciones_expandir_set / counter;
			iteraciones_promedio_sucesor_no_set = (double)iteraciones_sucesor_no_set / counter;
			iteraciones_promedio_sucesor_set = (double)iteraciones_sucesor_set / counter;

			break;
		}
	}

	std::cout << std::endl;
	std::cout << "-----------------------------------------------------------------------" << std::endl;
	std::cout << "\tAlgoritmo\t   Nodos promedio\tIteraciones promedio\n" << std::endl;
	std::cout << "\tProf_no_set\t\t" << nodos_promedio_profundidad_no_set << std::endl;
	std::cout << "\tProf_set\t\t" << nodos_promedio_profundidad_set << std::endl;
	std::cout << "\tVegas_exp_no_set\t" << nodos_promedio_lasvegas_expandir_no_set << "\t\t\t";
	std::cout << iteraciones_promedio_expandir_no_set << std::endl;
	std::cout << "\tVegas_exp_set\t\t" << nodos_promedio_lasvegas_expandir_set << "\t\t\t";
	std::cout << iteraciones_promedio_expandir_set << std::endl;
	std::cout << "\tVegas_suc_no_set\t" << nodos_promedio_lasvegas_sucesor_no_set << "\t\t\t";
	std::cout << iteraciones_promedio_sucesor_no_set << std::endl;
	std::cout << "\tVegas_suc_set\t\t" << nodos_promedio_lasvegas_sucesor_set << "\t\t\t";
	std::cout << iteraciones_promedio_sucesor_set << std::endl;
	std::cout << "-----------------------------------------------------------------------" << std::endl;
	std::cout << std::endl;
}
