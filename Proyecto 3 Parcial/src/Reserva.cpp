#include "../include/Reserva.h"
#include <iomanip>
#include <sstream>
#include <ctime> // Include this header for time_t and std::mktime

Reserva::Reserva() : idMesa(0) {}

Reserva::Reserva(const Cliente& cliente, int idMesa, const std::tm& fecha)
    : cliente(cliente), idMesa(idMesa), fecha(fecha) {
    try {
        fechaHora = convertirTmAString(fecha);
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al convertir la fecha a string: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al convertir la fecha a string." << std::endl;
    }
}

Reserva::Reserva(const std::string& nombreCliente, int idMesa, const std::tm& fecha)
    : cliente("", nombreCliente, "", ""), idMesa(idMesa), fecha(fecha) {
    try {
        fechaHora = convertirTmAString(fecha);
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al convertir la fecha a string: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al convertir la fecha a string." << std::endl;
    }
}

Reserva::Reserva(const std::string& nombreCliente, int idMesa, const std::string& fechaHora)
    : cliente("", nombreCliente, "", ""), idMesa(idMesa), fechaHora(fechaHora) {
    try {
        fecha = convertirStringATm(fechaHora);
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al convertir el string a fecha: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al convertir el string a fecha." << std::endl;
    }
}

Reserva::Reserva(const std::string& cedula, const std::string& nombreCliente, const std::string& telefono, const std::string& email, int idMesa, const std::tm& fecha)
    : cliente(cedula, nombreCliente, telefono, email), idMesa(idMesa), fecha(fecha) {
    try {
        fechaHora = convertirTmAString(fecha);
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al convertir la fecha a string: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al convertir la fecha a string." << std::endl;
    }
}

Reserva::Reserva(const std::string& cedula, const std::string& nombreCliente, const std::string& telefono, const std::string& email, int idMesa, const std::string& fechaHora)
    : cliente(cedula, nombreCliente, telefono, email), idMesa(idMesa), fechaHora(fechaHora) {
    try {
        fecha = convertirStringATm(fechaHora);
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al convertir el string a fecha: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al convertir el string a fecha." << std::endl;
    }
}

const Cliente& Reserva::getCliente() const {
    return cliente;
}

int Reserva::getIdMesa() const {
    return idMesa;
}

const std::tm& Reserva::getFecha() const {
    return fecha;
}

const std::string& Reserva::getFechaHora() const {
    return fechaHora;
}


std::string Reserva::convertirTmAString(const std::tm& fecha) const {
    try {
        std::ostringstream oss;
        oss << std::put_time(&fecha, "%Y-%m-%d %H:%M");
        return oss.str();
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al convertir la fecha a string: " << e.what() << std::endl;
        return "";
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al convertir la fecha a string." << std::endl;
        return "";
    }
}

std::tm Reserva::convertirStringATm(const std::string& fechaHora) const {
    try {
        std::tm tm = {};
        std::istringstream ss(fechaHora);
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");
        return tm;
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al convertir el string a fecha: " << e.what() << std::endl;
        return {};
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al convertir el string a fecha." << std::endl;
        return {};
    }
}
