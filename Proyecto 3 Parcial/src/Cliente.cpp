#include "../include/Cliente.h"

Cliente::Cliente(const std::string& id, const std::string& nombre, const std::string& telefono)
    : cedula(id), nombre(nombre), telefono(telefono) {}

Cliente::Cliente(const std::string& cedula, const std::string& nombre, const std::string& telefono, const std::string& email)
    : cedula(cedula), nombre(nombre), telefono(telefono), email(email) {}

const std::string& Cliente::getNombre() const {
    return nombre;
}

const std::string& Cliente::getTelefono() const {
    return telefono;
}

const std::string& Cliente::getCedula() const {
    return cedula;
}

const std::string& Cliente::getEmail() const {
    return email;
}

void Cliente::mostrarCliente() const {
    try {
        std::cout << "Cliente Cédula: " << cedula
                  << " | Nombre: " << nombre
                  << " | Teléfono: " << telefono
                  << " | Email: " << email
                  << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al mostrar la información del cliente: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al mostrar la información del cliente." << std::endl;
    }
}
