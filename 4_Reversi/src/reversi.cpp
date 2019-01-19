#include "../header/reversi.h"
#include <cstddef>
#include <iostream>
#include <assert.h>

void Reversi::inicializar()
{
	for (unsigned i = 0; i < filas; i++)
	{
		for (unsigned j = 0; j < columnas; j++)
		{
			posicion.set_tablero(i, j, Turno::vacia);
		}
	}
	posicion.set_tablero((filas / 2) - 1, (columnas / 2) - 1, Turno::humano);
	posicion.set_tablero((filas / 2), (columnas / 2), Turno::humano);
	posicion.set_tablero((filas / 2) - 1, (columnas / 2), Turno::ordenador);
	posicion.set_tablero((filas / 2), (columnas / 2) - 1, Turno::ordenador);
	posicion.set_turno(Turno::humano);
	posicion.set_pasa(Tipo_tablero::no_pasa);
	jugadas_validas_humano = posicion.calcula_jugadas();
	heuristica = 0;

	algoritmo = Algoritmo::alpha_beta;

	// TO-CHECK
	profundidad_maxima = 11;
}
void Reversi::ejecuta_movimiento(const unsigned fil, const unsigned col)
{
	auto jugadas_validas = posicion.calcula_jugadas();
	if (!jugadas_validas.empty())
	{
		if (turno_humano())
		{
			for (auto &jugada : jugadas_validas)
			{
				if (jugada.x == fil && jugada.y == col) //La casilla (fil,col)es una de las jugadas validas
				{
					posicion.actualiza_tablero(jugada);
					posicion.set_turno(Turno::ordenador);
					posicion.set_pasa(Tipo_tablero::no_pasa);
				}
			}
		}
		else
		{
			for (auto &jugada : jugadas_validas)
			{
				if (jugada.x == fil && jugada.y == col) //La casilla (fil,col)es una de las jugadas validas
				{
					posicion.actualiza_tablero(jugada);
					posicion.set_turno(Turno::humano);
					posicion.set_pasa(Tipo_tablero::no_pasa);
				}
			}
		}
	}
	else
	{
		if (posicion.get_pasa() == Tipo_tablero::no_pasa)
		{
			posicion.set_pasa(Tipo_tablero::pasa);
			if (turno_humano())
				posicion.set_turno(Turno::humano);
			else
				posicion.set_turno(Turno::ordenador);
		}
		else
		{
			posicion.set_pasa(Tipo_tablero::terminal);
		}
	}
}
void Reversi::ejecuta_movimiento()
{
	do
	{
		if (algoritmo == Algoritmo::minimax)
		{
			heuristica = estrategia_minimax();
		}
		else if (algoritmo == Algoritmo::alpha_beta)
		{
			heuristica = estrategia_alpha_beta();
		}
		posicion.set_turno(Turno::humano);
		jugadas_validas_humano = posicion.calcula_jugadas();
		if (!jugadas_validas_humano.size())                        //Tablero en pasa para humano
		{
			if (posicion.get_pasa() == Tipo_tablero::no_pasa)
			{
				posicion.set_pasa(Tipo_tablero::pasa);
				posicion.set_turno(Turno::ordenador);
			}
			else
			{
				posicion.set_pasa(Tipo_tablero::terminal);
			}
		}
	} while (turno_ordenador());
}



