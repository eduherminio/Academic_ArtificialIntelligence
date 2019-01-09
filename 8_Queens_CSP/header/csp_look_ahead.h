#ifndef CSP_LOOK_AHEAD_H_INCLUDED
#define CSP_LOOK_AHEAD_H_INCLUDED

template <typename T>
bool Problema_csp<T>::look_ahead()
{
  inicializa();

  bool exito= false;
  nodos_expandidos= 0;
  bool bloqueo= false;

  std::vector< std::pair<unsigned, T> > lista_asignaciones;

  // Usa lista_exclusiones_dominio y la variable bloqueo, pero no usa función expandir alguna
  // Actualiza dominios, y no estados. Las pareja de variables y valores que quitamos de los dominios
  // pasan a lista_exclusiones_dominio, desde donde podrán ser restauradas después en caso de bloqueo
  while(!exito)
  {
    ++nodos_expandidos;
    if(!bloqueo)
    {
      auto variable= seleccion_variable();
      for(const auto& valor : dominio[variable])    // No hay función expandir: si no hay bloqueo, es que hay dominio -> hay variables
        lista_asignaciones.push_back({variable, valor});
    }
    else
    {
      if(lista_asignaciones.empty())  // No solution
        break;
      else
      {
        bool eliminar= true;
        while(eliminar)
        {
          if(solucion.back().first == lista_asignaciones.back().first)
            eliminar= false;

          restaura_dominio(solucion.back().first);  // Vacía los conjuntos imposibles de la última variable de la solución -- Equivalente a restaura_estado en backtracking)
          libera_variable(solucion.back().first);   // Variables_sin_etiquetar.push_back(var) // vuelve a dejar disponible la variable
          solucion.pop_back();
        }
      }
    }

    solucion.push_back(lista_asignaciones.back());
    bloquea_variable(); // variables_sin_etiquetar.pop_back();  // seleccion_variable() empuja siempre a la variable seleccionada al final del vector

    if(variables_sin_etiquetar.empty())
      exito= true;
    else
    {
      bloqueo= actualiza_dominio(solucion.back());  // equivalente a expandir_bt: comprueba la existencia de bloqueos
      lista_asignaciones.pop_back();
    }
  }
  return exito;
}

template <typename T>
void Problema_csp<T>::restaura_dominio(const unsigned variable)
{
  for(auto& asignacion : lista_exclusiones_dominio[variable])
  {
    dominio[asignacion.first].push_back(asignacion.second);
  }

  lista_exclusiones_dominio[variable].clear();
}

#endif // CSP_LOOK_AHEAD_H_INCLUDED
