#include "header/controlador.h"

int main()
{
  Vista vista;

  unsigned num_individuos=100;
  unsigned num_generaciones=50000;
  double porcentaje_elite=0.1;          // 10% mejores permanecen
  double probabilidad_mutacion=0.02;
  unsigned tam_torneo=10;

  Genetico_Tsp<ruta::Ruta> genetico_tsp;
  genetico_tsp.inicializacion(num_individuos,porcentaje_elite,num_generaciones,probabilidad_mutacion,tam_torneo);
  genetico_tsp.set_seleccion(Seleccion::torneo_determinista);
  controlador::Controlador c(vista,genetico_tsp);
  c.ejecutar();
}