int Reversi::estrategia_alpha_beta()
{
	// TO-DO: Correct algorithm
	std::vector<Nodo_reversi_alpha_beta> lista;

	Nodo_reversi_alpha_beta nodo_inicial(posicion);
	nodo_inicial.set_nodo_inicial();
	lista.push_back(nodo_inicial);

	lista.back().set_alpha(-10);
	lista.back().set_beta(+10);

	auto valor_alpha = lista.front().get_alpha();  // debugging purposes
	auto valor_beta = lista.front().get_beta();

	while (!lista.empty())
	{
		// std::cout<<"Nueva iter:"<<std::endl;

		//auto nodo_actual= lista.back(); // puede ser tentador, pero sólo sería válido para leer y no para sobrescribir el nodo.
		int pos_padre = lista.back().get_padre();

		// if(pos_padre>-1){
		//   std::cout<<"-Nodo: " <<lista.size()-1 << "("<<pos_padre<<")"<<"\t\tAlpha: "<<lista.back().get_alpha()<<"\tBeta: "<<lista.back().get_beta()<<std::endl;
		//   std::cout<<"-Padre: "<<pos_padre<<"\t\tAlpha: "<<lista.at(pos_padre).get_alpha()<<"\tBeta: "<<lista.at(pos_padre).get_beta()<<std::endl;
		// }
		//
		// else
		//   std::cout<<"- Nodo: " <<lista.size()-1<<" ("<<pos_padre<<")"<<"\t\tAlpha: "<<lista.back().get_alpha()<<"\tBeta: "<<lista.back().get_beta()<<std::endl;

		if (!lista.back().get_visitado())    // No visitado, lo VISITAMOS
		{
			// std::cout<<"no visitado"<<std::endl;
			lista.back().set_visitado();

			if (lista.back().get_pasa() == Tipo_tablero::terminal)
			{             // Posicion terminal: pasan los dos
				lista.back().set_alpha_o_beta(lista.back().evalua_posicion(true));
				// std::cout<<"Terminal"<<std::endl;
				// std::cout<<"Nodo:\t\tAlpha: "<<lista.back().get_alpha()<<"\tBeta: "<<lista.back().get_beta()<<std::endl;
			}
			else if (lista.back().get_profundidad() == profundidad_maxima)
			{     // Suspension
				lista.back().set_alpha_o_beta(lista.back().evalua_posicion(false));
				// std::cout<<"Suspensión"<<std::endl;
				// std::cout<<"Nodo:\t\tAlpha: "<<lista.back().get_alpha()<<"\tBeta: "<<lista.back().get_beta()<<std::endl;
				// if(lista.back().get_turno()==Turno::ordenador)
				//   std::cout<<"MIN"<<std::endl;
				// else
				//   std::cout<<"MAX"<<std::endl;
			}
			else
			{
				if (pos_padre > 0)
				{
					lista.back().set_alpha(lista.at(pos_padre).get_alpha());
					lista.back().set_beta(lista.at(pos_padre).get_beta());
				}
				else
				{
					// std::cout<<"primeros hijos"<<std::endl;
					lista.back().set_alpha(lista.front().get_alpha());
					lista.back().set_beta(lista.front().get_beta());
				}
				// Parece mentira, pero cuando un nodo pasa por aquí, es porque ya se han expandido (que no visitado) todos sus nodos hermanos,
				// por lo que ya se ha actualizado su padre y el valor que adquiere el alpha y el beta del nodo es el último calculado (heredado del padre)

				auto tam_lista = lista.size();
				// auto alpha_actual= lista.back().get_alpha();
				// auto beta_actual= lista.back().get_beta();

				for (auto& hijo : lista.back().expandir())
				{
					hijo.set_padre(tam_lista - 1);
					hijo.set_alpha(lista.at(tam_lista - 1).get_alpha());
					hijo.set_beta(lista.at(tam_lista - 1).get_beta());

					lista.push_back(hijo);
				}

				// std::cout<<"Nodo: " <<tam_lista-1<<"\t\tAlpha: "<<lista.at(tam_lista-1).get_alpha()<<"\tBeta: "<<lista.at(tam_lista-1).get_beta()<<std::endl;
			}
		}

		else     // Nodo ya visitado, lo EXPANDIMOS
		{
			// std::cout<<"visitado"<<std::endl;
			bool poda = false;
			// if(lista.back().get_turno()==Turno::ordenador)
			//   std::cout<<"turno ordenador: "<<lista.back().get_alpha()<<" "<<lista.back().get_beta()<<std::endl;
			// else
			//   std::cout<<"turno humano: "<<lista.back().get_alpha()<<" "<<lista.back().get_beta()<<std::endl;

			if (pos_padre >= 0)
			{
				// if(lista.back().get_turno()==Turno::ordenador)
				//   std::cout<<"\nMIN"<<std::endl;
				// else
				//   std::cout<<"\nMAX"<<std::endl;
				//
				// std::cout<<"Padre:\t\tAlpha: "<<lista.at(pos_padre).get_alpha()<<"\tBeta: "<<lista.at(pos_padre).get_beta()<<std::endl;
				// std::cout<<"Nodo:\t\tAlpha: "<<lista.back().get_alpha()<<"\tBeta: "<<lista.back().get_beta()<<std::endl;

				if (lista.back().get_turno() == Turno::ordenador)
				{                     // Ordenador: nodo MIN
					if (lista.back().get_beta() > lista.at(pos_padre).get_alpha())
					{     // Poda
						if (lista.at(pos_padre).get_beta() <= lista.back().get_beta())
						{
							poda = true;
						}
						else
						{                                                               // No poda: actualizamos padre
							lista.at(pos_padre).set_alpha(lista.back().get_beta());
							// lista.at(pos_padre).set_alpha_o_beta(lista.back().get_beta());
						}
					}
				}
				else
				{                                                              // Humano:    nodo MAX

					if (lista.back().get_alpha() < lista.at(pos_padre).get_beta())
					{        // Poda
						if (lista.back().get_alpha() <= lista.at(pos_padre).get_alpha())
						{  // futuro beta del padre <= alpha del padre
							poda = true;
						}
						else
						{                                                               // No poda: actualizamos padre
							lista.at(pos_padre).set_beta(lista.back().get_alpha());
							// lista.at(pos_padre).set_alpha_o_beta(lista.back().get_alpha());

						}

						if (pos_padre == 0)
						{  //Mejoramos la puntuacion del nodo raiz
							std::cout << "\nNodo raiz: " << lista.back().get_alpha() << " " << lista.back().get_beta() << std::endl;
							posicion.set_tablero(lista.back().get_tablero());
							posicion.set_pasa(lista.back().get_pasa());

							valor_alpha = lista.back().get_alpha(); // debugging purposes
							valor_beta = lista.back().get_beta(); // debugging purposes
						}
					}
				}
				// std::cout<<"Nuevo padre:\tAlpha: "<<lista.at(pos_padre).get_alpha()<<"\tBeta: "<<lista.at(pos_padre).get_beta()<<std::endl;
			}


			if (poda == true)
			{
				// std::cout<<"Poda"<<std::endl;
				while ((lista.size() - 1 != pos_padre) && lista.size())
				{      // Eliminamos nodos hasta que el último de la lista sea el padre
					lista.pop_back();
				}
				assert(lista.back().get_padre() == lista.at(pos_padre).get_padre());
				//  lista.resize(pos_padre+1);    // No es posible
			}
			else
			{
				lista.pop_back();                                             // Eliminamos el nodo actual
			}
		}
		//std::cout<<" -> "<<lista.back().get_alpha()<<" "<<lista.back().get_beta()<<std::endl;

	}

	std::cout << valor_alpha << " " << valor_beta << std::endl;

	return(valor_alpha);  // sirve para visualizar en la consola
}

