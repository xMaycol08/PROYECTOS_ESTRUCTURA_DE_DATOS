#include "../include/Utils.h"
#include <ctime>
#include <vector>
#include <iostream>
#include <conio.h>
#include <limits>

void mostrarMenu(int &opcion)
{
    std::vector<std::string> opciones = {
        "Agregar reserva",
        "Mostrar disponibilidad de mesas",
        "Cancelar reserva",
        "Mostrar reservas",
        "Mostrar reservas por cédula",
        "Buscar cliente por cédula", // Nueva opción para buscar cliente por cédula
        "Generar reservas en PDF",
        "Hacer backup de reservas",
        "Recuperar backup de reservas",
        "Ayuda", // Nueva opción de ayuda
        "Salir"
    };
    int seleccion = 0;

    while (true)
    {
        Utils::limpiarPantalla();
        std::cout << "===== SISTEMA DE RESERVAS =====" << std::endl;
        for (size_t i = 0; i < opciones.size(); ++i)
        {
            if (i == static_cast<size_t>(seleccion)) // Cast seleccion to size_t
                std::cout << ">> " << opciones[i] << " <<" << std::endl;
            else
                std::cout << "   " << opciones[i] << std::endl;
        }

        char tecla = _getch();
        if (tecla == 72)
        { // Flecha Arriba
            seleccion = (seleccion - 1 + opciones.size()) % opciones.size();
        }
        else if (tecla == 80)
        { // Flecha Abajo
            seleccion = (seleccion + 1) % opciones.size();
        }
        else if (tecla == '\r')
        { // Enter
            opcion = seleccion + 1;
            break;
        }
    }
}

void Utils::limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

