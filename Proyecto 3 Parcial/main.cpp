#include <iostream>
#include "include/Menu.h"
#include "include/Calendario.h"
#include "include/ArbolClientes.h"
#include "include/GrafoDisponibilidad.h"
#include "include/DataManager.h"
#include "include/Validaciones.h"
#include "include/ReservaManager.h"
#include "include/Utils.h"
#include "include/BackupManager.h" // Include BackupManager header
#include <windows.h>
#include <algorithm> // Include algorithm for std::sort
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include "include/pdf_generator.h"
#include "include/Reserva.h"
#include "include/ComplexityAnalyzer.h" // Include ComplexityAnalyzer

int main()
{
    try
    {
        const std::string inputFile = "reservas.txt";
        const std::string backupDir = "./backups"; // Backup directory
        Calendario calendario;
        ArbolClientes arbolClientes;
        GrafoDisponibilidad grafo;
        DataManager dataManager;

        // Configurar la consola para usar UTF-8
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);

        // Cargar reservas previas desde el archivo
        ReservaManager::cargarReservas(calendario, grafo, arbolClientes);

        int opcion;
        do
        {
            mostrarMenu(opcion); // Use the mostrarMenu function

            std::string cedula;
            std::string fechaHoraStr;
            switch (opcion)
            {
            case 1:
                Menu::gestionarReservas(calendario, arbolClientes, grafo, dataManager, ReservaManager::getReservas());
                break;
            case 2:
                ReservaManager::cargarReservas(calendario, grafo, arbolClientes);
                std::cout << "📅 Ingrese la fecha y hora (YYYY-MM-DD HH:MM): ";
                fechaHoraStr = Validaciones::validarFechaHora();
                grafo.mostrarDisponibilidad(fechaHoraStr, ReservaManager::getReservas());
                break;
            case 3:
                if (ReservaManager::getReservas().empty())
                {
                    std::cout << "📭 No hay reservas para cancelar." << std::endl;
                }
                else
                {
                    ReservaManager::cancelarReservaPorCedula(calendario, arbolClientes, grafo); // Use the updated method
                }
                break;
            case 4:
                if (ReservaManager::getReservas().empty())
                {
                    std::cout << "📂 No hay reservas para mostrar." << std::endl;
                }
                else
                {
                    ReservaManager::mostrarReservas();
                }
                break;
            case 5:
                if (ReservaManager::getReservas().empty())
                {
                    std::cout << "📂 No hay reservas para mostrar por cédula." << std::endl;
                }
                else
                {
                    std::cout << "🔢 Ingrese la cédula del cliente: ";
                    cedula = Validaciones::validarCedulaReal();
                    ReservaManager::mostrarReservasPorCedula(cedula);
                }
                break;
            case 6:
                if (ReservaManager::getReservas().empty())
                {
                    std::cout << "📂 No hay reservas para buscar cliente." << std::endl;
                }
                else
                {
                    std::cout << "🔢 Ingrese la cédula del cliente: ";
                    cedula = Validaciones::validarCedulaReal();
                    arbolClientes.buscarPorCedulaYMostrar(cedula);
                }
                break;
            case 7:
                if (ReservaManager::getReservas().empty())
                {
                    std::cout << "📂 No hay registros para generar en PDF." << std::endl;
                }
                else
                {
                    std::cout << "Generando reservas en PDF..." << std::endl;
                    createPDF(inputFile);
                }
                break;
            case 8:
                BackupManager::hacerBackup(backupDir);
                break;
            case 9:
                BackupManager::recuperarBackup(backupDir);
                ReservaManager::liberarMemoria();
                calendario.limpiarReservas();
                grafo.limpiarReservas();
                arbolClientes.limpiarClientes();
                ReservaManager::cargarReservas(calendario, grafo, arbolClientes);
                break;
            case 10:
                // Abrir el archivo de ayuda
                system("start Help.chm");
                break;
            case 11:
                std::cout << "🔚 Saliendo del sistema..." << std::endl;
                break;
            default:
                std::cout << "❌ Opción no válida, intente de nuevo." << std::endl;
            }
            system("pause");

        } while (opcion != 11);

        // Guardar reservas en el archivo antes de salir
        ReservaManager::guardarReservas();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Se produjo una excepción: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Se produjo una excepción desconocida." << std::endl;
    }

    return 0;
}