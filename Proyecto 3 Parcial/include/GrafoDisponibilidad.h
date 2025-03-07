#ifndef GRAFO_DISPONIBILIDAD_H
#define GRAFO_DISPONIBILIDAD_H

#include <vector>
#include <map>
#include <string>
#include "Mesa.h"
#include "Reserva.h"

class NodoMesa {
public:
    int id;
    std::vector<NodoMesa*> adyacentes;
    Mesa* mesa;
    NodoMesa(int id) : id(id), mesa(new Mesa(id)) {}
    ~NodoMesa() { delete mesa; }
};

class GrafoDisponibilidad {
private:
    std::map<int, NodoMesa*> nodos;
    std::map<std::string, std::vector<int>> reservasPorFecha;
    std::vector<Mesa*> mesasDisponibles;  // Lista de todas las mesas

public:
    GrafoDisponibilidad();
    ~GrafoDisponibilidad();
    void agregarMesa(int id);
    void agregarArista(int id1, int id2);
    void cargarMesasDesdeArchivo(std::string archivo);
    std::vector<int> obtenerMesasDisponibles(const std::string& fechaHora) const;
    void agregarReserva(int idMesa, const std::string& fechaHora);
    void mostrarDisponibilidad(const std::string& fechaHora, const std::vector<Reserva*>& reservas) const;
    void eliminarReserva(int idMesa, const std::string& fechaHora);
    void liberarMemoria();
    void limpiarReservas(); // Agregar declaración
};

#endif // GRAFO_DISPONIBILIDAD_H
