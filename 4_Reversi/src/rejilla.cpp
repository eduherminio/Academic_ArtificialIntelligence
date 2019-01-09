#include "../header/rejilla.h"
#include <iostream>

bool Rejilla::get_fila_columna(unsigned x_pos,unsigned y_pos,unsigned &fil,unsigned &col) const
{
  return true;
}

void Rejilla::set_rejilla(unsigned f,unsigned c,unsigned tam_casilla,unsigned hueco_entre_casillas,unsigned hueco_al_borde,const Textura& textura)
{
  filas=f;
  columnas=c;
  //tam_casilla=dim_cas;
  for (auto i =0u; i!=filas; ++i)
  {
    for (auto j=0u; j!=columnas; ++j)
    {
      Casilla t(sf::Rect<unsigned>(j*(tam_casilla+hueco_entre_casillas)+hueco_al_borde,i*(tam_casilla +hueco_entre_casillas)+hueco_al_borde,tam_casilla,tam_casilla));
      casillas.push_back(t);
    }
  }

  for (auto i =0u; i!=filas; ++i)
  {
    for (auto j=0u; j!=columnas; ++j)
    {
      set_tipo_casilla(i,j,Tipo_casilla::vacia,textura);
    }
  }

  unsigned pos_ini=((filas/2)-1)*columnas+(columnas/2)-1;
  casillas[pos_ini].set_tipo(Tipo_casilla::humano,textura);
  casillas[pos_ini+1].set_tipo(Tipo_casilla::ordenador,textura);
  casillas[pos_ini+columnas].set_tipo(Tipo_casilla::ordenador,textura);
  casillas[pos_ini+columnas+1].set_tipo(Tipo_casilla::humano,textura);
}

void Rejilla::borra_rejilla(const Textura& textura)
{
  for (auto& casilla:casillas)
  {
    casilla.set_tipo(Tipo_casilla::vacia_tono1,textura);
  }
}


bool Rejilla::indice_casilla(sf::Vector2i posicion,unsigned &fil,unsigned &col) const
{
  bool salida=false;
  unsigned contador=0;
  for(auto &x:casillas)
  {
    auto rect=x.get_rectangulo();
    auto x1=rect.getPosition().x;
    auto y1=rect.getPosition().y;
    auto x2=x1+rect.getSize().x;
    auto y2=y1+rect.getSize().y;

    if(posicion.x>x1 && posicion.x<x2 && posicion.y>y1 && posicion.y<y2)
    {
      fil=contador/filas;
      col=contador%columnas;
      salida=true;
      break;
    }
    ++contador;
  }
  return salida;
}

//void Rejilla::set_tipo_casilla(sf::Vector2i posicion, Tipo_casilla tipo_casilla,const Textura textura)
//{
//    casillas[indice_casilla(posicion)].set_tipo(tipo_casilla,textura);
//}

void Rejilla::set_tipo_casilla(unsigned fil,unsigned col, Tipo_casilla tipo_casilla,const Textura& textura)
{
  if(tipo_casilla==Tipo_casilla::vacia)
  {
    if(fil%2==0)
    {
      if(col%2==0)
      tipo_casilla=Tipo_casilla::vacia_tono1;
      else
      tipo_casilla=Tipo_casilla::vacia_tono2;
    }
    else
    {
      if(col%2==0)
      tipo_casilla=Tipo_casilla::vacia_tono2;
      else
      tipo_casilla=Tipo_casilla::vacia_tono1;
    }
  }
  casillas[fil*columnas+col].set_tipo(tipo_casilla,textura);
}
void Rejilla::draw(sf::RenderTarget& target, sf::RenderStates ) const
{
  for (const auto& casilla : casillas)
  target.draw(casilla);
}
