#pragma once
#include <string>
using namespace std;

bool validarCedula(const string& cedula);
bool validarTexto(const string& texto);
bool esBisiesto(int anio);
bool validarFecha(const string& fecha);
bool validarEntero(const string& numero);
bool validarFlotante(const string& numero);
bool validarOpcionMenu(int opcion, int min, int max);
bool validarPrecio(double precio);
bool validarCalificacion(double calificacion);
bool validarISBN(const std::string& isbn);

// Funciones para ingresar n�meros de forma segura
bool ingresarNumero(int& numero);         // Para enteros (por ejemplo, a�o)
bool ingresarNumero(double& numero);      // Para decimales (por ejemplo, precio o calificaci�n)
bool ingresarOpcionMenu(int& opcion);     // Funci�n para validar la opci�n seleccionada en el men�
