#include "../include/ReservaManager.h"
#include "../include/Validaciones.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

std::vector<Reserva*> ReservaManager::reservas;

ReservaManager::~ReservaManager() {
    liberarMemoria();
}

void ReservaManager::liberarMemoria() {
    for (auto reserva : reservas) {
        delete reserva;
    }
    reservas.clear();
}

void ReservaManager::cargarReservas(Calendario& calendario, GrafoDisponibilidad& grafo, ArbolClientes& arbolClientes) {
    try {
        liberarMemoria();
        std::ifstream file("reservas.txt");
        
        if (!file) {
            std::cerr << "Error: No se pudo abrir reservas.txt." << std::endl;
            return;
        }
        
        std::string line;

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string cedula, nombreCliente, telefono, email, fechaHora;
            int idMesa;
            
            if (std::getline(iss, cedula, ',') && std::getline(iss, nombreCliente, ',') &&
                std::getline(iss, telefono, ',') && std::getline(iss, email, ',') &&
                iss >> idMesa && iss.ignore() && std::getline(iss, fechaHora)) {
                
                Reserva* reserva = new Reserva(cedula, nombreCliente, telefono, email, idMesa, fechaHora);
                reservas.push_back(reserva);
                calendario.agregarReserva(*reserva);
                grafo.agregarReserva(idMesa, fechaHora);
                arbolClientes.insertar(Cliente(cedula, nombreCliente, telefono, email));
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al cargar las reservas: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al cargar las reservas." << std::endl;
    }
}

void ReservaManager::guardarReservas() {
    try {
        std::ofstream file("reservas.txt");
        for (const auto& reserva : reservas) {
            file << reserva->getCliente().getCedula() << ","
                 << reserva->getCliente().getNombre() << ","
                 << reserva->getCliente().getTelefono() << ","
                 << reserva->getCliente().getEmail() << ","
                 << reserva->getIdMesa() << ","
                 << reserva->getFechaHora() << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al guardar las reservas: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al guardar las reservas." << std::endl;
    }
}


void ReservaManager::mostrarReservas() {
    try {
        // Recargar reservas desde el archivo antes de mostrarlas
        Calendario calendario;
        GrafoDisponibilidad grafo;
        ArbolClientes arbolClientes;
        cargarReservas(calendario, grafo, arbolClientes);

        std::cout << std::setw(100) << std::setfill('=') << "" << std::endl;
        std::cout << std::setw(50) << std::setfill(' ') << "RESERVAS" << std::endl;
        std::cout << std::setw(100) << std::setfill('=') << "" << std::endl;

        if (reservas.empty()) {
            std::cout << "No hay reservas disponibles." << std::endl;
        } else {
            std::cout << std::setfill(' ') 
                      << std::left << std::setw(15) << "Cédula"
                      << std::setw(20) << "Nombre"
                      << std::setw(15) << "Teléfono"
                      << std::setw(25) << "Correo"
                      << std::setw(10) << "Mesa"
                      << std::setw(20) << "Fecha y Hora" << std::endl;
            std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;

            for (const auto& reserva : reservas) {
                std::cout << std::setfill(' ') << std::left 
                          << std::setw(15) << reserva->getCliente().getCedula()
                          << std::setw(20) << reserva->getCliente().getNombre()
                          << std::setw(15) << reserva->getCliente().getTelefono()
                          << std::setw(25) << reserva->getCliente().getEmail()
                          << std::setw(10) << reserva->getIdMesa()
                          << std::setw(20) << reserva->getFechaHora() << std::endl;
            }
        }
        std::cout << std::setw(100) << std::setfill('=') << "" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al mostrar las reservas: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al mostrar las reservas." << std::endl;
    }
}

bool ReservaManager::mostrarReservasPorCedula(const std::string& cedula) {
    try {
        // Recargar reservas desde el archivo antes de mostrarlas
        Calendario calendario;
        GrafoDisponibilidad grafo;
        ArbolClientes arbolClientes;
        cargarReservas(calendario, grafo, arbolClientes);

        std::cout << std::setw(100) << std::setfill('=') << "" << std::endl;
        std::cout << std::setw(50) << std::setfill(' ') << "RESERVAS DEL CLIENTE CON CÉDULA " << cedula << std::endl;
        std::cout << std::setw(100) << std::setfill('=') << "" << std::endl;

        bool found = false;
        int index = 1;
        std::cout << std::setfill(' ')
                  << std::left << std::setw(5) << "No."
                  << std::setw(15) << "Cédula"
                  << std::setw(20) << "Nombre"
                  << std::setw(15) << "Teléfono"
                  << std::setw(20) << "Correo"
                  << std::setw(10) << "Mesa"
                  << std::setw(20) << "Fecha y Hora" << std::endl;
                  std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;

        for (const auto& reserva : reservas) {
            if (reserva->getCliente().getCedula() == cedula) {
                std::cout << std::setfill(' ')
                          << std::left << std::setw(5) << index
                          << std::setw(15) << reserva->getCliente().getCedula()
                          << std::setw(20) << reserva->getCliente().getNombre()
                          << std::setw(15) << reserva->getCliente().getTelefono()
                          << std::setw(20) << reserva->getCliente().getEmail()
                          << std::setw(10) << reserva->getIdMesa()
                          << std::setw(20) << reserva->getFechaHora() << std::endl;
                found = true;
                index++;
            }
        }
        if (!found) {
            std::cout << "No se encontraron reservas para el cliente con cédula: " << cedula << std::endl;
        }
        std::cout << std::setw(100) << std::setfill('=') << "" << std::endl;
        return found;
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al mostrar las reservas por cédula: " << e.what() << std::endl;
        return false;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al mostrar las reservas por cédula." << std::endl;
        return false;
    }
}

void ReservaManager::cancelarReservaPorCedula(Calendario& calendario, ArbolClientes& arbolClientes, GrafoDisponibilidad& grafo) {
    try {
        std::string cedula;
        std::cout << "🔢 Ingrese la cédula del cliente: ";
        cedula = Validaciones::validarCedulaReal();

        if (!mostrarReservasPorCedula(cedula)) {
            return;
        }

        std::string opcionStr;
        std::cout << "Seleccione el número de la reserva que desea cancelar (o digite 0 para regresar al menu): ";
        opcionStr = Validaciones::validarSoloNumeros(2); // Assuming the option number is at most 2 digits
        int opcion = std::stoi(opcionStr);

        if (opcion == 0) {
            std::cout << "Operación cancelada." << std::endl;
            return;
        }

        int index = 1;
        for (auto it = reservas.begin(); it != reservas.end(); ++it) {
            if ((*it)->getCliente().getCedula() == cedula) {
                if (index == opcion) {
                    std::string fechaHora = (*it)->getFechaHora();
                    int idMesa = (*it)->getIdMesa();
                    calendario.eliminarReserva(cedula, idMesa, fechaHora);
                    grafo.eliminarReserva(idMesa, fechaHora);
                    delete *it;
                    it = reservas.erase(it);
                    guardarReservas();
                    std::cout << "Reserva cancelada exitosamente." << std::endl;

                    bool hasMoreReservations = false;
                    for (const auto& reserva : reservas) {
                        if (reserva->getCliente().getCedula() == cedula) {
                            hasMoreReservations = true;
                            break;
                        }
                    }

                    if (!hasMoreReservations) {
                        arbolClientes.eliminarCliente(cedula);
                    }
                    return;
                }
                index++;
            }
        }

        std::cout << "Opción no válida." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al cancelar la reserva por cédula: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al cancelar la reserva por cédula." << std::endl;
    }
}

std::vector<Reserva*>& ReservaManager::getReservas() {
    return reservas;
}