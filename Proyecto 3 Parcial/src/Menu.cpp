#include "../include/Menu.h"
#include "../include/Reserva.h"
#include "../include/Utils.h"
#include "../include/Validaciones.h"
#include <iomanip>
#include <sstream>
#include <algorithm> // Include this header for std::find

void Menu::gestionarReservas(Calendario &calendario, ArbolClientes &arbolClientes, GrafoDisponibilidad &grafo, DataManager &dataManager, std::vector<Reserva*> &reservas)
{
    try {
        // Cargar clientes desde el DataManager al arbolClientes
        dataManager.cargarClientes(arbolClientes);

        std::string cedula, nombre, telefono, email;
        int idMesa;
        std::string fechaHoraStr;

        std::cout << "🔢 Ingrese la cédula del cliente: ";
        cedula = Validaciones::validarCedulaReal();

        // Verificar si el cliente ya existe
        Cliente clienteExistente = arbolClientes.buscarPorCedula(cedula);
        if (!clienteExistente.getCedula().empty())
        {
            std::cout << "Cliente existente encontrado. Usando información del cliente.\n";
            nombre = clienteExistente.getNombre();
            telefono = clienteExistente.getTelefono();
            email = clienteExistente.getEmail();
        }
        else
        {
            std::cout << "👤 Ingrese el nombre del cliente: ";                 
            nombre = Validaciones::validarNombre();
            std::cout << "📞 Ingrese el teléfono del cliente: ";
            telefono = Validaciones::validarNumeroTelefono();
            std::cout << "📧 Ingrese el email del cliente: ";
            email = Validaciones::validarCorreo();
        }

        std::cout << "🍽️ Ingrese el número de la mesa (1-5): ";
        idMesa = std::stoi(Validaciones::validarMesa());

        while (true) {
            std::cout << "📅 Ingrese la fecha y hora (YYYY-MM-DD HH:MM): ";
            fechaHoraStr = Validaciones::validarFechaHora();

            // Obtener la fecha y hora actual del sistema
            std::time_t t = std::time(nullptr);
            std::tm tmActual = *std::localtime(&t);

            // Convertir la fecha y hora ingresada a std::tm
            std::istringstream ss(fechaHoraStr);
            std::tm tmFechaHora = {};
            ss >> std::get_time(&tmFechaHora, "%Y-%m-%d %H:%M");

            // Comparar la fecha y hora ingresada con la actual
            if (std::mktime(&tmFechaHora) < std::mktime(&tmActual)) {
                std::cout << "ERROR: No se puede ingresar una fecha y hora pasada. Intente nuevamente.\n";
            } else {
                break; // La fecha y hora es válida, salir del bucle
            }
        }

        // Verificar si la mesa está disponible en la fecha y hora especificada
        std::vector<int> disponibles = grafo.obtenerMesasDisponibles(fechaHoraStr);
        if (std::find(disponibles.begin(), disponibles.end(), idMesa) == disponibles.end())
        {
            std::cerr << "⚠️ La mesa ya está reservada en esa fecha y hora." << std::endl;
            std::cout << "Iniciando búsqueda de disponibilidad mediante backtracking...\n";

            // Implementar backtracking para encontrar la mesa disponible más cercana
            int nuevaMesa = -1;
            for (int i = idMesa - 1; i >= 1; --i) {
                if (std::find(disponibles.begin(), disponibles.end(), i) != disponibles.end()) {
                    nuevaMesa = i;
                    break;
                }
            }
            if (nuevaMesa == -1) {
                for (int i = idMesa + 1; i <= 5; ++i) {
                    if (std::find(disponibles.begin(), disponibles.end(), i) != disponibles.end()) {
                        nuevaMesa = i;
                        break;
                    }
                }
            }

            if (nuevaMesa != -1) {
                char respuesta;
                std::cout << "Desea reservar en el mismo horario la mesa " << nuevaMesa << "? [Y/N]: ";
                respuesta = Validaciones::validarSiNo()[0];
                if (respuesta == 'Y' || respuesta == 'y') {
                    idMesa = nuevaMesa;
                } else {
                    std::cout << "Reserva cancelada.\n";
                    return;
                }
            } else {
                std::cout << "No se encontraron mesas disponibles en el mismo horario.\n";
                return;
            }
        }

        // Registrar el nuevo cliente
        Cliente nuevoCliente(cedula, nombre, telefono, email);
        arbolClientes.insertar(nuevoCliente);
        Reserva* nuevaReserva = new Reserva(cedula, nombre, telefono, email, idMesa, fechaHoraStr);
        calendario.agregarReserva(*nuevaReserva);
        grafo.agregarReserva(idMesa, fechaHoraStr); // Asegurarse de actualizar el grafo de disponibilidad
        dataManager.guardarReservas(calendario);
        std::cout << "🎉 Reserva registrada con éxito." << std::endl;
        // Actualizar la lista de reservas en tiempo de ejecución
        reservas.push_back(nuevaReserva);
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al gestionar las reservas: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al gestionar las reservas." << std::endl;
    }
}






