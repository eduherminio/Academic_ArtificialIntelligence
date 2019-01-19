#ifndef CSP_SELECCION_VARIABLE_H_INCLUDED
#define CSP_SELECCION_VARIABLE_H_INCLUDED

template <typename T>
void Problema_csp<T>::tipo_seleccion_variable(const csp::Seleccion_variable sel_var)
{
	switch (sel_var)
	{
	case Seleccion_variable::estatica:
		seleccion_variable = [this]() -> unsigned
		{
			return(seleccion_variable_estatica());
		};
		break;
	case Seleccion_variable::aleatoria:
		seleccion_variable = [this]() -> unsigned
		{
			return(seleccion_variable_aleatoria());
		};
		break;
	case Seleccion_variable::mrv:
		seleccion_variable = [this]() -> unsigned
		{
			return(seleccion_variable_mrv());
		};
		break;
	default:
		assert(false && "Tipo de seleccion de variable no implementado");
		break;
	}
}

template <typename T>
unsigned Problema_csp<T>::seleccion_variable_estatica()
{
	return(variables_sin_etiquetar.back());
}

template <typename T>
unsigned Problema_csp<T>::seleccion_variable_aleatoria()
{
	// DONE

	// fast erase: now variables_sin_etiquetar is ready for a pop_back(), later in Problema_csp<T>::bloquea_variable()
	std::uniform_int_distribution<unsigned> aleatorio(0, variables_sin_etiquetar.size() - 1);

	// std::iter_swap(variables_sin_etiquetar.begin() + aleatorio(rng), variables_sin_etiquetar.end() - 1);
	// return variables_sin_etiquetar.back();

	// Note: providing the selected element isn't used within the vector any more (which makes sense, due to it's already returned), a swap isn't needed
	auto it = variables_sin_etiquetar.begin() + aleatorio(rng);
	const auto return_var = *it;
	*it = std::move(variables_sin_etiquetar.back());

	return return_var;
}

template <typename T>
unsigned Problema_csp<T>::seleccion_variable_mrv()
{
	// DONE

	// Order decreasingly by dominio
	// Colocamos la variable seleccionada al final del vector
	// para su fácil bloqueo o liberación

	// for(int var=0; var<variables_sin_etiquetar.size(); ++var)
	//   if(var==0 || (var!=0 && static_cast<int> (dominio[variables_sin_etiquetar[var]].size()) != static_cast<int>(dominio[variables_sin_etiquetar[var-1]].size())))
	//     std::cout<<variables_sin_etiquetar[var]<<"("<<dominio[variables_sin_etiquetar[var]].size()<<") ";
	// std::cout<<std::endl;

	std::sort(variables_sin_etiquetar.begin(), variables_sin_etiquetar.end(), [this](const unsigned a, const unsigned b) -> bool
	{
		return dominio[a].size() > dominio[b].size();
	});

	// std::cout<<"Sorted:"<<std::endl;
	// for(int var=0; var<variables_sin_etiquetar.size(); ++var)
	//   if(var==0 || (var!=0 && static_cast<int> (dominio[variables_sin_etiquetar[var]].size()) != static_cast<int>(dominio[variables_sin_etiquetar[var-1]].size())))
	//     std::cout<<variables_sin_etiquetar[var]<<"("<<dominio[variables_sin_etiquetar[var]].size()<<") ";
	// std::cout<<std::endl<<std::endl<<std::endl;

	return variables_sin_etiquetar.back();
}

template <typename T>
void Problema_csp<T>::bloquea_variable()
{
	variables_sin_etiquetar.pop_back();
}

template <typename T>
void Problema_csp<T>::libera_variable(const unsigned variable)
{
	variables_sin_etiquetar.push_back(variable);
}

#endif // CSP_SELECCION_VARIABLE_ALGORITMO_H_INCLUDED
