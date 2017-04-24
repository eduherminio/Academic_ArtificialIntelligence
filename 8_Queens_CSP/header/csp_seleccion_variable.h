#ifndef CSP_SELECCION_VARIABLE_H_INCLUDED
#define CSP_SELECCION_VARIABLE_H_INCLUDED

template <typename T>
void Problema_csp<T>::tipo_seleccion_variable(const csp::Seleccion_variable sel_var)
{
  switch(sel_var)
  {
    case Seleccion_variable::estatica:
    seleccion_variable = [this]() -> unsigned   // TO-DO: Funcion lambda para definir aqui la funcion.
    // Entre corchetes, las variables que queremos sean accesibles desde dentro (el this nos permite acceder a todas las variables miembro)
    // Entre paréntesis, argumentos. La flecha: nueva manera de hacer un return:
    // auto funcion() -> variable_retornada
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
  std::uniform_int_distribution<unsigned>aleatorio(0,variables_sin_etiquetar.size()-1);
  unsigned selection= aleatorio(rng);
  std::iter_swap(variables_sin_etiquetar.begin()+selection, variables_sin_etiquetar.end()-1);

  return variables_sin_etiquetar.back();    //variables_sin_etiquetar[selection];
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
