#include "../include/ArbolClientes.h"
#include <iostream>
#include <fstream>

// Constructor
ArbolClientes::ArbolClientes() : raiz(nullptr) {}

// Destructor
ArbolClientes::~ArbolClientes() {
    try {
        liberarMemoria(raiz);
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al liberar la memoria en ArbolClientes: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al liberar la memoria en ArbolClientes." << std::endl;
    }
}

// Liberar memoria de forma recursiva
void ArbolClientes::liberarMemoria(NodoAVL* nodo) {
    try {
        if (nodo) {
            liberarMemoria(nodo->izquierda);
            liberarMemoria(nodo->derecha);
            delete nodo;
        }
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al liberar la memoria de los nodos: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al liberar la memoria de los nodos." << std::endl;
    }
}

int ArbolClientes::obtenerAltura(NodoAVL* nodo) {
    return nodo ? nodo->altura : 0;
}

int ArbolClientes::obtenerBalance(NodoAVL* nodo) {
    return nodo ? obtenerAltura(nodo->izquierda) - obtenerAltura(nodo->derecha) : 0;
}

NodoAVL* ArbolClientes::rotacionDerecha(NodoAVL* y) {
    try {
        NodoAVL* x = y->izquierda;
        NodoAVL* temp = x->derecha;
        x->derecha = y;
        y->izquierda = temp;

        y->altura = std::max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;
        x->altura = std::max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;

        return x;
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al realizar la rotación a la derecha: " << e.what() << std::endl;
        return nullptr;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al realizar la rotación a la derecha." << std::endl;
        return nullptr;
    }
}

NodoAVL* ArbolClientes::rotacionIzquierda(NodoAVL* x) {
    try {
        NodoAVL* y = x->derecha;
        NodoAVL* temp = y->izquierda;
        y->izquierda = x;
        x->derecha = temp;

        x->altura = std::max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;
        y->altura = std::max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;

        return y;
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al realizar la rotación a la izquierda: " << e.what() << std::endl;
        return nullptr;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al realizar la rotación a la izquierda." << std::endl;
        return nullptr;
    }
}

NodoAVL* ArbolClientes::insertar(NodoAVL* nodo, const Cliente& cliente) {
    try {
        if (!nodo) {
            return new NodoAVL(cliente);  // Si el nodo es nulo, creamos un nuevo nodo con el cliente
        }
        // Cambiar comparación de 'nombre' a 'cedula'
        if (cliente.getCedula() < nodo->cliente.getCedula()) {
            nodo->izquierda = insertar(nodo->izquierda, cliente);  // Insertar en el subárbol izquierdo
        } else if (cliente.getCedula() > nodo->cliente.getCedula()) {
            nodo->derecha = insertar(nodo->derecha, cliente);  // Insertar en el subárbol derecho
        } else {
            return nodo;  // Si la cédula ya existe, no insertamos el cliente
        }

        // Recalcular la altura del nodo
        nodo->altura = 1 + std::max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha));

        // Calcular el balance del nodo
        int balance = obtenerBalance(nodo);

        // Realizar las rotaciones necesarias para balancear el árbol
        if (balance > 1 && cliente.getCedula() < nodo->izquierda->cliente.getCedula()) {
            return rotacionDerecha(nodo);
        }
        if (balance < -1 && cliente.getCedula() > nodo->derecha->cliente.getCedula()) {
            return rotacionIzquierda(nodo);
        }
        if (balance > 1 && cliente.getCedula() > nodo->izquierda->cliente.getCedula()) {
            nodo->izquierda = rotacionIzquierda(nodo->izquierda);
            return rotacionDerecha(nodo);
        }
        if (balance < -1 && cliente.getCedula() < nodo->derecha->cliente.getCedula()) {
            nodo->derecha = rotacionDerecha(nodo->derecha);
            return rotacionIzquierda(nodo);
        }

        return nodo;
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al insertar un cliente: " << e.what() << std::endl;
        return nullptr;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al insertar un cliente." << std::endl;
        return nullptr;
    }
}

void ArbolClientes::insertar(const Cliente& cliente) {
    try {
        raiz = insertar(raiz, cliente);
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al insertar un cliente en el árbol: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al insertar un cliente en el árbol." << std::endl;
    }
}


