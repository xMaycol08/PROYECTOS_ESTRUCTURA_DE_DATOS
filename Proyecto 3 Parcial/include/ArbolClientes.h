#ifndef ARBOLCLIENTES_H
#define ARBOLCLIENTES_H

#include <iostream>
#include "Cliente.h"
#include <string>
#include <map>

class NodoAVL {
public:
    Cliente cliente;
    NodoAVL* izquierda;
    NodoAVL* derecha;
    int altura;

    NodoAVL(const Cliente& cliente) : cliente(cliente), izquierda(nullptr), derecha(nullptr), altura(1) {}
};

class ArbolClientes {
public:
    ArbolClientes();
    ~ArbolClientes(); // Destructor
    void insertar(const Cliente& cliente);
    Cliente buscarPorCedula(const std::string& cedula) const;
    void eliminarCliente(const std::string& cedula);
    void buscarPorCedulaYMostrar(const std::string& cedula) const;
    void limpiarClientes(); // Agregar declaración

private:
    NodoAVL* raiz;
    std::map<std::string, Cliente> clientes;

    int obtenerAltura(NodoAVL* nodo);
    int obtenerBalance(NodoAVL* nodo);
    NodoAVL* rotacionDerecha(NodoAVL* y);
    NodoAVL* rotacionIzquierda(NodoAVL* x);
    NodoAVL* insertar(NodoAVL* nodo, const Cliente& cliente);
    NodoAVL* eliminarNodo(NodoAVL* nodo, const std::string& cedula);
    NodoAVL* obtenerMinimo(NodoAVL* nodo);
    void eliminarReservaArchivo(const std::string& cedula); // Add this method declaration
    void liberarMemoria(NodoAVL* nodo); // New method for memory management
};

#endif
