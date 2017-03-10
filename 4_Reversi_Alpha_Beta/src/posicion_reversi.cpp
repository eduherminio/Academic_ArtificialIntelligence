#include "../header/posicion_reversi.h"
#include <iostream>

const int Posicion_reversi::despl[8][2]= {{-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1}};

void Posicion_reversi::actualiza_tablero(const struct Jugada jugada)
{
  int x,y,despl_x,despl_y;

  for(auto dir:jugada.dir) // direcciones
  {
    despl_x=despl[dir][0];
    despl_y=despl[dir][1];

    x=jugada.x;
    y=jugada.y;
    do{
      set_tablero(x,y,turno);
      x+=despl_x;
      y+=despl_y;
    }while(tablero[x][y]!=turno);
  }
}

std::vector<Jugada> Posicion_reversi::calcula_jugadas() const
{
  std::vector<Jugada> lista_jugadas;
  bool salida;
  bool jugada_valida;
  int x,y,despl_x,despl_y;

  unsigned filas=get_filas();
  unsigned columnas=get_columnas();

  for(unsigned i=0; i<filas; i++)
  {
    for(unsigned j=0; j<columnas; j++)
    {
      if(tablero[i][j]==Turno::vacia)
      {
        std::vector<unsigned>direcciones;
        for(unsigned dir=0; dir<8; dir++) //8 posibles direcciones
        {
          despl_x=despl[dir][0];
          despl_y=despl[dir][1];
          x=i;
          y=j;
          salida=false;
          jugada_valida=false;
          while(!salida)
          {
            x+=despl_x;
            y+=despl_y;
            if(x<0 || y<0 || x==int(filas) || y==int(columnas) || tablero[x][y]==Turno::vacia) //x o y fuera del tablero o casilla vacia
            salida=true;
            else if(tablero[x][y]==turno)
            {
              salida=true;
              if(jugada_valida)//Hemos encontrado al menos una pieza contraria enre la nuestra
              {
                direcciones.push_back(dir);
              }
            }
            else
            jugada_valida=true; //Incrementamos contador cada vez que la ficha es del otro color
          }

        }
        if(direcciones.size()>0) //Hemos encontrado alguna jugada valida
        lista_jugadas.push_back({unsigned(i),unsigned(j),direcciones});
      }
    }
  }
  return lista_jugadas;
}


int Posicion_reversi::evalua_posicion(const bool es_terminal) const
{
  //La heuristica da valores entre [-get_filas()*get_columnas(),get_filas()*get_columnas()]
  int valor=0;
  for(unsigned i = 0; i < get_filas(); i++)
  {
    for(unsigned j = 0; j < get_columnas(); j++)
    {
      if(tablero[i][j]==Turno::ordenador)
      ++valor;
      else if(tablero[i][j]==Turno::humano)
      --valor;
    }
  }
  if(es_terminal) //La puntuaci�n de una posici�n terminal ganadora siempre ser� mayor que la   -- TO-CHECK
  {               //puntuaci�n de una heur�stica. Es mejor saber que ganas seguro por 3 fichas
    //que una heur�stica eval�e que posiblemente ganes por 10 fichas
    if(valor>0)
    {
      valor+=get_filas()*get_columnas();
    }
    else if(valor<0)
    {
      valor-=get_filas()*get_columnas();
    }
  }


  //A mejorar la heuristica por el alumno
  return valor;
}

void Posicion_reversi::imprime_tablero()
{
  for(unsigned i = 0; i < get_filas(); i++)
  {
    for(unsigned j = 0; j < get_columnas(); j++)
    {
      if(tablero[i][j]==Turno::ordenador)
      std::cout<<"O ";
      else if(tablero[i][j]==Turno::humano)
      std::cout<<"H ";
      else
      std::cout<<"  ";
    }
    std::cout<<std::endl;
  }
}
