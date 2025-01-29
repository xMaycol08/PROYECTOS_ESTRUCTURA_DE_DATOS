/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Validaciones de entrada de datos                         *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          01/01/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/


#include "Validaciones.h"
#include <cctype>
#include <conio.h> // Para _getch()

// Validación de fecha
bool Validaciones::validarFecha(const string& fecha) {
    try {
        regex formatoFecha(R"(\d{2}-\d{2}-\d{4})");
        if (!regex_match(fecha, formatoFecha)) {
            cout << "Error: El formato de la fecha debe ser DD-MM-YYYY.\n";
            return false;
        }

        int dia, mes, anio;
        sscanf(fecha.c_str(), "%d-%d-%d", &dia, &mes, &anio);

        if (anio < 1900 || anio <= 0 || mes < 1 || mes > 12 || dia < 1 || dia > diasEnMes(mes, anio)) {
            cout << "Error: Fecha no válida. Ingrese nuevamente.\n";
            return false;
        }

        // Obtener la fecha actual
        time_t t = time(nullptr);
        tm* fechaActual = localtime(&t);

        int diaActual = fechaActual->tm_mday;
        int mesActual = fechaActual->tm_mon + 1;
        int anioActual = fechaActual->tm_year + 1900;

        // Verificar que la fecha ingresada no sea mayor a la actual
        if (anio > anioActual || (anio == anioActual && mes > mesActual) || (anio == anioActual && mes == mesActual && dia > diaActual)) {
            cout << "Error: La fecha no puede ser mayor a la fecha actual.\n";
            return false;
        }

        // Validar que la fecha de nacimiento sea al menos 5 años antes de la fecha actual
        if (anio > anioActual - 5 || (anio == anioActual - 5 && (mes > mesActual || (mes == mesActual && dia > diaActual)))) {
            cout << "Error: La fecha de nacimiento debe ser al menos 5 años antes de la fecha actual.\n";
            return false;
        }
        
        return true;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return false;
    }
}

// Validación de título y nombre
bool Validaciones::validarTituloNombre(const string& texto, const string& campo) {
    try {
        regex formatoTituloNombre(R"(([A-ZÁÉÍÓÚÑ][a-záéíóúñ]+)(\s[A-ZÁÉÍÓÚÑ][a-záéíóúñ]+)*)");
        if (texto.empty() || texto.find_first_not_of(' ') == string::npos) {
            cout << "Error: El campo " << campo << " no puede estar vacío o contener solo espacios.\n";
            return false;
        } else if (!regex_match(texto, formatoTituloNombre)) {
            cout << "Error: El campo " << campo << " debe comenzar con una letra mayúscula y las demas minúsculas.\n";
            return false;
        }
        return true;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return false;
    }
}

// Validación de título
bool Validaciones::validarTitulo(const string& texto, const string& campo) {
    try {
        regex formatoTitulo(R"(([A-ZÁÉÍÓÚÑa-záéíóúñ0-9#\+\-]+)(\s[A-ZÁÉÍÓÚÑa-záéíóúñ0-9#\+\-]+)*)");
        if (texto.empty() || texto.find_first_not_of(' ') == string::npos) {
            cout << "Error: El campo " << campo << " no puede estar vacío o contener solo espacios.\n";
            return false;
        } else if (!regex_match(texto, formatoTitulo)) {
            cout << "Error: El campo " << campo << " debe comenzar con una letra mayúscula, número o carácter especial permitido y cada palabra debe tener al menos una letra.\n";
            return false;
        }

        // Verificar que cada palabra comience con mayúscula y las demás letras sean minúsculas o caracteres especiales permitidos
        stringstream ss(texto);
        string palabra;
        while (ss >> palabra) {
            if (!isupper(palabra[0]) && !isdigit(palabra[0])) {
                cout << "Error: Cada palabra debe comenzar con una letra mayúscula o un número.\n";
                return false;
            }
            for (size_t i = 1; i < palabra.size(); ++i) {
                if (!islower(palabra[i]) && !isdigit(palabra[i]) && palabra[i] != '#' && palabra[i] != '+' && palabra[i] != '-') {
                    cout << "Error: Las letras después de la primera deben ser minúsculas o caracteres especiales permitidos.\n";
                    return false;
                }
            }
        }

        return true;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return false;
    }
}


