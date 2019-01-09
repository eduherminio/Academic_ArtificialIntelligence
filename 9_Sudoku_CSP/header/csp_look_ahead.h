#ifndef CSP_LOOK_AHEAD_H_INCLUDED
#define CSP_LOOK_AHEAD_H_INCLUDED

template <typename T>
bool Problema_csp<T>::look_ahead()
{
  inicializa();

  bool exito=false;
  nodos_expandidos=0;
  bool bloqueo=false;

  std::vector<std::pair<unsigned,T>>lista_asignaciones;

  while(!exito)
  {
    ++nodos_expandidos;
    if(!bloqueo)
    {
      auto variable=seleccion_variable();
      for(auto& valor:dominio[variable])
      {
        lista_asignaciones.push_back({variable,valor});
      }
    }
    else
    {
      if(lista_asignaciones.empty())
      {
        break;
      }
      else
      {
        bool eliminar=true;
        while(eliminar)
        {
          if(solucion.back().first==lista_asignaciones.back().first)
          eliminar=false;
          restaura_dominio(solucion.back().first);
          libera_variable(solucion.back().first);
          solucion.pop_back();

        }
      }
    }
    solucion.push_back(lista_asignaciones.back());
    bloquea_variable();
    if(variables_sin_etiquetar.empty())
    {
      exito=true;
    }
    else
    {
      bloqueo=actualiza_dominio(solucion.back());
      lista_asignaciones.pop_back();
    }
  }
  return exito;
}

template <typename T>
void Problema_csp<T>::restaura_dominio(const unsigned variable)
{
  for(auto& asignacion:lista_exclusiones_dominio[variable])
  {
    dominio[asignacion.first].push_back(asignacion.second);
  }
  lista_exclusiones_dominio[variable].clear();
}

#endif // CSP_LOOK_AHEAD_H_INCLUDED
