#ifndef CSP_FC_H_INCLUDED
#define CSP_FC_H_INCLUDED

//Actualiza dominio Forward Checking
template<typename T>
bool Problema_csp<T>::actualiza_dominio_fc(const std::pair<unsigned, T> &asignacion)
{
  // TO-DO
  // DONE

  auto assigned_queen= asignacion.first;
  auto assigned_value= asignacion.second;

  // Quitamos assigned_value del dominio del resto de reinas
  std::cout<<"Dominio teniendo en cuenta la asignación {"<<assigned_queen<<","<<assigned_value<<"}"<<std::endl;
  // dominio[assigned_queen].clear();
  // dominio[assigned_queen].push_back(assigned_value);
  for(const auto& queen : variables_sin_etiquetar)
  {
    if(relacionadas(assigned_queen, queen))
    {
      for(int val=0; val<dominio[queen].size(); ++val)
      {
        if( (dominio[queen][val] ==   assigned_value) ||
            (dominio[queen][val] ==  (assigned_value + abs(assigned_queen - queen))) ||
            (dominio[queen][val] ==  (assigned_value - abs(assigned_queen - queen)))
          )
        {
          lista_exclusiones_dominio[assigned_queen].push_back(std::make_pair(queen, dominio[queen][val]));
                // std::cout<<"##"<<queen<<" "<<val<<std::endl;
          auto it= dominio[queen].begin() + val;
          *it= std::move(dominio[queen].back());
          dominio[queen].pop_back();
                // imprime_dominio();
                // imprime_lista_exclusiones_dominio();
          val--; // Chceck again that position, since there's a new valor
        }
      }
    }
  }

  imprime_dominio();
  imprime_lista_exclusiones_dominio();

  // Forward checking: comparamos consistencia de las variables no asignadas
  bool bloqueo= false;
  // for(auto& fila_1 : variables_sin_etiquetar) //int para fil y col para no tener problemas al restar en funcion abs()
  for(int queen =0; queen<variables_sin_etiquetar.size(); ++queen)
  {
    auto fila_1= variables_sin_etiquetar[queen];
    for(auto& fila_2 : variables_sin_etiquetar)
    {
      if(fila_1==fila_2)
        continue;

      // std::cout<<std::endl<<fila_1<<"vs"<<fila_2<<std::endl;
      if(relacionadas(fila_1, fila_2))    // Nota: comprobar sólo para reinas relacionadas (en este caso es indiferente, porque todas lo están, pero no será así en el sudoku)
      {
        if(dominio[fila_1].empty() == true || dominio[fila_2].empty() == true)
        {
                  std::cout<<"return true"<<std::endl;
          return true;
        }
        // for(const auto val_dom_1 : dominio[fila_1])
        for(int val_1=0; val_1<dominio[fila_1].size(); ++val_1)
        {
          auto val_dom_1= dominio[fila_1][val_1];
          bool bloqueo= true;
          for(const auto val_dom_2: dominio[fila_2])
          {
            if(consistente(fila_1, val_dom_1, fila_2, val_dom_2) == true)
            {
                    // std::cout<< "["<<fila_1<<","<<val_dom_1<<"] y ["<<fila_2<<","<<val_dom_2<<"] son consistentes"<<std::endl;
              bloqueo= false;
              break;
            }
            // else
            //         std::cout<< "["<<fila_1<<","<<val_dom_1<<"] y ["<<fila_2<<","<<val_dom_2<<"] *NO* son consistentes"<<std::endl;
          }
          if(bloqueo==true)
          {
                    std::cout<< "["<<fila_1<<","<<val_dom_1<<"] y ["<<fila_2<<","<<"*"<<"] -> bloqueo"<<std::endl;
            lista_exclusiones_dominio[assigned_queen].push_back(std::make_pair(fila_1, val_dom_1));

            // auto it= dominio[assigned_queen].begin() + val_dom_1;
            // *it= std::move(dominio[assigned_queen].back());
            // dominio[assigned_queen].pop_back();
            auto it= dominio[fila_1].begin() + val_1;
            *it= std::move(dominio[fila_1].back());
                  std::cout<<dominio[fila_1].back()<<*it<<std::endl;
            dominio[fila_1].pop_back();
            imprime_lista_exclusiones_dominio();
            return true;

          }
        }
      }
    }
    //
    // std::cout<<"***************"<<std::endl;
    // imprime_dominio();

  }
  return false;

  // ver reinas::funcion relacionadas (en este caso, todas)
  // en el caso del sudoku, por ejemplo, devolvera true si están en el mismo cuadrado, fila o columna

  // ver reinas::funcion consistente
  // SI NO SON CONSISTENTES, LISTA DE EXCLUSIONES -> PUSH_BACK
}

#endif // CSP_FC_H_INCLUDED
