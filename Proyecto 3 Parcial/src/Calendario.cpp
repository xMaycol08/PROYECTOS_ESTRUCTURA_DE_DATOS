#include "../include/Calendario.h"
#include <algorithm> // Incluir la cabecera para std::remove_if
#include <sstream>   // Incluir la cabecera para std::istringstream
#include <iomanip>   // Incluir la cabecera para std::get_time

Calendario::Calendario() : cabeza(nullptr), cola(nullptr) {}

Calendario::~Calendario() {
    try {
        liberarMemoria();
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al liberar la memoria en Calendario: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al liberar la memoria en Calendario." << std::endl;
    }
}

void Calendario::liberarMemoria() {
    try {
        NodoFecha* actual = cabeza;
        while (actual) {
            NodoFecha* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
        cabeza = cola = nullptr;
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al liberar la memoria de las fechas: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al liberar la memoria de las fechas." << std::endl;
    }
}

void Calendario::agregarReserva(const Reserva& reserva) {
    try {
        NodoFecha* nuevo = new NodoFecha(reserva.getFecha());
        if (!cabeza) {
            cabeza = cola = nuevo;
        } else {
            cola->siguiente = nuevo;
            nuevo->anterior = cola;
            cola = nuevo;
        }
        reservas.push_back(reserva);
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al agregar una reserva: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al agregar una reserva." << std::endl;
    }
}

bool Calendario::eliminarReserva(const std::string& cedula, int idMesa, const std::string& fechaHora) {
    try {
        NodoFecha* actual = cabeza;
        while (actual) {
            std::tm tmFechaHora = {};
            std::istringstream ss(fechaHora);
            ss >> std::get_time(&tmFechaHora, "%Y-%m-%d %H:%M");
            if (std::mktime(actual->fechaHora) == std::mktime(&tmFechaHora)) {
                if (actual->anterior) {
                    actual->anterior->siguiente = actual->siguiente;
                } else {
                    cabeza = actual->siguiente;
                }
                if (actual->siguiente) {
                    actual->siguiente->anterior = actual->anterior;
                } else {
                    cola = actual->anterior;
                }
                delete actual;

                auto it = std::remove_if(reservas.begin(), reservas.end(), [&](const Reserva& reserva) {
                    return reserva.getCliente().getCedula() == cedula && reserva.getIdMesa() == idMesa && reserva.getFechaHora() == fechaHora;
                });
                if (it != reservas.end()) {
                    reservas.erase(it, reservas.end());
                }

                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al eliminar una reserva: " << e.what() << std::endl;
        return false;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al eliminar una reserva." << std::endl;
        return false;
    }
}

const std::vector<Reserva>& Calendario::getReservas() const {
    try {
        return reservas;
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al obtener las reservas: " << e.what() << std::endl;
        throw;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al obtener las reservas." << std::endl;
        throw;
    }
}

void Calendario::limpiarReservas() {
    reservas.clear();
}
