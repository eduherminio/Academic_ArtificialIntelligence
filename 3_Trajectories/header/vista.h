#ifndef VISTA_H_INCLUDED
#define VISTA_H_INCLUDED

#include "observador.h"
#include "rejilla.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

enum class Evento_Vista {EJECUTAR,FIN};
class Vista
{
    unsigned filas;
    unsigned columnas;
    unsigned tam_casilla;
    sf::RenderWindow render_window;
    Rejilla rejilla;
    bool desplazamiento_diagonal_habilitado,existe_casilla_inicial, existe_casilla_final;
    sf::Font font;
    sf::Text texto_num_movimientos, texto_tiempo, texto_desplazamiento_en_diagonal,texto_trayectoria_encontrada, noCasillaText;
    sf::Clock solveTime;

    void procesa_eventos();
    void procesa_eventos_raton();
    void procesa_eventos_teclado(sf::Keyboard::Key& evt);
    void render();
    void carga_mensajes(int alto);

    Observador<Evento_Vista> observador;
public:
    Vista(unsigned filas,unsigned columnas,unsigned tam_casilla);
    std::pair<unsigned,unsigned> pos_casilla_inicial();
    std::pair<unsigned,unsigned> pos_casilla_final();
    std::vector<std::pair<unsigned,unsigned>> pos_muros();
    void dibuja_trayectoria(const std::vector<std::pair<unsigned,unsigned>>&);
    void trayectoria_encontrada(const std::vector<std::pair<unsigned,unsigned>>& solucion,const unsigned num_nodos_expandidos);
    Observador<Evento_Vista>& get_observador()
    {
        return observador;
    }
    void ejecutar();
};
#endif // VISTA_H_INCLUDED
