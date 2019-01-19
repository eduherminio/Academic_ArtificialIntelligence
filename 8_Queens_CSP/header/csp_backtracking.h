#ifndef CSP_BACKTRACKING_H_INCLUDED
#define CSP_BACKTRACKING_H_INCLUDED

template <typename T>
bool Problema_csp<T>::backtracking()
{
	inicializa();

	bool exito = false;
	nodos_expandidos = 0;

	std::vector<std::pair<unsigned, T>> lista_asignaciones;

	while (!exito)
	{
		++nodos_expandidos;
		auto variable = seleccion_variable();

		if (!expandir_bt(variable, lista_asignaciones))    // no free squares for this queen
		{
			if (lista_asignaciones.empty())  // No solution
				break;
			else
			{
				bool eliminar = true;
				while (eliminar)
				{
					if (solucion.back().first == lista_asignaciones.back().first)  // pop(solucion) hasta llegar a una posible reasignación de la última reina que se ha podido asignar
						eliminar = false;
					restaura_estado(solucion.back());                                                 // Actualiza los sets, sacando la casilla ocupada
					libera_variable(solucion.back().first); // variables_sin_etiquetar.push_back(var) // vuelve a dejar disponible la variable
					solucion.pop_back();
				}
			}
		}

		solucion.push_back(lista_asignaciones.back());  // Tenemos nuevo nodo disponible

		bloquea_variable(); // variables_sin_etiquetar.pop_back();  // seleccion_variable() ha empujado previamente la variable seleccionada al final del vector

		if (variables_sin_etiquetar.empty())
			exito = true;
		else
		{
			actualiza_estado(solucion.back());  // Actualiza los sets, introduciendo la casilla ocupada
			lista_asignaciones.pop_back();     //Eliminamos la asignacion de la lista
		}
	}
	return exito;
}

template <typename T>
bool Problema_csp<T>::expandir_bt(const unsigned variable, std::vector<std::pair<unsigned, T>>& lista_asignaciones)
{
	auto tam = lista_asignaciones.size();

	for (auto valor : dominio[variable])
	{
		if (consistente(variable, valor))   // Different function for every type of problem
		{
			lista_asignaciones.push_back({ variable, valor });
		}
	}

	return(tam != lista_asignaciones.size());  // True if nodes added
}

#endif // CSP_BACKTRACKING_H_INCLUDED