bool Validaciones::validarFechaPublicacion(const string& fechaPub, const string& fechaNacAutor) {
    try {
        // Crear objetos Fecha a partir de las cadenas de texto
        Fecha fechaPublicacion = Fecha::crearDesdeCadena(fechaPub);
        Fecha fechaNacimiento = Fecha::crearDesdeCadena(fechaNacAutor);

        // Validar que ambas fechas sean válidas
        if (!Fecha::esFechaValida(fechaPublicacion.getDia(), fechaPublicacion.getMes(), fechaPublicacion.getAnio()) ||
            !Fecha::esFechaValida(fechaNacimiento.getDia(), fechaNacimiento.getMes(), fechaNacimiento.getAnio())) {
            cout << "Error: Una o ambas fechas no son válidas.\n";
            return false;
        }

        // Obtener la fecha actual
        time_t t = time(nullptr);
        tm* fechaActual = localtime(&t);

        int diaActual = fechaActual->tm_mday;
        int mesActual = fechaActual->tm_mon + 1;
        int anioActual = fechaActual->tm_year + 1900;

        // Verificar que la fecha ingresada no sea mayor a la actual
        if (fechaPublicacion.getAnio() > anioActual || (fechaPublicacion.getAnio() == anioActual && fechaPublicacion.getMes() > mesActual) || (fechaPublicacion.getAnio() == anioActual && fechaPublicacion.getMes() == mesActual && fechaPublicacion.getDia() > diaActual)) {
            cout << "Error: La fecha no puede ser mayor a la fecha actual.\n";
            return false;
        }

        // Comparar si la diferencia de años es menor a 4
        int diferenciaAnios = fechaPublicacion.getAnio() - fechaNacimiento.getAnio();
        if (diferenciaAnios < 4) {
            cout << "Error: La fecha de publicación debe ser al menos 4 años posterior al año de nacimiento del autor (" 
                << fechaNacimiento.getAnio() << ").\n";
            return false;
        }

        return true;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return false;
    }
}



bool Validaciones::validarIsbn(const string& isbn) {
    try {
        if (isbn.empty()) {
            cout << "Error: El ISBN no puede estar vacío.\n";
            return false;
        }

        // Validar formato de guiones
        if (isbn.front() == '-' || isbn.back() == '-') {
            cout << "Error: El ISBN no puede comenzar ni terminar con un guion.\n";
            return false;
        }

        if (isbn.find("--") != string::npos) {
            cout << "Error: El ISBN no puede contener guiones consecutivos.\n";
            return false;
        }
        string isbnSinGuiones = isbn;
        isbnSinGuiones.erase(remove(isbnSinGuiones.begin(), isbnSinGuiones.end(), '-'), isbnSinGuiones.end());

        // Verificar que todos los caracteres no sean iguales
        if (all_of(isbnSinGuiones.begin(), isbnSinGuiones.end(), [isbnSinGuiones](char c) { return c == isbnSinGuiones[0]; })) {
            cout << "Error: El ISBN no puede contener todos los caracteres iguales.\n";
            return false;
        }

        if (isbnSinGuiones.size() == 10) {
            return validarIsbn10(isbnSinGuiones);
        } else if (isbnSinGuiones.size() == 13) {
            return validarIsbn13(isbnSinGuiones);
        }
        cout << "Error: El ISBN debe tener 10 o 13 caracteres (sin contar los guiones).\n";
        return false;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return false;
    }
}

bool Validaciones::validarIsbn10(const string& isbn) {
    try {
        if (isbn.size() != 10) {
            return false;
        }

        // Verificar que los primeros 9 caracteres sean dígitos y el último sea un dígito o 'X'
        for (int i = 0; i < 9; i++) {
            if (!isdigit(isbn[i])) {
                return false;
            }
        }

        char digitoControl = isbn[9];
        if (!(isdigit(digitoControl) || digitoControl == 'X')) {
            return false;
        }

        // Validar el dígito de control
        return calcularDigitoControlIsbn10(isbn) == 0;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return false;
    }
}

