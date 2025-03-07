#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "Calendario.h"
#include "ArbolClientes.h"
#include "GrafoDisponibilidad.h"
#include "DataManager.h"
#include "Reserva.h"
#include <vector>

class Menu {
public:
    static void gestionarReservas(Calendario& calendario, ArbolClientes& arbolClientes, GrafoDisponibilidad& grafo, DataManager& dataManager, std::vector<Reserva*>& reservas);
};

#endif // MENU_H
