#include "../include/Mesa.h"
#include <string>

// Constructor por defecto
Mesa::Mesa() : id(0), capacidad(0), disponible(true) {}

// Constructor con parámetros
Mesa::Mesa(int id, int capacidad) : id(id), capacidad(capacidad), disponible(true) {}

// Métodos Getters
int Mesa::getId() const {
    return id;
}

int Mesa::getCapacidad() const {
    return capacidad;
}

bool Mesa::estaDisponible() const {
    return disponible;
}

// Métodos de modificación
void Mesa::ocupar() {
    try {
        disponible = false;
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al ocupar la mesa: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al ocupar la mesa." << std::endl;
    }
}

void Mesa::liberar() {
    try {
        disponible = true;
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al liberar la mesa: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al liberar la mesa." << std::endl;
    }
}


// Constructor con número
Mesa::Mesa(int numero) : numero(numero) {
    // Initialize other members if necessary
}

int Mesa::getNumero() const {
    return numero;
}

std::string Mesa::getNombre() const {
    return nombre;
}

std::string Mesa::getTelefono() const {
    return telefono;
}
