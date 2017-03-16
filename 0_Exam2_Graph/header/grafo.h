#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <vector>
#include <string>
namespace grafo
{
  using std::vector;
  using std::string;

  struct Nodo
  {
    string nombre;

    // To complete
    vector<int> hijos;
    vector<int> coste_operadores;
    int coste_actual;
    int heuristica;
  };

  class Nodo_grafo
  {
  public:
    Nodo_grafo(const string& nombre):nombre(nombre)
    {
    }
    string get_nombre() const
    {
      return nombre;
    }
    vector<Nodo_grafo> expandir() const;

  private:
    string nombre;                    //Identificador del nodo
    static vector<Nodo> lista_nodos;  //Grafo
    friend double heuristica(const Nodo_grafo& nodo1,const Nodo_grafo& nodo2);
    friend double coste_operador(const Nodo_grafo& nodo1,const Nodo_grafo& nodo2);
  };

  double heuristica(const Nodo_grafo& nodo1, const Nodo_grafo& nodo2);
  double coste_operador(const Nodo_grafo& nodo1, const Nodo_grafo& nodo2);
}

#endif // GRAFO_H_INCLUDED
