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
  bool bloqueo= false;
  std::cout<<"Actualiza dominio "<<assigned_queen<<" "<<assigned_value<<std::endl;
  for(auto& fila_1 : variables_sin_etiquetar) //int para fil y col para no tener problemas al restar en funcion abs()
  {
    // fila = unassigned_queen
    // col= val_dom
    if(fila_1 != assigned_queen)  // needed?
    {
      for(auto& fila_2 : variables_sin_etiquetar)
      {
        std::cout<<fila_1<<"vs"<<fila_2<<std::endl;
        if((fila_2 != assigned_queen) && relacionadas(fila_1, fila_2))    // Nota: comprobar sólo para reinas relacionadas (en este caso es indiferente, porque todas lo están, pero no será así en el sudoku)
        {
          if(dominio[fila_1].empty() == true || dominio[fila_2].empty() == true)
          {
            std::cout<<"return true"<<std::endl;
            return true;
          }
          for(int iter_dom_1=0; iter_dom_1<dominio[fila_1].size(); ++iter_dom_1)     // Cada casilla 'libre' de una fila
          {
            for(int iter_dom_2=0; iter_dom_2<dominio[fila_2].size(); ++iter_dom_2)   // Cada casilla 'libre' de otra fila
            {
              if( (dominio[fila_1][iter_dom_1] != assigned_value) && (dominio[fila_2][iter_dom_2] != assigned_value) && (consistente(fila_1, dominio[fila_1][iter_dom_1], fila_2, dominio[fila_2][iter_dom_2]) == true) )
              {
                std::cout<<"break"<<std::endl;
                break;
              }
              else  // inconsistente: TO-CHECK
              {
                auto it= dominio[fila_1].begin() + iter_dom_1;
                *it= std::move(dominio[fila_1].back());
                dominio[assigned_queen].pop_back();
                lista_exclusiones_dominio[assigned_queen].push_back(std::make_pair(fila_1,iter_dom_1));
              }
            }
          }
        }
      }
    }

    std::cout<<"***************"<<std::endl;
    imprime_dominio();

  }
  return false;

  // ver reinas::funcion relacionadas (en este caso, todas)
  // en el caso del sudoku, por ejemplo, devolvera true si están en el mismo cuadrado, fila o columna

  // ver reinas::funcion consistente
  // SI NO SON CONSISTENTES, LISTA DE EXCLUSIONES -> PUSH_BACK
}

#endif // CSP_FC_H_INCLUDED
