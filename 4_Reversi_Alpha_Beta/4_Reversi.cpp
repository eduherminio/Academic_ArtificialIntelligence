#include "header/controlador.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  unsigned int filas, columnas;



  if(argc==2) {
    filas=      std::atoi(argv[1]);
    columnas=   std::atoi(argv[1]);
  }
  else if (argc==3) {
    filas=      std::atoi(argv[1]);
    columnas=   std::atoi(argv[2]);
  }
  else  {
    filas=    8u;
    columnas= 8u;
  }

    const auto rows= filas;
    const auto cols= columnas;
    std::cout<<"Selected size: "<<rows<<"x"<<cols<<std::endl;

  controlador::Controlador c(rows,cols);

  c.ejecutar();

  return 0;
}
