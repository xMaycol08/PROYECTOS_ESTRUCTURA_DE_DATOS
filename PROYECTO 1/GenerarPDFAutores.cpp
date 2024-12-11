#include "GenerarPDFAutores.h"
#include <iostream>
#include <hpdf.h>
#include <cstdlib>  // Para usar system() y abrir el PDF autom�ticamente

GenerarPDFAutores::GenerarPDFAutores(ListaAutores& listaAutores) : listaAutores(listaAutores) {}

void GenerarPDFAutores::generarPDF(const std::string& nombreArchivo) {
    // Crear un documento PDF
    HPDF_Doc pdf = HPDF_New(nullptr, nullptr);
    if (!pdf) {
        std::cerr << "Error al crear el documento PDF." << std::endl;
        return;
    }

    // Crear una p�gina en blanco
    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

    // Establecer las fuentes
    HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", nullptr);
    HPDF_Page_SetFontAndSize(page, font, 12);

    // Definir la posici�n inicial para el texto
    float yPosition = 750.0f;

    // T�tulo del documento
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, font, 16);
    HPDF_Page_TextOut(page, 50.0f, yPosition, "Lista de Autores");
    HPDF_Page_EndText(page);
    yPosition -= 30.0f;

    // Separador
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, font, 10);
    HPDF_Page_TextOut(page, 50.0f, yPosition, "==========================================");
    HPDF_Page_EndText(page);
    yPosition -= 20.0f;

    // Recorremos la lista de autores y generamos su informaci�n en el PDF
    NodoAutores* actual = listaAutores.getCabeza();
    if (actual == nullptr) {
        std::cout << "La lista de autores est� vacia." << std::endl;
        return;
    }

    // Escribir los autores en el PDF
    do {
        // Separar cada campo en una l�nea diferente
        std::string cedulaTexto = "Cedula: " + actual->getCedula();
        std::string nombreTexto = "Nombre: " + actual->getNombre();
        std::string apellidoTexto = "Apellido: " + actual->getApellido();
        std::string fechaTexto = "Fecha de Publicacion: " + actual->getFechaPublicacion();

        // Escribir la c�dula
        HPDF_Page_BeginText(page);
        HPDF_Page_SetFontAndSize(page, font, 12);
        HPDF_Page_TextOut(page, 50.0f, yPosition, cedulaTexto.c_str());
        HPDF_Page_EndText(page);
        yPosition -= 20.0f;  // Espaciado despu�s de c�dula

        // Escribir el nombre
        HPDF_Page_BeginText(page);
        HPDF_Page_SetFontAndSize(page, font, 12);
        HPDF_Page_TextOut(page, 50.0f, yPosition, nombreTexto.c_str());
        HPDF_Page_EndText(page);
        yPosition -= 20.0f;  // Espaciado despu�s de nombre

        // Escribir el apellido
        HPDF_Page_BeginText(page);
        HPDF_Page_SetFontAndSize(page, font, 12);
        HPDF_Page_TextOut(page, 50.0f, yPosition, apellidoTexto.c_str());
        HPDF_Page_EndText(page);
        yPosition -= 20.0f;  // Espaciado despu�s de apellido

        // Escribir la fecha de publicaci�n
        HPDF_Page_BeginText(page);
        HPDF_Page_SetFontAndSize(page, font, 12);
        HPDF_Page_TextOut(page, 50.0f, yPosition, fechaTexto.c_str());
        HPDF_Page_EndText(page);
        yPosition -= 30.0f;  // Espaciado despu�s de fecha

        // Agregar una l�nea de separaci�n entre autores
        std::string lineaSeparadora = "--------------------------------------------";

        HPDF_Page_BeginText(page);
        HPDF_Page_SetFontAndSize(page, font, 10);
        HPDF_Page_TextOut(page, 50.0f, yPosition, lineaSeparadora.c_str());
        HPDF_Page_EndText(page);
        yPosition -= 20.0f;  // Espaciado despu�s de la l�nea

        // Si el texto se sale de la p�gina, crear una nueva p�gina
        if (yPosition < 100.0f) {
            yPosition = 750.0f;
            page = HPDF_AddPage(pdf);
            HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
            HPDF_Page_SetFontAndSize(page, font, 12);

            // Reimprimir t�tulo en nueva p�gina
            HPDF_Page_BeginText(page);
            HPDF_Page_SetFontAndSize(page, font, 16);
            HPDF_Page_TextOut(page, 50.0f, yPosition, "Lista de Autores");
            HPDF_Page_EndText(page);
            yPosition -= 30.0f;

            // Separador
            HPDF_Page_BeginText(page);
            HPDF_Page_SetFontAndSize(page, font, 10);
            HPDF_Page_TextOut(page, 50.0f, yPosition, "==========================================");
            HPDF_Page_EndText(page);
            yPosition -= 20.0f;
        }

        actual = actual->getSiguiente();

    } while (actual != listaAutores.getCabeza()); // Recorre la lista circular

    // Guardar el archivo PDF
    HPDF_SaveToFile(pdf, nombreArchivo.c_str());
    HPDF_Free(pdf);

    std::cout << "El archivo PDF fue generado correctamente: " << nombreArchivo << std::endl;

    // Abrir el PDF autom�ticamente
    std::string command = "start " + nombreArchivo;  // Para Windows
    // Si est�s en Linux/Mac, usa: std::string command = "xdg-open " + nombreArchivo;
    system(command.c_str());
}

