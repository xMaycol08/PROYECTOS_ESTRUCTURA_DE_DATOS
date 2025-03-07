#ifndef CALENDARIO_H
#define CALENDARIO_H

#include <iostream>
#include <ctime>
#include <vector>
#include "Reserva.h"

class NodoFecha {
public:
    std::tm* fechaHora;
    NodoFecha* siguiente;
    NodoFecha* anterior;

    NodoFecha(const std::tm& fecha)
        : fechaHora(new std::tm(fecha)), siguiente(nullptr), anterior(nullptr) {}

    ~NodoFecha() {
        delete fechaHora;
    }
};

class Calendario {
public:
    Calendario();
    ~Calendario();
    void agregarReserva(const Reserva& reserva);
    bool eliminarReserva(const std::string& cedula, int idMesa, const std::string& fechaHora);
    const std::vector<Reserva>& getReservas() const;
    void limpiarReservas(); // Agregar declaración

private:
    NodoFecha* cabeza;
    NodoFecha* cola;
    std::vector<Reserva> reservas;
    void liberarMemoria();
};

#endif
