#ifndef CSP_BACKTRACKING_H_INCLUDED
#define CSP_BACKTRACKING_H_INCLUDED

template <typename T>
bool Problema_csp<T>::backtracking()
{
  inicializa();

  bool exito=false;
  nodos_expandidos=0;

  std::vector<std::pair<unsigned,T>>lista_asignaciones;
  while(!exito)
  {
    ++nodos_expandidos;
    auto variable=seleccion_variable();

    if(!expandir_bt(variable,lista_asignaciones))
    {
      if(lista_asignaciones.empty())
      {
        break;  //No hay solucion
      }
      else
      {
        bool eliminar=true;
        while(eliminar)
        {
          if(solucion.back().first==lista_asignaciones.back().first)
          eliminar=false;
          restaura_estado(solucion.back());
          libera_variable(solucion.back().first); //Liberamos al final del vector variables_sin_etiquetar
          solucion.pop_back();

        }
      }
    }
    solucion.push_back(lista_asignaciones.back());  //Tenemos nuevo nodo disponible

    bloquea_variable();  //La variable seleccionada siempre es la ultima del vector variables_sin_etiquetar
    if(variables_sin_etiquetar.empty())
    {
      exito=true;
    }
    else
    {
      actualiza_estado(solucion.back());
      lista_asignaciones.pop_back();     //Eliminamos la asignacion de la lista
    }
  }
  return exito;
}

template <typename T>
bool Problema_csp<T>::expandir_bt(const unsigned variable,std::vector<std::pair<unsigned,T>>& lista_asignaciones)
{
  auto tam=lista_asignaciones.size();
  for(auto valor:dominio[variable])
  {
    if(consistente(variable,valor))   //Esta Función depende de cada problema
    {
      lista_asignaciones.push_back({variable,valor});
    }
  }
  return(tam!=lista_asignaciones.size());  //Devolvemos true si se han añadido nodos
}

#endif // CSP_BACKTRACKING_H_INCLUDED
