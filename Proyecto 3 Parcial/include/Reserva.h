#ifndef RESERVA_H
#define RESERVA_H

#include <string>
#include <ctime>
#include <iostream>
#include "Cliente.h"

class Reserva {
public:
    Reserva(); // Default constructor
    Reserva(const Cliente& cliente, int idMesa, const std::tm& fecha);
    Reserva(const std::string& cedula, const std::string& nombreCliente, const std::string& telefono, const std::string& email, int idMesa, const std::tm& fecha);
    Reserva(const std::string& cedula, const std::string& nombreCliente, const std::string& telefono, const std::string& email, int idMesa, const std::string& fechaHora);
    Reserva(const std::string& nombreCliente, int idMesa, const std::tm& fecha);
    Reserva(const std::string& nombreCliente, int idMesa, const std::string& fechaHora);

    const Cliente& getCliente() const;
    int getIdMesa() const;
    const std::tm& getFecha() const;
    const std::string& getFechaHora() const;
    const std::string& getCedula() const { return cliente.getCedula(); }
    const std::string& getNombre() const { return cliente.getNombre(); }
    const std::string& getTelefono() const { return cliente.getTelefono(); }
    const std::string& getEmail() const { return cliente.getEmail(); }

private:
    Cliente cliente;
    int idMesa;
    std::tm fecha;
    std::string fechaHora;

    std::string convertirTmAString(const std::tm& fecha) const;
    std::tm convertirStringATm(const std::string& fechaHora) const;
};

#endif // RESERVA_H
