#pragma once
#include "ListaLibros.h"
#include <string>
#include <iostream>
#include <fstream>
#include <hpdf.h>  // Asegúrate de tener instalada la librería Haru PDF

class GenerarPDFLibros {
public:
    GenerarPDFLibros(ListaLibros& listaLibros);
    void generarPDF(const std::string& nombreArchivo);

private:
    ListaLibros& listaLibros;
};
