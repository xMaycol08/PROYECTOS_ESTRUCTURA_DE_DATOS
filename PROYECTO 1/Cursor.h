#ifndef CURSOR_H
#define CURSOR_H
#include <windows.h>
#include <string>

class Cursor {
private:
    int posicion;          // Posici�n actual del cursor
    int totalOpciones;     // Total de opciones del men�

public:
    // Constructor que recibe el total de opciones del men�
    Cursor(int totalOpciones);

    // M�todo para mover el cursor hacia arriba
    void moverArriba();

    // M�todo para mover el cursor hacia abajo
    void moverAbajo();

    // M�todo para obtener la posici�n actual del cursor
    int getPosicion();

    // M�todo para mostrar el men� con el cursor en la opci�n seleccionada
    void actualizarMenu(const std::string opciones[], int totalOpciones);

    // M�todo que verifica si se presion� la tecla Enter
    bool aceptarSeleccion();

    // M�todo que verifica si alguna tecla ha sido presionada
    bool teclaPresionada();
    void cambiarColorTexto(int color);
};

#endif // CURSOR_H
