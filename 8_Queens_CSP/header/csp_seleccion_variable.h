#ifndef CSP_SELECCION_VARIABLE_H_INCLUDED
#define CSP_SELECCION_VARIABLE_H_INCLUDED

template <typename T>
void Problema_csp<T>::tipo_seleccion_variable(const csp::Seleccion_variable sel_var)
{
  switch(sel_var)
  {
    // seleccion_variable is a pointer to function, defined in problema_csp
    // Here we use lambdas functions to define those functions to whom selecion_variable can point here:
    // seleccion_variable = [this]() -> unsigned
    // [this]:        variable capture: variables declared outside the lambda which needs to be used inside of it
    // ()_:           parameters, as a normal function
    // -> unsigned    new return value sintax: auto foo() -> return type
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
    default:
      assert(false && "Variable selection type not implemented");
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
  auto it= variables_sin_etiquetar.begin() + aleatorio(rng);
  const auto return_var= *it;
  *it= std::move(variables_sin_etiquetar.back());

  return return_var;
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
