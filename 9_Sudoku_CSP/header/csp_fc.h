#ifndef CSP_FC_H_INCLUDED
#define CSP_FC_H_INCLUDED

//Actualiza dominio Forward Checking
template<typename T>
bool Problema_csp<T>::actualiza_dominio_fc(const std::pair<unsigned, T> &asignacion)
{
  // DONE

  auto assigned_queen= asignacion.first;
  auto assigned_value= asignacion.second;

  for(const auto& queen : variables_sin_etiquetar)
  {
    if(relacionadas(assigned_queen, queen))
    {
      for(int val=0; val<dominio[queen].size(); ++val)
      {
        auto queen_value= dominio[queen][val];
        if(consistente(assigned_queen, assigned_value, queen, queen_value) == false)
        {
          lista_exclusiones_dominio[assigned_queen].push_back(std::make_pair(queen, queen_value));

          auto it= dominio[queen].begin() + val;  // Fast deletion method
          *it= std::move(dominio[queen].back());
          dominio[queen].pop_back();

          --val; // Check again that position, since there's a new valor
        }
      }
      if(dominio[queen].empty())
        return true;
    }
  }

  return false;
}

#endif // CSP_FC_H_INCLUDED
