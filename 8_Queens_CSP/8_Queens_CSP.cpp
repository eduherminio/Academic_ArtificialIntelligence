#include "header/reinas.h"
#include "header/problema_csp.h"
#include "header/cronometro.h"

const int n_reinas = 8;

int main()
{
	reinas::Reinas reinas(n_reinas);
	Cronometro<std::milli> crono;

	crono.inicio();

	// if(reinas.resolver(csp::Seleccion_variable::estatica, csp::Algoritmo::bt))
	// if(reinas.resolver(csp::Seleccion_variable::aleatoria, csp::Algoritmo::bt))
	if (reinas.resolver(csp::Seleccion_variable::estatica, csp::Algoritmo::fc))
		// if(reinas.resolver())                                                        // same as above, due to default parameters of bool resolver()
		// if(reinas.resolver(csp::Seleccion_variable::aleatoria, csp::Algoritmo::fc))
	{
		std::cout << "\nSolution:" << std::endl;
		reinas::imprime_solucion(reinas.get_solucion());
		std::cout << "\nVisited nodes= " << reinas.get_nodos_expandidos() << std::endl;
	}

	crono.fin();

	std::cout << "Spent time:: " << crono << " ms.\n" << std::endl;

	return 0;
}
