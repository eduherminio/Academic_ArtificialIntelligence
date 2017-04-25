#ifndef CSP_SELECCION_VARIABLE_H_INCLUDED
#define CSP_SELECCION_VARIABLE_H_INCLUDED

template <typename T>
void Problema_csp<T>::tipo_seleccion_variable(const csp::Seleccion_variable sel_var)
{
  switch(sel_var)
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
  std::uniform_int_distribution<unsigned>aleatorio(0,variables_sin_etiquetar.size()-1);
  //TO-DO
  //Colocamos la variable seleccionada al final del vector
  //para su f�cil bloqueo o liberaci�n
  //Completar
  //return(variable);
}
template <typename T>
unsigned Problema_csp<T>::seleccion_variable_mrv()
{
  //Completar
  // TO-DO: La que tenga menor dominio

  //Colocamos la variable seleccionada al final del vector
  //para su f�cil bloqueo o liberaci�n

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
