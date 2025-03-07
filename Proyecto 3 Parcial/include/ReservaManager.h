#ifndef RESERVAMANAGER_H
#define RESERVAMANAGER_H

#include <vector>
#include "Reserva.h"
#include "Calendario.h"
#include "GrafoDisponibilidad.h"
#include "ArbolClientes.h"

class ReservaManager {
public:
    ~ReservaManager(); // Destructor
    static void cargarReservas(Calendario& calendario, GrafoDisponibilidad& grafo, ArbolClientes& arbolClientes);
    static void guardarReservas();
    static void mostrarReservas();
    static bool mostrarReservasPorCedula(const std::string& cedula);
    static void cancelarReservaPorCedula(Calendario& calendario, ArbolClientes& arbolClientes, GrafoDisponibilidad& grafo);
    static std::vector<Reserva*>& getReservas();
    static void liberarMemoria(); // Mover a public

private:
    static std::vector<Reserva*> reservas;
};

#endif // RESERVAMANAGER_H
