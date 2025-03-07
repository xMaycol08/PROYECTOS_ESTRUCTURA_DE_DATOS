#include "../include/ComplexityAnalyzer.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

std::vector<std::string> ComplexityAnalyzer::obtenerClases() {
    // Aquí se deben listar las clases disponibles para el análisis
    return {"ArbolClientes", "BackupManager", "Calendario", "Cliente", "ComplexityAnalyzer", "DataManager", "GrafoDisponibilidad", "Menu", "Mesa", "Reserva", "ReservaManager", "Utils", "Validaciones"};
}

std::vector<std::string> ComplexityAnalyzer::obtenerFunciones(const std::string& className) {
    // Aquí se deben listar las funciones disponibles para cada clase
    if (className == "ArbolClientes") {
        return {
            "ArbolClientes", "~ArbolClientes", "liberarMemoria", "obtenerAltura", "obtenerBalance",
            "rotacionDerecha", "rotacionIzquierda", "insertar(Cliente)",
            "buscarPorCedula", "eliminarCliente", "eliminarNodo",
            "obtenerMinimo", "eliminarReservaArchivo", "buscarPorCedulaYMostrar"
        };
    } else if (className == "BackupManager") {
        return {"hacerBackup", "recuperarBackup", "obtenerFechaHoraActual"};
    } else if (className == "Calendario") {
        return {"liberarMemoria", "agregarReserva", "eliminarReserva", "getReservas"};
    } else if (className == "Cliente") {
        return {"Cliente", "getNombre", "getTelefono", "getCedula", "getEmail", "mostrarCliente"};
    } else if (className == "ComplexityAnalyzer") {
        return {"obtenerClases", "obtenerFunciones", "analizarComplejidad"};
    } else if (className == "DataManager") {
        return {"guardarReservas", "cargarReservas", "cargarClientes"};
    } else if (className == "GrafoDisponibilidad") {
        return {"GrafoDisponibilidad", "~GrafoDisponibilidad", "liberarMemoria", "cargarMesasDesdeArchivo", "obtenerMesasDisponibles", "mostrarDisponibilidad", "agregarReserva", "eliminarReserva"};
    } else if (className == "Menu") {
        return {"dataManager.cargarClientes", "arbolClientes.buscarPorCedula", "Validaciones::validarCedulaReal", "std::find", "grafo.obtenerMesasDisponibles", "arbolClientes.insertar", "calendario.agregarReserva", "grafo.agregarReserva", "dataManager.guardarReservas", "reservas.push_back"};
    } else if (className == "Mesa") {
        return {"Mesa", "Mesa(int, int)", "getId", "getCapacidad", "estaDisponible", "ocupar", "liberar", "Mesa(int numero)", "getNumero", "getNombre", "getTelefono"};
    } else if (className == "Reserva") {
        return {"Reserva", "Reserva(const Cliente&, int, const std::tm&)", "Reserva(const std::string&, int, const std::tm&)", "Reserva(const std::string&, int, const std::string&)", "Reserva(const std::string&, const std::string&, const std::string&, const std::string&, int, const std::string&)", "Reserva(const std::string&, const std::string&, const std::string&, const std::string&, int, const std::tm&)", "getCliente", "getIdMesa", "getFecha", "convertirTmAString", "getFechaHora", "convertirStringATm"};
    } else if (className == "ReservaManager") {
        return {"~ReservaManager", "liberarMemoria", "cargarReservas", "guardarReservas", "mostrarReservas", "mostrarReservasPorCedula", "cancelarReservaPorCedula", "getReservas"};
    } else if (className == "Utils") {
        return {"mostrarMenu", "limpiarPantalla"};
    } else if (className == "Validaciones") {
        return {"validarCedulaReal", "validarNombre", "capitalizarNombre", "validarNumeroTelefono", "validarMesa", "validarCorreo", "validarFechaHora"};
    }
    return {};
}

void ComplexityAnalyzer::analizarComplejidad(const std::string& className, const std::string& functionName) {
    std::string command = "python analyze_complexity.py " + className + " \"" + functionName + "\"";
    std::system(command.c_str());
}