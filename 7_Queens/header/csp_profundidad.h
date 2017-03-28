namespace problema_csp
{
  template<typename T>
  bool Problema_csp<T>::profundidad()
  {
    struct Nodo
    {
      T nodo;
      bool visitado;
    };
    std::vector<Nodo> lista;
    lista.push_back({nodo_inicial,false});

    size_t indice=0;
    bool exito=false;
    nodos_expandidos=0;
    while(exito==false && lista.size()>0)
    {
      // TO-DO - busqueda en profundidad
      exito=true; //Eliminar esta linea
    }
    if(exito)
    {
      nodo_solucion=lista[indice].nodo;
    }
    return exito;
  }
}
