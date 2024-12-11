#include "NodoLibros.h"
#include <iostream>

using namespace std;

NodoLibros::NodoLibros(string _titulo, string _autor, string _isbn, string _genero, string _anioLanzamiento, float _precio, float _calificacion)
    : titulo(_titulo), autor(_autor), isbn(_isbn), genero(_genero), anioLanzamiento(_anioLanzamiento), precio(_precio), calificacion(_calificacion),
      siguiente(nullptr), anterior(nullptr) {
    // Mensaje de depuraci�n
    //cout << "Nodo creado: " << titulo << ", " << autor << ", " << isbn << ", "
       //  << genero << ", " << anioLanzamiento << ", " << precio << ", " << calificacion << "\n";
}



string NodoLibros::getTitulo() { return titulo; }
string NodoLibros::getAutor() { return autor; }
string NodoLibros::getIsbn() { return isbn; }
string NodoLibros::getGenero() { return genero; }
string NodoLibros::getAnioLanzamiento() { return anioLanzamiento; }
float NodoLibros::getPrecio() { return precio; }
float NodoLibros::getCalificacion() { return calificacion; }

NodoLibros* NodoLibros::getSiguiente() { return siguiente; }
NodoLibros* NodoLibros::getAnterior() { return anterior; }

void NodoLibros::setSiguiente(NodoLibros* _siguiente) { siguiente = _siguiente; }
void NodoLibros::setAnterior(NodoLibros* _anterior) { anterior = _anterior; }
