#ifndef CSP_FC_H_INCLUDED
#define CSP_FC_H_INCLUDED

//Actualiza dominio Forward Checking
template<typename T>
bool Problema_csp<T>::actualiza_dominio_fc(const std::pair<unsigned,T> &asignacion)
{
  auto var_1=asignacion.first;
  auto val_1=asignacion.second;
  for(auto var_2:variables_sin_etiquetar) //int para fil y col para no tener problemas al restar en funcion abs()
  {
    //Completar
  }
  return false;
}

#endif // CSP_FC_H_INCLUDED
