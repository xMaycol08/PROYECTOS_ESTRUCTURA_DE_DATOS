#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <string>

class Cliente {
private:
    std::string cedula;
    std::string nombre;
    std::string telefono;
    std::string email;

public:
    Cliente() = default; // Default constructor
    Cliente(const std::string& cedula, const std::string& nombre, const std::string& telefono, const std::string& email);
    Cliente(const std::string& id, const std::string& nombre, const std::string& telefono);

    const std::string& getCedula() const;
    const std::string& getNombre() const;
    const std::string& getTelefono() const;
    const std::string& getEmail() const;

    void mostrarCliente() const;

    // Add operator<< for output stream
    friend std::ostream& operator<<(std::ostream& os, const Cliente& cliente) {
        os << cliente.getNombre();
        return os;
    }

    // Add operator== to compare Cliente with std::string
    bool operator==(const std::string& nombre) const {
        return this->getNombre() == nombre;
    }
};

#endif
