#pragma once

#include <string>
#include <vector>

class BackupManager {
public:
    static void crearBackupConFecha(const std::string& carpeta, const std::string& archivoOriginal);
    static void restaurarBackup(const std::string& carpeta, const std::string& archivoBackup, const std::string& archivoDestino);
    static std::vector<std::string> listarArchivosEnCarpeta(const std::string& carpeta); // M�todo para listar archivos

private:
    static std::string obtenerFechaHora(); // Obtener la fecha y hora actual como string
};
