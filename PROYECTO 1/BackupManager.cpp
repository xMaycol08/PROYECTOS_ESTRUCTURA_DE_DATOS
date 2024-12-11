#include "BackupManager.h"
#include <iostream>
#include <vector>
#include <dirent.h> // Para manejo de directorios en sistemas compatibles con POSIX

std::vector<std::string> BackupManager::listarArchivosEnCarpeta(const std::string& carpeta) {
    std::vector<std::string> archivos;
    DIR* dir;
    struct dirent* entry;

    dir = opendir(carpeta.c_str());
    if (!dir) {
        std::cerr << "Error: No se pudo abrir la carpeta " << carpeta << "\n";
        return archivos;
    }

    while ((entry = readdir(dir)) != nullptr) {
        std::string nombreArchivo = entry->d_name;
        if (nombreArchivo != "." && nombreArchivo != "..") {
            archivos.push_back(nombreArchivo);
        }
    }

    closedir(dir);
    return archivos;
}
