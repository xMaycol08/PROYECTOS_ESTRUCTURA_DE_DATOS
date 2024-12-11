#pragma once
#include "ListaAutores.h"
#include <string>

class GenerarPDFAutores {
private:
    ListaAutores& listaAutores;

public:
    GenerarPDFAutores(ListaAutores& listaAutores);
    void generarPDF(const std::string& nombreArchivo);
};
