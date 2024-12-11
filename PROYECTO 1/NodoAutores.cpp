#include "NodoAutores.h"

NodoAutores::NodoAutores(string _cedula, string _nombre, string _apellido, string _fechaPublicacion)
    : cedula(_cedula), nombre(_nombre), apellido(_apellido), fechaPublicacion(_fechaPublicacion), siguiente(nullptr), anterior(nullptr) {}

string NodoAutores::getCedula() { return cedula; }
string NodoAutores::getNombre() { return nombre; }
string NodoAutores::getApellido() { return apellido; }
string NodoAutores::getFechaPublicacion() { return fechaPublicacion; }

NodoAutores* NodoAutores::getSiguiente() { return siguiente; }
NodoAutores* NodoAutores::getAnterior() { return anterior; }

void NodoAutores::setSiguiente(NodoAutores* _siguiente) { siguiente = _siguiente; }
void NodoAutores::setAnterior(NodoAutores* _anterior) { anterior = _anterior; }