bool Validaciones::validarIsbn13(const string& isbn) {
    try {
        if (isbn.size() != 13) {
            return false;
        }

        // Verificar que todos los caracteres sean dígitos
        for (int i = 0; i < 13; i++) {
            if (!isdigit(isbn[i])) {
                return false;
            }
        }

        // Validar el dígito de control
        return calcularDigitoControlIsbn13(isbn) == 0;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return false;
    }
}

int Validaciones::calcularDigitoControlIsbn10(const string& isbn) {
    try {
        int suma = 0;
        for (int i = 0; i < 9; i++) {
            suma += (isbn[i] - '0') * (10 - i);
        }
        char digitoControl = isbn[9];
        if (digitoControl == 'X') {
            suma += 10;
        } else {
            suma += (digitoControl - '0');
        }
        return suma % 11;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return -1;
    }
}

int Validaciones::calcularDigitoControlIsbn13(const string& isbn) {
    try {
        int suma = 0;
        for (int i = 0; i < 12; i++) {
            if (i % 2 == 0) {
                suma += (isbn[i] - '0');
            } else {
                suma += (isbn[i] - '0') * 3;
            }
        }
        int digitoControlCalculado = (10 - (suma % 10)) % 10;
        return digitoControlCalculado == (isbn[12] - '0') ? 0 : -1;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return -1;
    }
}

// Validación de ISNI
bool Validaciones::validarIsni(const string& isni) {
    try {
        // Remover espacios y guiones del ISNI
        std::string isniSinEspacios = isni;
        isniSinEspacios.erase(
            std::remove_if(isniSinEspacios.begin(), isniSinEspacios.end(),
                        [](char c) { return c == '-' || c == ' '; }),
            isniSinEspacios.end());

        // Verificar que el tamaño sea exactamente 16 caracteres
        if (isniSinEspacios.size() != 16) {
            std::cout << "Error: El ISNI debe contener exactamente 16 caracteres (sin incluir espacios ni guiones).\n";
            return false;
        }

        // Verificar que los primeros 15 caracteres sean numéricos
        if (!std::all_of(isniSinEspacios.begin(), isniSinEspacios.end() - 1, ::isdigit)) {
            std::cout << "Error: Los primeros 15 caracteres del ISNI deben ser numéricos.\n";
            return false;
        }

        // Verificar que el último carácter sea un dígito o una 'X'
        char lastChar = isniSinEspacios[15];
        if (!(std::isdigit(lastChar) || lastChar == 'X')) {
            std::cout << "Error: El último carácter del ISNI debe ser un dígito o 'X'.\n";
            return false;
        }

        // Verificar que todos los caracteres no sean iguales
        if (all_of(isniSinEspacios.begin(), isniSinEspacios.end(), [isniSinEspacios](char c) { return c == isniSinEspacios[0]; })) {
            std::cout << "Error: Ingrese un Isni Valido.\n";
            return false;
        }

        // Cálculo del dígito de control
        int sum = 0;
        int weight = 1; // Alternating weights: 1, 2
        for (int i = 0; i < 15; ++i) {
            int digit = isniSinEspacios[i] - '0';
            sum += digit * weight;
            weight = (weight == 1) ? 2 : 1;
        }

        return true;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return false;
    }
}


// Validación de texto no vacío
bool Validaciones::validarTextoNoVacio(const string& texto, const string& campo) {
    try {
        if (texto.empty() || texto.find_first_not_of(' ') == string::npos) {
            cout << "Error: El campo " << campo << " no puede estar vacío o contener solo espacios.\n";
            return false;
        }
        return true;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return false;
    }
}

