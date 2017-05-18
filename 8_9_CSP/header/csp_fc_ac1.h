#ifndef CSP_AC1_H_INCLUDED
#define CSP_AC1_H_INCLUDED

template <typename T>
bool Problema_csp<T>::actualiza_dominio_fc_ac1(const std::pair<unsigned,T>& asignacion)
{
  bool bloqueo= actualiza_dominio_fc(asignacion);
  if(!bloqueo)  //Consistencia de arco ac-1 en variables sin asignar
    bloqueo= actualiza_dominio_ac1(asignacion.first);
  return bloqueo;
}

//Actualiza dominios de variables sin asignar entre si: algoritmo AC-1
template <typename T>
bool Problema_csp<T>::actualiza_dominio_ac1(const unsigned variable)
{
  bool cambio= true;
  while(cambio)
  {
    cambio= false;
    for(const auto& var_i:variables_sin_etiquetar)
    {
      for(const auto& var_j:variables_sin_etiquetar)
      {
        if(var_i!=var_j && relacionadas(var_i, var_j))
        {
          if(revisar_ac1(variable, var_i, var_j))
          {
            cambio= true; // repetir el doble bucle for, al haber alteración del dominio de la variable. Parte que AC3 mejora
            if(dominio[var_i].empty())
            {
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}

template <typename T>
bool Problema_csp<T>::revisar_ac1(const unsigned variable, const unsigned var_i, const unsigned var_j)
{
  // DONE


  bool cambio=false;

  for(int i=0; i<dominio[var_i].size(); ++i)
  {
    auto dom_i= dominio[var_i][i];
    bool consistency= false;
    for(const auto& dom_j : dominio[var_j])
    {
      if(consistente(var_i, var_j, dom_i, dom_j)==true)
      {
        consistency= true;
        break;
      }
    }

    if(consistency== false)
    {
      lista_exclusiones_dominio[variable].push_back({var_i, dom_i});
      dominio[var_i][i]=dominio[var_i].back();

      // auto it= dominio[var_i].begin() + i;
      // *it= std::move(dominio[var_i].back());
      dominio[var_i].pop_back();

      cambio= true;
      --i;
    }
  }

  return cambio;
}
#endif // CSP_AC1_H_INCLUDED
