#ifndef ENUMERACIONES_H_INCLUDED
#define ENUMERACIONES_H_INCLUDED

#include <stdint.h>

enum class Tipo_casilla :uint8_t { vacia, vacia_tono1, vacia_tono2, vacia_posible, humano, ordenador };
enum class Turno :uint8_t { vacia, humano, ordenador };
enum class Tipo_tablero :uint8_t { no_pasa, pasa, terminal };
enum class Evento_vista :uint8_t { casilla, manual, ordenador };

#endif // ENUMERACIONES_H_INCLUDED
