#include "../header/nodo_reversi.h"

//El valor minimax inicial es [-2*filas*columnas+1] en nodos MAX y [2*filas*columnas+1] en nodos MIN
//Los valores alphabeta iniciales son [-filas*columnas+1,filas*columnas+1]
void Nodo_reversi_minimax::set_nodo_inicial()
{
	padre = -1;
	minimax = -int(2 * posicion.get_filas()*posicion.get_columnas()) - 1;
	visitado = false;
	profundidad = 0;
}

void Nodo_reversi_alpha_beta::set_nodo_inicial()
{
	padre = -1;
	alpha = -int(2 * posicion.get_filas()*posicion.get_columnas()) - 1;
	beta = int(2 * posicion.get_filas()*posicion.get_columnas()) + 1;
	visitado = false;
	profundidad = 0;
}
