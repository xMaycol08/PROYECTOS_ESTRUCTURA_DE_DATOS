#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <iostream>
#include <fstream>
#include "Calendario.h"
#include "ArbolClientes.h" // Include this header for ArbolClientes

class DataManager {
public:
    static void cargarReservas(Calendario& calendario);
    static void guardarReservas(const Calendario& calendario);
    void cargarClientes(ArbolClientes& arbolClientes);
};

#endif
