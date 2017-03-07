#include "header/controlador.h"

int main()
{
   //Estos parametros podrian elegirse por linea de comandos o
   //leerse desde un fichero de configuracion
    const auto tam_casilla = 40u;
    const auto filas=18u;
    const auto columnas=32u;

    controlador::Controlador c(filas,columnas,tam_casilla);

    try
    {
        c.ejecutar();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what();
    }
}
