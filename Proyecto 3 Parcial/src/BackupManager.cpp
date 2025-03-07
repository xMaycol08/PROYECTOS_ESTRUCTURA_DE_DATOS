#include "../include/BackupManager.h"
#include "../include/ReservaManager.h" // Incluir ReservaManager para recargar reservas
#include "../include/Validaciones.h"
#include "../include/Calendario.h"
#include "../include/GrafoDisponibilidad.h" 
#include "../include/ArbolClientes.h"// Incluir Validaciones para validar entradas
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <vector>
#include <algorithm>
#include <windows.h> // Incluir para CreateDirectory y FindFirstFile, FindNextFile

void BackupManager::hacerBackup(const std::string& directorio) {
    try {
        // Crear la carpeta "backups" si no existe
        if (CreateDirectory(directorio.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
            std::ifstream src("reservas.txt", std::ios::binary);
            
            // Verificar si el archivo está vacío
            if (!src || src.peek() == std::ifstream::traits_type::eof()) {
                std::cerr << "No hay datos para hacer backup." << std::endl;
                return;
            }

            std::string fechaHora = obtenerFechaHoraActual();
            std::string backupFile = directorio + "/" + fechaHora + ".txt";
            std::ofstream dst(backupFile, std::ios::binary);

            if (!dst) {
                std::cerr << "Error al crear el backup." << std::endl;
                return;
            }

            dst << src.rdbuf();
            std::cout << "Backup creado exitosamente: " << backupFile << std::endl;
        } else {
            std::cerr << "Error al crear el directorio de backups." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al hacer el backup: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al hacer el backup." << std::endl;
    }
}

void BackupManager::recuperarBackup(const std::string& directorio) {
    try {
        
        std::vector<std::string> backups;
        WIN32_FIND_DATA findFileData;
        HANDLE hFind = FindFirstFile((directorio + "\\*.txt").c_str(), &findFileData);

        if (hFind == INVALID_HANDLE_VALUE) {
            std::cerr << "No hay backups disponibles." << std::endl;
            return;
        } else {
            do {
                backups.push_back(findFileData.cFileName);
            } while (FindNextFile(hFind, &findFileData) != 0);
            FindClose(hFind);
        }

        if (backups.empty()) {
            std::cerr << "No hay backups disponibles." << std::endl;
            return;
        }

        std::sort(backups.begin(), backups.end());
        std::cout << "Backups disponibles:" << std::endl;
        for (size_t i = 0; i < backups.size(); ++i) {
            std::cout << i + 1 << ". " << backups[i] << std::endl;
        }

        Validaciones validador;
        std::string opcionStr;
        int opcion;

        while (true) {
            std::cout << "Seleccione el número del backup que desea recuperar (0 para cancelar): ";
            opcionStr = validador.validarSoloNumeros(2); // Asumiendo que no habrá más de 99 backups
            opcion = std::stoi(opcionStr);

            if (opcion == 0) {
                std::cout << "Acción cancelada." << std::endl;
                return;
            } else if (opcion >= 1 && opcion <= static_cast<int>(backups.size())) {
                break;
            } else {
                std::cerr << "Opción no válida." << std::endl;
            }
        }
        std::string backupFile = directorio + "/" + backups[opcion - 1];
        std::ifstream src(backupFile, std::ios::binary);
        std::ofstream dst("reservas.txt", std::ios::binary);

        if (!src || !dst) {
            std::cerr << "Error al recuperar el backup."<< std::endl;
            return;
        }

        dst << src.rdbuf();
        std::cout << "Backup recuperado exitosamente: " << backupFile << std::endl;

        // Limpiar estructuras de datos antes de recargar reservas
        ReservaManager::liberarMemoria();
        Calendario calendario;
        GrafoDisponibilidad grafo;
        ArbolClientes arbolClientes;
        calendario.limpiarReservas();
        grafo.limpiarReservas();
        arbolClientes.limpiarClientes();

        // Recargar reservas después de recuperar el backup
        ReservaManager::cargarReservas(calendario, grafo, arbolClientes);
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al recuperar el backup: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al recuperar el backup." << std::endl;
    }
}

std::string BackupManager::obtenerFechaHoraActual() {
    try {
        std::time_t now = std::time(nullptr);
        std::tm* ltm = std::localtime(&now);
        char buffer[30];
        std::strftime(buffer, sizeof(buffer), "%a %b %d %H.%M.%S %Y", ltm);
        return std::string(buffer);
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al obtener la fecha y hora actual: " << e.what() << std::endl;
        return "";
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al obtener la fecha y hora actual." << std::endl;
        return "";
    }
}