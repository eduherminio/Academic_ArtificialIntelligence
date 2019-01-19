#ifndef OBSERVADOR_H_INCLUDED
#define OBSERVADOR_H_INCLUDED

#include <functional>  // for std::function
#include <utility>     // for std::forward and std::move
#include <map>
#include <vector>

template <typename Evento>
class Observador
{
public:
	//////////////////  OBSERVADOR ///////////////////////////////////////////////
	template <typename Funcion>
	void registra_observador(const Evento& evento, const Funcion& observador)
	{
		lista_observadores[evento].push_back(observador);
	}

	void notifica(const Evento& evento) const
	{
		for (const auto& obs : lista_observadores.at(evento))
			obs();
	}
	//////////////////////////////////////////////////////////////////////////////

private:
	std::map<Evento, std::vector<std::function<void()>>> lista_observadores;
};


#endif // OBSERVADOR_H_INCLUDED
