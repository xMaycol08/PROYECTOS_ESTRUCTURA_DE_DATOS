#ifndef MESA_H
#define MESA_H

#include <iostream>
#include <string>

class Mesa {
private:
    int id;
    int capacidad;
    bool disponible;
    int numero;
    std::string nombre;
    std::string telefono;

public:
    // Constructor por defecto
    Mesa();

    // Constructor con parámetros
    Mesa(int id, int capacidad);
    Mesa(int numero); // Constructor

    // Métodos Getters
    int getId() const;
    int getCapacidad() const;
    bool estaDisponible() const;
    int getNumero() const; // Getter for numero
    std::string getNombre() const; // Getter for nombre
    std::string getTelefono() const; // Getter for telefono

    // Métodos de modificación
    void ocupar();
    void liberar();
};

#endif // MESA_H
