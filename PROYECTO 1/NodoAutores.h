#pragma once
#include <string>
using namespace std;

class NodoAutores {
private:
    string cedula;
    string nombre;
    string apellido;
    string fechaPublicacion;
    NodoAutores* siguiente;
    NodoAutores* anterior;

public:
    NodoAutores(string, string, string, string);
    string getCedula();
    string getNombre();
    string getApellido();
    string getFechaPublicacion();
    NodoAutores* getSiguiente();
    NodoAutores* getAnterior();
    void setSiguiente(NodoAutores*);
    void setAnterior(NodoAutores*);
};
