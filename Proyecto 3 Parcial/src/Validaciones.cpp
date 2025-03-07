#include "../include/Validaciones.h"
#include <regex>
#include <iostream>
#include <conio.h> // For getch() on Windows
#include <cctype>  // For isalpha, toupper, tolower
#include <ctime>
#include <sstream>
#include <iomanip>  // Para std::get_time



std::string Validaciones::validarCedulaReal()
{
    try {
        std::string cedula;

        while (true)
        {
            cedula.clear();
            char ch;

            // Capturar solo números y permitir backspace
            while (true)
            {
                ch = _getch();
                if (ch >= '0' && ch <= '9' && cedula.length() < 10) // Solo números permitidos y máximo 10 caracteres
                {
                    std::cout << ch; // Mostrar el número ingresado
                    cedula += ch;
                }
                else if (ch == 8 && !cedula.empty()) // Permitir Backspace
                {
                    std::cout << "\b \b"; // Borra en pantalla
                    cedula.pop_back();
                }
                else if (ch == '\r' && cedula.length() == 10) // Enter solo si la cédula tiene 10 dígitos
                {
                    break;
                }
            }
            std::cout << std::endl; // Salto de línea después de la entrada

            // Verificar longitud exacta
            if (cedula.length() != 10)
            {
                std::cout << "Error: La cédula debe contener exactamente 10 dígitos.\n";
            }
            else
            {
                // Validación del código de provincia
                int provincia = std::stoi(cedula.substr(0, 2));
                if (provincia < 1 || provincia > 24)
                {
                    std::cout << "Error: La cédula tiene un código de provincia inválido.\n";
                }
                else
                {
                    // Validación del dígito verificador
                    int digitoVerificador = cedula[9] - '0';
                    int suma = 0;

                    for (int i = 0; i < 9; i++)
                    {
                        int digito = cedula[i] - '0';
                        if (i % 2 == 0)
                        { // Posiciones impares
                            digito *= 2;
                            if (digito > 9)
                                digito -= 9;
                        }
                        suma += digito;
                    }

                    int decenaSuperior = (suma + 9) / 10 * 10;
                    int calculado = decenaSuperior - suma;

                    if (calculado == digitoVerificador)
                    {
                        return cedula; // Retorna la cédula válida
                    }
                    else
                    {
                        std::cout << "Error: La cédula no es válida.\n";
                    }
                }
            }

            // Mensaje de reintento solo después de un error
            std::cout << "Ingrese la cédula del cliente: ";
        }
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al validar la cédula: " << e.what() << std::endl;
        return "";
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al validar la cédula." << std::endl;
        return "";
    }
}

