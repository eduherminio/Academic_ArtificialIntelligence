#ifndef BB_BACKTRACKING_H_INCLUDED
#define BB_BACKTRACKING_H_INCLUDED

/*
  Diferencia frente a csp: no acabamos cuando encontramos una solución
*/

template <typename T>
bool Problema_bb<T>::bb_backtracking()
{
  bool exito=false;
  nodos_expandidos=0;

  std::vector< std::pair<unsigned,T> > lista_asignaciones;
  std::vector< std::pair<unsigned,T> > solucion_actual;

  bool nueva_solucion=false;
  while(true)
  {
    ++nodos_expandidos;

    if(nueva_solucion || !expandir_bt(seleccion_variable(), lista_asignaciones))
    {
      if(lista_asignaciones.empty())
      {
        return exito;
      }
      else
      {
        nueva_solucion= false;
        bool eliminar= true;
        while(eliminar)
        {
          if(solucion_actual.back().first == lista_asignaciones.back().first)
            eliminar= false;
          restaura_estado(solucion_actual.back());
          libera_variable(solucion_actual.back().first); // Liberamos al final del vector variables_sin_etiquetar
          solucion_actual.pop_back();
        }
      }
    }
    solucion_actual.push_back(lista_asignaciones.back());  // Tenemos nuevo nodo disponible

    bloquea_variable();  // La variable seleccionada siempre es la ultima del vector variables_sin_etiquetar
    actualiza_estado(solucion_actual.back());
    lista_asignaciones.pop_back();     // Eliminamos la asignacion de la lista

    if(variables_sin_etiquetar.empty())
    {
      exito= true;
      nueva_solucion= true;
      actualiza_solucion(solucion_actual);  // Le mandamos al solución al problema concreto, que es el que sabe si hay que minimizar, maximizar, etc. En csp, aquí se acabaría el algoritmo
    }
  }
}

template <typename T>
bool Problema_bb<T>::expandir_bt(const unsigned variable, std::vector<std::pair<unsigned,T>>& lista_asignaciones)
{
  auto tam= lista_asignaciones.size();
  for(auto valor : dominio[variable])
  {
    if(consistente(variable, valor))   // Esta funcion depende de cada problema
      lista_asignaciones.push_back({variable, valor});
  }

  return(tam != lista_asignaciones.size());  // Devolvemos true si se han añadido nodos
}

#endif // BB_BACKTRACKING_H_INCLUDED