int Reversi::estrategia_minimax()
{
	std::vector<Nodo_reversi_minimax> lista;

	Nodo_reversi_minimax nodo_inicial(posicion);
	nodo_inicial.set_nodo_inicial();
	lista.push_back(nodo_inicial);

	auto valor_minimax = lista[0].get_minimax(); //valor final para MAX

	while (!lista.empty())
	{
		if (!lista.back().get_visitado())
		{
			lista.back().set_visitado();
			if (lista.back().get_pasa() == Tipo_tablero::terminal)  //Posicion terminal: pasan los dos
			{
				lista.back().set_minimax(lista.back().evalua_posicion(true));
			}
			else if (lista.back().get_profundidad() == profundidad_maxima)  //Suspension
			{
				lista.back().set_minimax(lista.back().evalua_posicion(false));
			}
			else
			{
				auto tam_lista = lista.size();
				auto minimax_actual = lista.back().get_minimax();
				for (auto &hijo : lista.back().expandir())
				{
					hijo.set_padre(tam_lista - 1);
					hijo.set_minimax(-minimax_actual);
					lista.push_back(hijo);
				}
			}
		}
		else     // TO-CHECK: visitado?
		{
			//          actualiza minimax padre
			auto padre = lista.back().get_padre();
			if (padre >= 0)
			{
				auto minimax_hijo = lista.back().get_minimax();
				auto minimax_padre = lista[padre].get_minimax();

				if (lista.back().get_turno() == Turno::ordenador) //El padre es humano: nodo MIN
				{
					if (minimax_hijo < minimax_padre)
					{
						lista[padre].set_minimax(minimax_hijo);
					}
				}

				else  //El padre es ordenador: nodo MAX
				{
					if (minimax_hijo > minimax_padre)
					{
						lista[padre].set_minimax(minimax_hijo);
						if (padre == 0) //Mejoramos la puntuacion del nodo raiz
						{
							posicion.set_tablero(lista.back().get_tablero());
							posicion.set_pasa(lista.back().get_pasa());
							valor_minimax = minimax_hijo;
						}
					}
				}
			}
			lista.pop_back();  //Eliminamos el nodo actual
		}
	}
	return(valor_minimax);
}