Cliente ArbolClientes::buscarPorCedula(const std::string& cedula) const {
    try {
        NodoAVL* actual = raiz;
        while (actual != nullptr) {
            if (actual->cliente.getCedula() == cedula) {
                return actual->cliente;
            } else if (cedula < actual->cliente.getCedula()) {
                actual = actual->izquierda;
            } else {
                actual = actual->derecha;
            }
        }
        return Cliente();
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al buscar un cliente por cédula: " << e.what() << std::endl;
        return Cliente();
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al buscar un cliente por cédula." << std::endl;
        return Cliente();
    }
}

void ArbolClientes::eliminarCliente(const std::string& cedula) {
    try {
        raiz = eliminarNodo(raiz, cedula);
        eliminarReservaArchivo(cedula);
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al eliminar un cliente: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al eliminar un cliente." << std::endl;
    }
}

NodoAVL* ArbolClientes::eliminarNodo(NodoAVL* nodo, const std::string& cedula) {
    try {
        if (!nodo) return nodo;

        if (cedula < nodo->cliente.getCedula()) {
            nodo->izquierda = eliminarNodo(nodo->izquierda, cedula);
        } else if (cedula > nodo->cliente.getCedula()) {
            nodo->derecha = eliminarNodo(nodo->derecha, cedula);
        } else {
            if (!nodo->izquierda || !nodo->derecha) {
                NodoAVL* temp = nodo->izquierda ? nodo->izquierda : nodo->derecha;
                if (!temp) {
                    temp = nodo;
                    nodo = nullptr;
                } else {
                    *nodo = *temp;
                }
                delete temp;
            } else {
                NodoAVL* temp = obtenerMinimo(nodo->derecha);
                nodo->cliente = temp->cliente;
                nodo->derecha = eliminarNodo(nodo->derecha, temp->cliente.getCedula());
            }
        }

        if (!nodo) return nodo;

        nodo->altura = 1 + std::max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha));
        int balance = obtenerBalance(nodo);

        if (balance > 1 && obtenerBalance(nodo->izquierda) >= 0) return rotacionDerecha(nodo);
        if (balance > 1 && obtenerBalance(nodo->izquierda) < 0) {
            nodo->izquierda = rotacionIzquierda(nodo->izquierda);
            return rotacionDerecha(nodo);
        }
        if (balance < -1 && obtenerBalance(nodo->derecha) <= 0) return rotacionIzquierda(nodo);
        if (balance < -1 && obtenerBalance(nodo->derecha) > 0) {
            nodo->derecha = rotacionDerecha(nodo->derecha);
            return rotacionIzquierda(nodo);
        }

        return nodo;
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al eliminar un nodo: " << e.what() << std::endl;
        return nullptr;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al eliminar un nodo." << std::endl;
        return nullptr;
    }
}

NodoAVL* ArbolClientes::obtenerMinimo(NodoAVL* nodo) {
    try {
        NodoAVL* actual = nodo;
        while (actual->izquierda) actual = actual->izquierda;
        return actual;
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al obtener el nodo mínimo: " << e.what() << std::endl;
        return nullptr;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al obtener el nodo mínimo." << std::endl;
        return nullptr;
    }
}

void ArbolClientes::eliminarReservaArchivo(const std::string& cedula) {
    try {
        std::ifstream archivoEntrada("reservas.txt");
        std::ofstream archivoSalida("reservas_temp.txt");
        std::string linea;

        while (std::getline(archivoEntrada, linea)) {
            if (linea.find(cedula) == std::string::npos) {
                archivoSalida << linea << std::endl;
            }
        }

        archivoEntrada.close();
        archivoSalida.close();

        std::remove("reservas.txt");
        std::rename("reservas_temp.txt", "reservas.txt");
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al eliminar la reserva del archivo: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al eliminar la reserva del archivo." << std::endl;
    }
}

void ArbolClientes::buscarPorCedulaYMostrar(const std::string& cedula) const {
    try {
        NodoAVL* actual = raiz;
        bool found = false;
        while (actual != nullptr) {
            if (actual->cliente.getCedula() == cedula) {
                actual->cliente.mostrarCliente();
                found = true;
                break;
            } else if (cedula < actual->cliente.getCedula()) {
                actual = actual->izquierda;
            } else {
                actual = actual->derecha;
            }
        }
        if (!found) {
            std::cout << "No se encontraron clientes con la cédula: " << cedula << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Se produjo una excepción al buscar y mostrar un cliente por cédula: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Se produjo una excepción desconocida al buscar y mostrar un cliente por cédula." << std::endl;
    }
}

void ArbolClientes::limpiarClientes() {
    liberarMemoria(raiz);
    raiz = nullptr;
}
