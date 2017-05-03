#ifndef CSP_FC_H_INCLUDED
#define CSP_FC_H_INCLUDED

//Actualiza dominio Forward Checking
template<typename T>
bool Problema_csp<T>::actualiza_dominio_fc(const std::pair<unsigned,T> &asignacion)
{
  auto variable_asignada= asignacion.first;
  auto valor_asignado= asignacion.second;
  for(auto variable_sin_asignar : variables_sin_etiquetar) //int para fil y col para no tener problemas al restar en funcion abs()
  {
    if(!dominio[variable_sin_asignar].size())
      return true;

    if(relacionadas(variable_asignada, variable_sin_asignar))
    {
      for(int iter_dom=0; iter_dom<dominio[variable_sin_asignar].size(); ++iter_dom)
      {
        if(valor_asignado == dominio[variable_sin_asignar][iter_dom] && consistente(variable_asignada, valor_asignado)== true);
        {
          lista_exclusiones_dominio[variable_asignada].push_back(std::make_pair(variable_sin_asignar, dominio[variable_sin_asignar][iter_dom]));

          auto it= dominio[variable_sin_asignar].begin() + iter_dom;
          *it= std::move(dominio[variable_sin_asignar].back());
          dominio[variable_sin_asignar].pop_back();
          iter_dom--;
          if(!dominio[variable_sin_asignar].size())
            return true;
        }
      }
    }
  }
  return false;
}

#endif // CSP_FC_H_INCLUDED