// Validación de texto
bool Validaciones::validarTexto(const string& texto, const string& campo) {
    try {
        regex formatoTexto(R"([a-zA-ZñÑáéíóúÁÉÍÓÚ\s]+)");
        if (texto.empty() || texto.find_first_not_of(' ') == string::npos) {
            cout << "Error: El campo " << campo << " no puede estar vacío o contener solo espacios.\n";
            return false;
        } else if (!regex_match(texto, formatoTexto)) {
            cout << "Error: El campo " << campo << " solo debe contener letras, espacios y caracteres válidos en español.\n";
            return false;
        }
        return true;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return false;
    }
}

// Función auxiliar: días en un mes
int Validaciones::diasEnMes(int mes, int anio) {
    try {
        switch (mes) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
            case 4: case 6: case 9: case 11: return 30;
            case 2: return (esBisiesto(anio)) ? 29 : 28;
            default: return 0;
        }
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return 0;
    }
}

// Función auxiliar: año bisiesto
bool Validaciones::esBisiesto(int anio) {
    try {
        return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return false;
    }
}

int Validaciones::ingresarAnio(const string& mensaje) {
    int anio;
    string input;
    while (true) {
        cout << mensaje;
        input.clear();
        char ch;
        while ((ch = _getch()) != '\r') { // Leer hasta que se presione Enter
            if (isdigit(ch) && input.size() < 4) {
                cout << ch;
                input += ch;
            } else if (ch == '\b' && !input.empty()) { // Permitir backspace
                cout << "\b \b";
                input.pop_back();
            }
        }
        cout << endl;

        // Validar si la entrada está vacía
        if (input.empty()) {
            cout << "Error: Debe ingresar un dato (no puede estar vacío)." << endl;
            continue;
        }

        // Validar que el año sea numérico y tenga 4 dígitos
        try {
            anio = stoi(input);  // Convertimos la entrada a entero
            if (anio < 1900 || anio > 2025) {
                throw invalid_argument("Año fuera de rango.");
            }
            break;  // Salimos del bucle si el año es válido
        } catch (const invalid_argument& e) {
            cout << "Error: Ingrese un año válido de 4 dígitos desde 1900 hasta el año actual." << endl;
        } catch (const out_of_range& e) {
            cout << "Error: El año ingresado está fuera de rango." << endl;
        }
    }
    return anio;
}

string Validaciones::leerSoloNumeros() {
    try {
        string input;
        char ch;
        while ((ch = _getch()) != '\r') { // Leer hasta que se presione Enter
            if (isdigit(ch)) {
                cout << ch;
                input += ch;
            } else if (ch == '\b' && !input.empty()) { // Permitir backspace
                cout << "\b \b";
                input.pop_back();
            }
        }
        cout << endl;

        return input;
    } catch (const exception& e) {
        cerr << "Error al leer solo números: " << e.what() << endl;
        return "";
    }
}

string Validaciones::leerIsbnIsni() {
    try {
        string input;
        char ch;
        while ((ch = _getch()) != '\r') { // Leer hasta que se presione Enter
            if (isdigit(ch) || ch == '-' || ch == 'X' || ch == ' ') {
                cout << ch;
                input += ch;
            } else if (ch == '\b' && !input.empty()) { // Permitir backspace
                cout << "\b \b";
                input.pop_back();
            }
        }
        cout << endl;
        return input;
    } catch (const exception& e) {
        cerr << "Error al leer ISBN/ISNI: " << e.what() << endl;
        return "";
    }
}

bool Validaciones::contieneLetra(const std::string& titulo) {
    for (char c : titulo) {
        if (std::isalpha(c)) {
            return true;
        }
    }
    return false;
}

std::string Validaciones::leerSoloCaracteres() {
    try {
        std::string input;
        char ch;
        while ((ch = _getch()) != '\r') { // Leer hasta que se presione Enter
            if (isalpha(ch) && input.empty()) { // Permitir solo un carácter alfabético
                std::cout << ch;
                input += ch;
            } else if (ch == '\b' && !input.empty()) { // Permitir backspace
                std::cout << "\b \b";
                input.pop_back();
            }
        }
        std::cout << std::endl;
        return input;
    } catch (const std::exception& e) {
        std::cerr << "Error al leer solo caracteres: " << e.what() << std::endl;
        return "";
    }
}