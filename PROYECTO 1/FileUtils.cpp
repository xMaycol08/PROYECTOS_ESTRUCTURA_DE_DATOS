#include "FileUtils.h"
#include <iostream>
#include <dirent.h> // Para trabajar con directorios POSIX
#include <vector>
#include <string>

// Funci�n para listar archivos en una carpeta
std::vector<std::string> listarArchivosEnCarpeta(const std::string& carpeta) {
    std::vector<std::string> archivos;
    DIR* dir = opendir(carpeta.c_str()); // Abrir el directorio

    if (!dir) {
        std::cerr << "Error: No se pudo abrir el directorio " << carpeta << "\n";
        return archivos;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string nombreArchivo = entry->d_name;
        // Ignorar los nombres "." y ".."
        if (nombreArchivo != "." && nombreArchivo != "..") {
            archivos.push_back(nombreArchivo);
        }
    }
    closedir(dir); // Cerrar el directorio
    return archivos;
}

// Funci�n para mostrar los archivos en consola
void mostrarArchivos(const std::string& carpeta) {
    std::vector<std::string> archivos = listarArchivosEnCarpeta(carpeta);
    if (archivos.empty()) {
        std::cout << "No hay archivos en la carpeta " << carpeta << ".\n";
        return;
    }
    std::cout << "Archivos en la carpeta " << carpeta << ":\n";
    for (const auto& archivo : archivos) {
        std::cout << "- " << archivo << "\n";
    }
}
