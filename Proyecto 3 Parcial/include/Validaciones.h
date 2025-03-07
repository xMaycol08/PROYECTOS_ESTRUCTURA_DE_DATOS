#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>

class Validaciones {
public:
    static std::string validarNombre();
    static std::string validarNumeroTelefono(); // New method declaration
    static std::string validarMesa();
    static std::string validarCorreo();
    static std::string validarFechaHora();
    static std::string validarCedulaReal();
    static std::string validarSoloNumeros(int longitud);
    static std::string validarSiNo(); // New method declaration

private:
    static std::string capitalizarNombre(const std::string& nombre);
};

#endif // VALIDACIONES_H
