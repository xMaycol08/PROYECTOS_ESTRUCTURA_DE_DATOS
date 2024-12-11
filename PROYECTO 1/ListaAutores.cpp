#include "ListaAutores.h"
#include "Validaciones.h"
#include <iostream>
#include "json.hpp"
#include <chrono>
#include "BackupManager.h"

using json = nlohmann::json;

ListaAutores::ListaAutores() : cabeza(nullptr) {}

ListaAutores::~ListaAutores() {
    if (cabeza) {
        NodoAutores* actual = cabeza;
        do {
            NodoAutores* siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        } while (actual != cabeza);
    }
}

bool ListaAutores::insertar(string cedula, string nombre, string apellido, string fechaPublicacion) {
    if (buscar(cedula)) {
        cout << "Error: Autor con cedula " << cedula << " ya existe.\n";
        return false;
    }

    NodoAutores* nuevo = new NodoAutores(cedula, nombre, apellido, fechaPublicacion);

    if (!cabeza) {
        cabeza = nuevo;
        cabeza->setSiguiente(cabeza);
        cabeza->setAnterior(cabeza);
    } else {
        NodoAutores* ultimo = cabeza->getAnterior();
        ultimo->setSiguiente(nuevo);
        nuevo->setAnterior(ultimo);
        nuevo->setSiguiente(cabeza);
        cabeza->setAnterior(nuevo);
    }
    guardarEnArchivoJSON(); // Usar JSON para guardar cambios
    cout << "Guardado Exitosamente.\n";
    return true;
}

NodoAutores* ListaAutores::buscar(string cedula) {
    if (!cabeza) return nullptr;

    NodoAutores* actual = cabeza;
    do {
        if (actual->getCedula() == cedula) {
            return actual;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    return nullptr;
}

bool ListaAutores::eliminar(string cedula) {
    NodoAutores* encontrado = buscar(cedula);
    if (!encontrado) {
        cout << "Error: Autor no encontrado.\n";
        return false;
    }

    if (encontrado->getSiguiente() == encontrado) {
        cabeza = nullptr;
    } else {
        NodoAutores* anterior = encontrado->getAnterior();
        NodoAutores* siguiente = encontrado->getSiguiente();
        anterior->setSiguiente(siguiente);
        siguiente->setAnterior(anterior);
        if (cabeza == encontrado) {
            cabeza = siguiente;
        }
    }
    delete encontrado;
    guardarEnArchivoJSON(); // Usar JSON para guardar cambios
    return true;
}

void ListaAutores::mostrar() {
    if (!cabeza) {
        cout << "Lista de autores vacia.\n";
        return;
    }

    NodoAutores* actual = cabeza;
    do {
        cout << "Cedula: " << actual->getCedula()
             << ", Nombre: " << actual->getNombre()
             << ", Apellido: " << actual->getApellido()
             << ", Fecha de Publicacion: " << actual->getFechaPublicacion() << "\n";
        actual = actual->getSiguiente();
    } while (actual != cabeza);
}

void ListaAutores::guardarEnArchivoJSON() {
    if (!cabeza) {
        cout << "La lista de autores esta vacia.\n";
        return;
    }

    json jAutores = json::array();

    NodoAutores* actual = cabeza;
    do {
        jAutores.push_back({
            {"cedula", actual->getCedula()},
            {"nombre", actual->getNombre()},
            {"apellido", actual->getApellido()},
            {"fechaPublicacion", actual->getFechaPublicacion()}
        });
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    std::ofstream archivo("autores.json");
    if (archivo.is_open()) {
        archivo << jAutores.dump(4);
        archivo.close();

    } else {
        cout << "Error: No se pudo abrir el archivo para guardar datos.\n";
    }
}

void ListaAutores::cargarDesdeArchivoJSON() {
    std::ifstream archivo("autores.json");
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo para cargar datos.\n";
        return;
    }

    json jAutores;
    archivo >> jAutores;
    archivo.close();

    for (const auto& autor : jAutores) {
        string cedula = autor["cedula"];
        string nombre = autor["nombre"];
        string apellido = autor["apellido"];
        string fechaPublicacion = autor["fechaPublicacion"];

        cout << "Cargando autor: " << cedula << ", " << nombre << ", " << apellido << "\n";
        insertar(cedula, nombre, apellido, fechaPublicacion);
    }

}

void ListaAutores::crearBackup() {
    // Verificar si hay datos para respaldar
    if (!cabeza) {
        cout << "No hay datos para hacer el backup.\n";
        return;
    }

    // Generar nombre con fecha y hora
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    tm localTime;
    localtime_s(&localTime, &now); // Convertir a hora local

    char buffer[64];
    strftime(buffer, sizeof(buffer), "BackupAutores/autores-%Y-%m-%d-%H-%M-%S.json", &localTime);

    // Guardar backup
    ofstream archivo(buffer);
    if (!archivo.is_open()) {
        cout << "Error: No se pudo crear el backup en la carpeta BackupAutores.\n";
        return;
    }

    json jAutores = json::array();
    NodoAutores* actual = cabeza;
    do {
        jAutores.push_back({
            {"cedula", actual->getCedula()},
            {"nombre", actual->getNombre()},
            {"apellido", actual->getApellido()},
            {"fechaPublicacion", actual->getFechaPublicacion()}
        });
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    archivo << jAutores.dump(4);
    archivo.close();
    cout << "Backup creado exitosamente: " << buffer << "\n";
}


void ListaAutores::restaurarBackup(const std::string& nombreArchivo) {
    std::ifstream archivo("BackupAutores/" + nombreArchivo); // Leer desde la carpeta BackupAutores
    if (!archivo.is_open()) {
        std::cout << "Error: No se pudo abrir el archivo de backup " << nombreArchivo << ".\n";
        return;
    }

    json jAutores;
    archivo >> jAutores; // Leer el contenido del archivo JSON
    archivo.close();

    // Comprobar si el backup está vacío
    if (jAutores.empty()) {
        std::cout << "No existe nada en el backup.\n";
        return;
    }

    // Liberar memoria de la lista actual (si existe)
    if (cabeza) {
        NodoAutores* actual = cabeza;
        do {
            NodoAutores* siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        } while (actual != cabeza);
        cabeza = nullptr; // Reiniciar la lista
    }

    // Reconstruir la lista desde el backup
    for (const auto& autor : jAutores) {
        std::string cedula = autor["cedula"];
        std::string nombre = autor["nombre"];
        std::string apellido = autor["apellido"];
        std::string fechaPublicacion = autor["fechaPublicacion"];

        NodoAutores* nuevo = new NodoAutores(cedula, nombre, apellido, fechaPublicacion);
        if (!cabeza) {
            cabeza = nuevo;
            cabeza->setSiguiente(cabeza);
            cabeza->setAnterior(cabeza);
        } else {
            NodoAutores* ultimo = cabeza->getAnterior();
            ultimo->setSiguiente(nuevo);
            nuevo->setAnterior(ultimo);
            nuevo->setSiguiente(cabeza);
            cabeza->setAnterior(nuevo);
        }
    }

    // Guardar todos los datos una sola vez
    guardarEnArchivoJSON();

    std::cout << "Backup restaurado correctamente desde " << nombreArchivo << ".\n";
}
