#include "Validaciones.h"
#include <regex>
#include <iostream>
#include <limits>
#include <ctime>
#include <string>

// Validaciones existentes
bool validarCedula(const string& cedula) {
    if (cedula.length() != 10) return false;
    if (!regex_match(cedula, regex("\\d{10}"))) return false;

    int suma = 0;
    for (int i = 0; i < 9; i++) {
        int digito = cedula[i] - '0';
        if (i % 2 == 0) {
            digito *= 2;
            if (digito > 9) digito -= 9;
        }
        suma += digito;
    }

    int ultimoDigito = cedula[9] - '0';
    int decenaSuperior = (suma + 9) / 10 * 10;
    return ultimoDigito == (decenaSuperior - suma);
}

bool validarTexto(const string& texto) {
    return regex_match(texto, regex("^[a-zA-Z������������ ]+$"));
}

bool esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

bool validarFecha(const string& fecha) {
    // Expresión regular para el formato MM/DD/YYYY
    regex formato("^(0[1-9]|1[0-2])/(0[1-9]|[12][0-9]|3[01])/[0-9]{4}$");
    if (!regex_match(fecha, formato)) {
        cerr << "Error: Formato de fecha invalido. Use MM/DD/YYYY." << endl;
        return false;
    }

    // Extraer mes, día y año de la cadena
    int mes = stoi(fecha.substr(0, 2));
    int dia = stoi(fecha.substr(3, 2));
    int anio = stoi(fecha.substr(6, 4));

    // Obtener el año actual
    time_t t = time(nullptr);
    tm* fechaActual = localtime(&t);
    int anioActual = fechaActual->tm_year + 1900;

    // Validar rango del año
    if (anio < 1700 || anio > anioActual) {
        cerr << "Error: La fecha debe estar entre 1700 y " << anioActual << "." << endl;
        return false;
    }

    // Validar días según el mes (sin considerar años bisiestos)
    int diasEnMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Si es un año bisiesto, ajustar el día máximo de febrero
    if (mes == 2 && esBisiesto(anio)) {
        diasEnMes[1] = 29; // febrero tiene 29 días en un año bisiesto
    }

    if (dia < 1 || dia > diasEnMes[mes - 1]) {
        cerr << "Error: El dia no es valido para el mes especificado." << endl;
        return false;
    }

    return true;
}

bool validarEntero(const string& numero) {
    return regex_match(numero, regex("^-?\\d+$"));
}

bool validarFlotante(const string& numero) {
    return regex_match(numero, regex("^-?\\d*\\.?\\d+$"));
}

bool validarOpcionMenu(int opcion, int min, int max) {
    return opcion >= min && opcion <= max;
}

bool validarPrecio(double precio) {
    return precio >= 0.0;
}

bool validarCalificacion(double calificacion) {
    return calificacion >= 0.0 && calificacion <= 10.0;
}

bool validarISBN(const std::string& isbn) {
     return std::regex_match(isbn, std::regex("[0-9]+(-[0-9]+)*"));
}

// Funci�n para ingresar n�meros enteros (por ejemplo, a�o)
bool ingresarNumero(int& numero) {
    while (true) {
        cin >> numero;
        if (cin.fail()) { // Si la entrada no es un n�mero
            cin.clear(); // Limpiar el error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar caracteres no v�lidos
            cout << "Error: Ingresa un numero valido.\n";
        } else {
            return true; // Entrada v�lida
        }
    }
}

// Funci�n para ingresar n�meros decimales (por ejemplo, precio o calificaci�n)
bool ingresarNumero(double& numero) {
    while (true) {
        cin >> numero;
        if (cin.fail()) { // Si la entrada no es un n�mero
            cin.clear(); // Limpiar el error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar caracteres no v�lidos
            cout << "Error: Ingresa un numero valido.\n";
        } else {
            return true; // Entrada v�lida
        }
    }
}

// Funci�n para ingresar y validar la opci�n seleccionada en el men�
bool ingresarOpcionMenu(int& opcion) {
    while (true) {
        cin >> opcion;
        if (cin.fail()) { // Si la entrada no es un n�mero
            cin.clear(); // Limpiar el error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar caracteres no v�lidos
            cout << "Error: Ingresa una opcion valida.\n";
             cout << "Vuelve a intentarlo por favor:";
        } else {
            return true; // Entrada v�lida
        }
    }
}