std::string Validaciones::validarNombre()
{
    try {
        std::string nombre;
        char c;

        while (true)
        {

            while (true)
            {
                c = _getch(); // Captura el carácter sin mostrarlo en pantalla

                // Permitir letras mayúsculas y minúsculas sin acentos
                if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
                {
                    std::cout << c; // Mostrar en pantalla
                    nombre += c;
                }
                // Permitir espacio solo si no está al inicio o repetido
                else if (c == ' ' && !nombre.empty() && nombre.back() != ' ')
                {
                    std::cout << c;
                    nombre += c;
                }
                // Permitir Backspace para borrar caracteres
                else if (c == 8 && !nombre.empty())
                {
                    std::cout << "\b \b"; // Borra en pantalla
                    nombre.pop_back();
                }
                // Permitir Enter solo si el nombre tiene al menos 3 caracteres
                else if (c == 13)
                {
                    if (nombre.empty() || std::all_of(nombre.begin(), nombre.end(), isspace))
                    {
                        std::cout << "\nError: El campo nombre no puede estar vacío o contener solo espacios.\n";
                        nombre.clear();
                        std::cout << "Ingrese el nombre del cliente: ";
                        break;
                    }
                    else if (nombre.length() >= 3)
                    {
                        std::cout << std::endl;
                        return capitalizarNombre(nombre);
                    }
                    else
                    {
                        std::cout << "\nError: El nombre debe tener al menos 3 caracteres.\n";
                        nombre.clear();
                        std::cout << "Ingrese el nombre del cliente: ";
                        break;
                    }
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al validar el nombre: " << e.what() << std::endl;
        return "";
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al validar el nombre." << std::endl;
        return "";
    }
}

std::string Validaciones::capitalizarNombre(const std::string &nombre)
{
    std::string resultado = nombre;
    bool nuevoInicio = true;

    for (size_t i = 0; i < resultado.length(); i++)
    {
        if (nuevoInicio && isalpha(resultado[i]))
        {
            resultado[i] = toupper(resultado[i]); // Primera letra en mayúscula
            nuevoInicio = false;
        }
        else
        {
            resultado[i] = tolower(resultado[i]); // Resto en minúsculas
        }

        if (resultado[i] == ' ')
        {
            nuevoInicio = true; // Nueva palabra detectada
        }
    }

    return resultado;
}

std::string Validaciones::validarNumeroTelefono()
{
    try {
        std::string telefono;
        char c;

        while (true)
        {

            while (true)
            {
                c = _getch(); // Captura el carácter sin mostrarlo en pantalla

                // Permitir solo números del 0 al 9
                if (c >= '0' && c <= '9' && telefono.length() < 10)
                {
                    std::cout << c; // Mostrar en pantalla
                    telefono += c;
                }
                // Permitir Backspace para borrar caracteres
                else if (c == 8 && !telefono.empty())
                {
                    std::cout << "\b \b"; // Borra en pantalla
                    telefono.pop_back();
                }
                // Permitir Enter solo si el número tiene 10 dígitos y empieza con "09"
                else if (c == 13)
                {
                    if (telefono.empty() || std::all_of(telefono.begin(), telefono.end(), isspace))
                    {
                        std::cout << "\nError: El campo teléfono no puede estar vacío o contener solo espacios.\n";
                        telefono.clear();
                        std::cout << "Ingrese el teléfono del cliente: ";
                        break;
                    }
                    else if (telefono.length() == 10 && telefono.substr(0, 2) == "09")
                    {
                        std::cout << std::endl;
                        return telefono;
                    }
                    else
                    {
                        std::cout << "\nError: El número debe tener 10 dígitos y empezar con '09'.\n";
                        telefono.clear();
                        std::cout << "Ingrese el teléfono del cliente: ";
                        break;
                    }
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al validar el número de teléfono: " << e.what() << std::endl;
        return "";
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al validar el número de teléfono." << std::endl;
        return "";
    }
}

std::string Validaciones::validarMesa()
{
    try {
        std::string input;
        char ch;

        while (true)
        {

            while (true)
            {
                ch = _getch();

                if (ch == '\r') // Enter para validar
                {
                    if (input.empty() || std::all_of(input.begin(), input.end(), isspace))
                    {
                        std::cout << std::endl
                                  << "Error: El campo no puede estar vacío.\n";
                        input.clear();
                        std::cout << "Ingrese el número de la mesa (1-5): ";
                        break;
                    }

                    std::cout << std::endl;
                    return input;
                }

                else if (ch == '\b' && !input.empty()) // Backspace
                {
                    std::cout << "\b \b";
                    input.pop_back();
                }

                else if (ch >= '1' && ch <= '5' && input.empty()) // Solo permite 1-5 y solo un dígito
                {
                    std::cout << ch;
                    input += ch;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al validar la mesa: " << e.what() << std::endl;
        return "";
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al validar la mesa." << std::endl;
        return "";
    }
}

//validacion correo
std::string Validaciones::validarCorreo()
{
    try {
        std::string correo;
        char ch;
        bool tieneArroba = false;

        while (true)
        {
            correo.clear();
            tieneArroba = false;

            while (true)
            {
                ch = _getch();

                if (ch == 13) // Enter para validar
                {
                    if (correo.empty() || std::all_of(correo.begin(), correo.end(), isspace))
                    {
                        std::cout << "\nError: El campo correo no puede estar vacío.";
                        break;
                    }

                    if (correo.front() == '.' || correo.front() == '-' || correo.front() == '_')
                    {
                        std::cout << "\nError: El correo no puede comenzar con '.', '-', o '_'.";
                        break;
                    }

                    if (correo.find("..") != std::string::npos || correo.find("--") != std::string::npos ||
                        correo.find("__") != std::string::npos || correo.find("._") != std::string::npos ||
                        correo.find("-.") != std::string::npos || correo.find("-_") != std::string::npos ||
                        correo.find("_.") != std::string::npos || correo.find("_-") != std::string::npos)
                    {
                        std::cout << "\nError: No se permiten caracteres especiales juntos ('..', '--', '__', '._', '-.', '-_', '_.', '_-').";
                        break;
                    }

                    if (!tieneArroba)
                    {
                        std::cout << "\nError: El correo debe contener un '@'.";
                        break;
                    }

                    size_t posArroba = correo.find('@');
                    size_t posPunto = correo.find('.', posArroba);

                    if (posPunto == std::string::npos)
                    {
                        std::cout << "\nError: El correo debe contener un '.' después del '@'.";
                        break;
                    }

                    // Validación de dominios permitidos
                    std::regex patronCorreo(R"(^[a-zA-Z0-9._+-]+@((gmail\.com|outlook\.com|yahoo\.com|hotmail\.com)|(yahoo\.es|hotmail\.es))$)");
                    if (!std::regex_match(correo, patronCorreo))
                    {
                        std::cout << "\nError: Solo se permiten correos de Gmail, Outlook y Yahoo con '.com'. Además, solo Hotmail y Yahoo pueden tener '.es'.";
                        break;
                    }

                    std::cout << std::endl;
                    return correo;
                }

                else if (ch == 8 && !correo.empty()) // Backspace
                {
                    if (correo.back() == '@')
                        tieneArroba = false;
                    correo.pop_back();
                    std::cout << "\b \b";
                }

                else if ((isalnum(ch) || ch == '.' || ch == '@' || ch == '_' || ch == '-' || ch == '+') && correo.length() < 50)
                {
                    if (ch == '@')
                    {
                        if (tieneArroba)
                            continue; // Evita múltiples '@'
                        tieneArroba = true;
                    }

                    correo += ch;
                    std::cout << ch;
                }
            }

            // Muestra el mensaje de "Ingrese el email" solo después del error
            std::cout << "\nIngrese el email del cliente: ";
        }
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al validar el correo: " << e.what() << std::endl;
        return "";
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al validar el correo." << std::endl;
        return "";
    }
}

std::string Validaciones::validarFechaHora()
{
    try {
        std::string fechaHora;
        char ch;
        
        while (true) {
            fechaHora.clear(); // Reinicia la variable en cada intento

            while (true) {
                ch = _getch();

                if (ch == 13) { // Enter para validar
                    std::cout << std::endl;

                    if (fechaHora.empty() || std::all_of(fechaHora.begin(), fechaHora.end(), isspace)) {
                        std::cout << "ERROR: La fecha y hora no puede estar vacía." << std::endl;
                        break;
                    }

                    if (fechaHora.length() != 16) {
                        std::cout << "ERROR: El formato debe ser exactamente 'YYYY-MM-DD HH:MM'." << std::endl;
                        break;
                    }

                    std::regex patronFechaHora(R"(^\d{4}-\d{2}-\d{2} \d{2}:\d{2}$)");
                    if (!std::regex_match(fechaHora, patronFechaHora)) {
                        std::cout << "ERROR: Formato de fecha y hora inválido." << std::endl;
                        break;
                    }

                    std::istringstream ss(fechaHora);
                    std::tm tmFechaHora = {};
                    ss >> std::get_time(&tmFechaHora, "%Y-%m-%d %H:%M");

                    if (ss.fail()) {
                        std::cout << "ERROR: Fecha y hora incorrecta." << std::endl;
                        break;
                    }

                    // Validar años bisiestos
                    int year = tmFechaHora.tm_year + 1900;
                    int month = tmFechaHora.tm_mon + 1;
                    int day = tmFechaHora.tm_mday;

                    if (month == 2 && day == 29) {
                        if ((year % 4 != 0) || (year % 100 == 0 && year % 400 != 0)) {
                            std::cout << "ERROR: El año ingresado no es bisiesto." << std::endl;
                            break;
                        }
                    }

                    // Validar que los minutos sean 00
                    if (tmFechaHora.tm_min != 0) {
                        std::cout << "ERROR: Las reservas solo pueden hacerse en la hora exacta (por ejemplo, 12:00, 13:00)." << std::endl;
                        break;
                    }

                    // Validar que la hora esté entre las 10:00 y las 22:00
                    if (tmFechaHora.tm_hour < 10 || tmFechaHora.tm_hour > 22) {
                        std::cout << "ERROR: La hora debe estar entre las 10:00 y las 22:00." << std::endl;
                        break;
                    }

                    // Obtener la fecha y hora actual del sistema
                    std::time_t t = std::time(nullptr);
                    std::tm tmActual = *std::localtime(&t);

                    // Comparar la fecha y hora ingresada con la actual
                    if (std::mktime(&tmFechaHora) < std::mktime(&tmActual)) {
                        if (tmFechaHora.tm_year == tmActual.tm_year &&
                            tmFechaHora.tm_mon == tmActual.tm_mon &&
                            tmFechaHora.tm_mday == tmActual.tm_mday &&
                            (tmFechaHora.tm_hour > tmActual.tm_hour ||
                             (tmFechaHora.tm_hour == tmActual.tm_hour && tmFechaHora.tm_min >= tmActual.tm_min))) {
                            return fechaHora; // La fecha es válida, se retorna
                        } else {
                            std::cout << "ERROR: No se puede ingresar una fecha y hora pasada." << std::endl;
                            break;
                        }
                    }

                    // Validar que la fecha no sea más de 3 años en el futuro
                    std::tm tmMaxFecha = tmActual;
                    tmMaxFecha.tm_year += 3; // Añadir 3 años
                    if (std::mktime(&tmFechaHora) > std::mktime(&tmMaxFecha)) {
                        std::cout << "ERROR: La fecha y hora no puede ser más de 3 años en el futuro." << std::endl;
                        break;
                    }

                    return fechaHora; // La fecha es válida, se retorna
                }
                else if (ch == 8) { // Backspace
                    if (!fechaHora.empty()) {
                        std::cout << "\b \b"; // Borra solo el último carácter en pantalla
                        fechaHora.pop_back();
                    }
                }
                else if ((isdigit(ch) || ch == '-' || ch == ' ' || ch == ':') && fechaHora.length() < 16) {
                    fechaHora += ch;
                    std::cout << ch;
                }
            }

            // Mensaje de reingreso después de un error
            std::cout << "\nIngrese nuevamente la fecha y hora: ";
        }
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al validar la fecha y hora: " << e.what() << std::endl;
        return "";
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al validar la fecha y hora." << std::endl;
        return "";
    }
}

std::string Validaciones::validarSoloNumeros(int longitud)
{
    try {
        std::string input;
        char ch;

        while (true)
        {
            input.clear();

            while (true)
            {
                ch = _getch();

                if (ch == 13) // Enter para validar
                {
                    if (input.empty())
                    {
                        std::cout << "\nError: El campo no puede estar vacío.";
                        break;
                    }
                    std::cout << std::endl;
                    return input;
                }
                else if (ch == 8 && !input.empty()) // Backspace
                {
                    std::cout << "\b \b";
                    input.pop_back();
                }
                else if (ch >= '0' && ch <= '9' && input.length()< longitud) // Solo números permitidos
                {
                    std::cout << ch;
                    input += ch;
                }
            }

            // Mensaje de reingreso después de un error
            std::cout << "\nIngrese nuevamente el campo: ";
        }
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al validar el campo: " << e.what() << std::endl;
        return "";
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al validar el campo." << std::endl;
        return "";
    }
}

std::string Validaciones::validarSiNo()
{
    try {
        std::string input;
        char ch;

        while (true)
        {
            input.clear();

            while (true)
            {
                ch = _getch();

                if (ch == 13) // Enter para validar
                {
                    if (input == "Y" || input == "y" || input == "N" || input == "n")
                    {
                        std::cout << std::endl;
                        return input;
                    }
                    else
                    {
                        std::cout << "\nError: Solo se permite 'Y' o 'N'.";
                        break;
                    }
                }
                else if (ch == 8 && !input.empty()) // Backspace
                {
                    std::cout << "\b \b";
                    input.pop_back();
                }
                else if ((ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n') && input.empty()) // Solo permite 'Y', 'y', 'N', 'n'
                {
                    std::cout << ch;
                    input += ch;
                }
            }

            // Mensaje de reingreso después de un error
            std::cout << "\nIngrese nuevamente (Y/N): ";
        }
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al validar la entrada: " << e.what() << std::endl;
        return "";
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al validar la entrada." << std::endl;
        return "";
    }
}
