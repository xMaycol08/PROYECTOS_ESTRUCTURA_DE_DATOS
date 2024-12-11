#pragma once
#include "NodoLibros.h"
#include "ListaAutores.h"
#include <string>
#include <regex>
#include <fstream>
#include "json.hpp" // Aseg�rate de que esta ruta sea correcta

using json = nlohmann::json; // Simplifica el uso de JSON

class ListaLibros {
private:
    NodoLibros* cabeza;

public:
    // Constructor y Destructor
    ListaLibros();
    ~ListaLibros();

    // Operaciones b�sicas
    bool insertar(string titulo, string autor, string isbn, string genero, string anioLanzamiento, float precio, float calificacion);
    NodoLibros* buscar(string isbn);
    bool eliminar(string isbn);
    void filtrarPorAnio();
    void mostrar();

    // Funciones para manejar JSON
    void cargarDesdeArchivoJSON(); // Cargar datos desde un archivo JSON
    void guardarEnArchivoJSON();   // Guardar datos en un archivo JSON

    // Funciones para Backup
    void crearBackup(); // Crear un backup con fecha y hora
    void restaurarBackup(const string& nombreArchivo); // Restaurar desde un backup

    // Relaci�n con autores
    string seleccionarAutor(ListaAutores& listaAutores);

    // M�todo getter para obtener el nodo cabeza
    NodoLibros* getCabeza() const { return cabeza; }
};
