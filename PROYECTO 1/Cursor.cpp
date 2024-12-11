#include "Cursor.h"
#include <iostream>
#include <conio.h> // Para _kbhit() y _getch() en Windows
#include <cstdlib> // Para system("cls")
#include <windows.h>

using namespace std;

// Constructor que inicializa la posici�n del cursor y el total de opciones
Cursor::Cursor(int totalOpciones) : posicion(0), totalOpciones(totalOpciones) {}

// M�todo para mover el cursor hacia arriba
void Cursor::moverArriba() {
    if (posicion > 0) {
        posicion--;
    }else {
        // Si est� en la primera opci�n, saltar al final
        posicion = totalOpciones - 1;
    }
}

// M�todo para mover el cursor hacia abajo
void Cursor::moverAbajo() {
    if (posicion < totalOpciones - 1) {
        posicion++;
    }else {
        // Si est� en la �ltima opci�n, saltar al principio
        posicion = 0;
    }
}

// M�todo para obtener la posici�n actual del cursor
int Cursor::getPosicion() {
    return posicion;
}

// M�todo para actualizar y mostrar el men� con el cursor en la opci�n seleccionada

void Cursor::actualizarMenu(const string opciones[], int totalOpciones) {
    system("cls");  // Limpiar la consola

    for (int i = 0; i < totalOpciones; i++) {
        if (i == posicion) {
            cambiarColorTexto(3); // Color amarillo para la opci�n seleccionada
            cout << "* " << opciones[i] << " *\n";
            cambiarColorTexto(7); // Restaurar color blanco
        } else {
            cout << "  " << opciones[i] << "\n";
        }
    }
}


// M�todo para verificar si se presion� la tecla Enter (c�digo 13)
bool Cursor::aceptarSeleccion() {
    return (_kbhit() && _getch() == 13); // Enter
}

// M�todo para verificar si se presion� cualquier tecla
bool Cursor::teclaPresionada() {
    return _kbhit();
}

void Cursor::cambiarColorTexto(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
