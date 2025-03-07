#include "../include/DataManager.h"
#include "../include/Reserva.h" // Include this header for Reserva
#include "../include/Cliente.h" // Include this header for Cliente
#include <iomanip> // Include this header for std::get_time
#include <fstream>
#include <sstream>
#include <unordered_set>

void DataManager::guardarReservas(const Calendario& calendario) {
    try {
        std::ofstream file("reservas.txt");
        for (const auto& reserva : calendario.getReservas()) {
            file << reserva.getCliente().getCedula() << ","
                 << reserva.getCliente().getNombre() << ","
                 << reserva.getCliente().getTelefono() << ","
                 << reserva.getCliente().getEmail() << ","
                 << reserva.getIdMesa() << ","
                 << reserva.getFechaHora() << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al guardar las reservas: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al guardar las reservas." << std::endl;
    }
}

void DataManager::cargarReservas(Calendario& calendario) {
    try {
        std::ifstream file("reservas.txt");
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string cedula, nombreCliente, telefono, email, fechaHora;
            int idMesa;
            if (std::getline(iss, cedula, ',') && std::getline(iss, nombreCliente, ',') &&
                std::getline(iss, telefono, ',') && std::getline(iss, email, ',') &&
                iss >> idMesa && iss.ignore() && std::getline(iss, fechaHora)) {
                Reserva* reserva = new Reserva(cedula, nombreCliente, telefono, email, idMesa, fechaHora);
                calendario.agregarReserva(*reserva);
                delete reserva; // Limpiar memoria dinámica
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al cargar las reservas: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al cargar las reservas." << std::endl;
    }
}

void DataManager::cargarClientes(ArbolClientes& arbolClientes) {
    try {
        std::ifstream file("reservas.txt");
        std::string line;
        std::unordered_set<std::string> clientesCargados; // Para evitar duplicados

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string cedula, nombre, telefono, email, fechaHora;
            int idMesa;
            if (std::getline(iss, cedula, ',') && std::getline(iss, nombre, ',') &&
                std::getline(iss, telefono, ',') && std::getline(iss, email, ',') &&
                iss >> idMesa && iss.ignore() && std::getline(iss, fechaHora)) {
                
                // Verificar si el cliente ya fue cargado
                if (clientesCargados.find(cedula) == clientesCargados.end()) {
                    Cliente* cliente = new Cliente(cedula, nombre, telefono, email);
                    arbolClientes.insertar(*cliente);
                    clientesCargados.insert(cedula); // Marcar como cargado
                    delete cliente; // Limpiar memoria dinámica
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al cargar los clientes: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al cargar los clientes." << std::endl;
    }
}
