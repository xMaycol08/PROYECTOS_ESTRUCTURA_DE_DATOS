#include "../include/GrafoDisponibilidad.h"
#include <iostream>
#include <fstream>
#include <sstream> // Asegurarse de incluir sstream
#include <algorithm>

GrafoDisponibilidad::GrafoDisponibilidad() {
    try {
        std::ifstream file("mesas.txt");
        if (!file) {
            std::ofstream defaultFile("mesas.txt");
            for (int i = 1; i <= 5; ++i) {
                defaultFile << i << std::endl;
            }
            defaultFile.close();
        }
        cargarMesasDesdeArchivo("mesas.txt");  // Cargar mesas desde archivo
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al inicializar GrafoDisponibilidad: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al inicializar GrafoDisponibilidad." << std::endl;
    }
}

GrafoDisponibilidad::~GrafoDisponibilidad() {
    liberarMemoria();
}

void GrafoDisponibilidad::agregarMesa(int id) {
    if (nodos.find(id) == nodos.end()) {
        nodos[id] = new NodoMesa(id);
    }
}

void GrafoDisponibilidad::agregarArista(int id1, int id2) {
    if (nodos.find(id1) != nodos.end() && nodos.find(id2) != nodos.end()) {
        nodos[id1]->adyacentes.push_back(nodos[id2]);
        nodos[id2]->adyacentes.push_back(nodos[id1]);
    }
}

void GrafoDisponibilidad::cargarMesasDesdeArchivo(std::string archivo) {
    try {
        std::ifstream file(archivo);
        if (!file) {
            std::cerr << "⚠️ No se encontró el archivo de configuración de mesas.\n";
            return;
        }

        int numeroMesa;
        while (file >> numeroMesa) {
            agregarMesa(numeroMesa);
        }
        file.close();
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al cargar las mesas desde el archivo: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al cargar las mesas desde el archivo." << std::endl;
    }
}

void GrafoDisponibilidad::agregarReserva(int idMesa, const std::string& fechaHora) {
    try {
        reservasPorFecha[fechaHora].push_back(idMesa);
        if (nodos.find(idMesa) != nodos.end()) {
            nodos[idMesa]->mesa->ocupar();
        }
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al agregar una reserva: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al agregar una reserva." << std::endl;
    }
}

void GrafoDisponibilidad::eliminarReserva(int idMesa, const std::string& fechaHora) {
    try {
        auto it = reservasPorFecha.find(fechaHora);
        if (it != reservasPorFecha.end()) {
            auto& mesas = it->second;
            mesas.erase(std::remove(mesas.begin(), mesas.end(), idMesa), mesas.end());
            if (mesas.empty()) {
                reservasPorFecha.erase(it);
            }
        }
        if (nodos.find(idMesa) != nodos.end()) {
            nodos[idMesa]->mesa->liberar();
        }
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al eliminar una reserva: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al eliminar una reserva." << std::endl;
    }
}

std::vector<int> GrafoDisponibilidad::obtenerMesasDisponibles(const std::string& fechaHora) const {
    try {
        std::vector<int> disponibles;
        for (const auto& nodo : nodos) {
            disponibles.push_back(nodo.first);
        }
        auto it = reservasPorFecha.find(fechaHora);
        if (it != reservasPorFecha.end()) {
            for (int idMesa : it->second) {
                disponibles.erase(std::remove(disponibles.begin(), disponibles.end(), idMesa), disponibles.end());
            }
        }
        return disponibles;
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al obtener las mesas disponibles: " << e.what() << std::endl;
        return {};
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al obtener las mesas disponibles." << std::endl;
        return {};
    }
}

void GrafoDisponibilidad::mostrarDisponibilidad(const std::string& fechaHora, const std::vector<Reserva*>& reservas) const {
    try {
        std::cout << "Debug: Fecha y hora recibida en mostrarDisponibilidad: " << fechaHora << std::endl; // Debug message
        std::cout << "Disponibilidad de mesas en " << fechaHora << ":\n";
        std::cout << "------------------------------------------\n";
        for (int i = 1; i <= 5; ++i) { // Asumiendo que hay 5 mesas
            bool ocupada = false;
            for (const auto& reserva : reservas) {
                if (reserva->getIdMesa() == i && reserva->getFechaHora() == fechaHora) {
                    ocupada = true;
                    std::cout << "Mesa #" << i << " - Estado: ❌ Ocupada  \n- Reservada por: " 
                              << reserva->getCliente().getNombre() << " \n- Contacto: " 
                              << reserva->getCliente().getTelefono() << "\n";
                    break;
                }
            }
            if (!ocupada) {
                std::cout << "Mesa #" << i << " - Estado: ✅ Disponible\n";
            }
        }
        std::cout << "------------------------------------------\n";
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al mostrar la disponibilidad de las mesas: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al mostrar la disponibilidad de las mesas." << std::endl;
    }
}

void GrafoDisponibilidad::liberarMemoria() {
    for (auto& nodo : nodos) {
        delete nodo.second;
    }
    nodos.clear();
}

void GrafoDisponibilidad::limpiarReservas() {
    reservasPorFecha.clear();
    for (auto& nodo : nodos) {
        nodo.second->mesa->liberar();
    }
}
