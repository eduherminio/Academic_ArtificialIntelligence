#ifndef BB_SELECCION_VARIABLE_H_INCLUDED
#define BB_SELECCION_VARIABLE_H_INCLUDED

template <typename T>
void Problema_bb<T>::tipo_seleccion_variable(const bb::Seleccion_variable sel_var)
{
  switch(sel_var)
  {
    case Seleccion_variable::estatica:
      ordenacion_estatica_variables_ad_hoc();     // Cada problema ordenará las variables como considere
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
  }
}



template <typename T>
unsigned Problema_bb<T>::seleccion_variable_estatica()
{
  return(variables_sin_etiquetar.back());
}

template <typename T>
unsigned Problema_bb<T>::seleccion_variable_aleatoria()
{
  std::uniform_int_distribution<unsigned>aleatorio(0, variables_sin_etiquetar.size()-1);
  auto indice= aleatorio(rng);
  //Colocamos la variable seleccionada al final del vector
  //para su f�cil bloqueo o liberaci�n
  auto variable= variables_sin_etiquetar[indice];
  variables_sin_etiquetar[indice]= variables_sin_etiquetar.back();
  variables_sin_etiquetar.back()= variable;
  return(variable);
}

template <typename T>
unsigned Problema_bb<T>::seleccion_variable_mrv()
{
  auto minimo=dominio[variables_sin_etiquetar[0]].size();
  auto indice=0;

  for(size_t i=1; i!=variables_sin_etiquetar.size(); ++i)
  {
    if(dominio[variables_sin_etiquetar[i]].size() < minimo)
    {
      indice= i;
      minimo= dominio[variables_sin_etiquetar[i]].size();
    }
  }
  //Colocamos la variable seleccionada al final del vector
  //para su f�cil bloqueo o liberaci�n
  auto variable= variables_sin_etiquetar[indice];
  variables_sin_etiquetar[indice]= variables_sin_etiquetar.back();
  variables_sin_etiquetar.back()= variable;

  return(variable);
}

template <typename T>
void Problema_bb<T>::bloquea_variable()
{
  variables_sin_etiquetar.pop_back();
}

template <typename T>
void Problema_bb<T>::libera_variable(const unsigned variable)
{
  variables_sin_etiquetar.push_back(variable);
}

#endif // CSP_SELECCION_VARIABLE_ALGORITMO_H_INCLUDED
