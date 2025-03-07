#ifndef BACKUPMANAGER_H
#define BACKUPMANAGER_H

#include <string>

class BackupManager {
public:
    static void hacerBackup(const std::string& directorio);
    static void recuperarBackup(const std::string& directorio);
private:
    static std::string obtenerFechaHoraActual();
};

#endif // BACKUPMANAGER_H