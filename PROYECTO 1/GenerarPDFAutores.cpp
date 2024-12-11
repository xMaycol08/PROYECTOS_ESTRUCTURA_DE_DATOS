#include "GenerarPDFAutores.h"
#include <iostream>
#include <hpdf.h>
#include <cstdlib>  // Para usar system() y abrir el PDF automáticamente

GenerarPDFAutores::GenerarPDFAutores(ListaAutores& listaAutores) : listaAutores(listaAutores) {}

void GenerarPDFAutores::generarPDF(const std::string& nombreArchivo) {
    // Crear un documento PDF
    HPDF_Doc pdf = HPDF_New(nullptr, nullptr);
    if (!pdf) {
        std::cerr << "Error al crear el documento PDF." << std::endl;
        return;
    }

    // Crear una página en blanco
    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

    // Establecer las fuentes
    HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", nullptr);
    HPDF_Page_SetFontAndSize(page, font, 12);

    // Definir la posición inicial para el texto
    float yPosition = 750.0f;

    // Título del documento
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

    // Recorremos la lista de autores y generamos su información en el PDF
    NodoAutores* actual = listaAutores.getCabeza();
    if (actual == nullptr) {
        std::cout << "La lista de autores está vacia." << std::endl;
        return;
    }

    // Escribir los autores en el PDF
    do {
        // Separar cada campo en una línea diferente
        std::string cedulaTexto = "Cedula: " + actual->getCedula();
        std::string nombreTexto = "Nombre: " + actual->getNombre();
        std::string apellidoTexto = "Apellido: " + actual->getApellido();
        std::string fechaTexto = "Fecha de Publicacion: " + actual->getFechaPublicacion();

        // Escribir la cédula
        HPDF_Page_BeginText(page);
        HPDF_Page_SetFontAndSize(page, font, 12);
        HPDF_Page_TextOut(page, 50.0f, yPosition, cedulaTexto.c_str());
        HPDF_Page_EndText(page);
        yPosition -= 20.0f;  // Espaciado después de cédula

        // Escribir el nombre
        HPDF_Page_BeginText(page);
        HPDF_Page_SetFontAndSize(page, font, 12);
        HPDF_Page_TextOut(page, 50.0f, yPosition, nombreTexto.c_str());
        HPDF_Page_EndText(page);
        yPosition -= 20.0f;  // Espaciado después de nombre

        // Escribir el apellido
        HPDF_Page_BeginText(page);
        HPDF_Page_SetFontAndSize(page, font, 12);
        HPDF_Page_TextOut(page, 50.0f, yPosition, apellidoTexto.c_str());
        HPDF_Page_EndText(page);
        yPosition -= 20.0f;  // Espaciado después de apellido

        // Escribir la fecha de publicación
        HPDF_Page_BeginText(page);
        HPDF_Page_SetFontAndSize(page, font, 12);
        HPDF_Page_TextOut(page, 50.0f, yPosition, fechaTexto.c_str());
        HPDF_Page_EndText(page);
        yPosition -= 30.0f;  // Espaciado después de fecha

        // Agregar una línea de separación entre autores
        std::string lineaSeparadora = "--------------------------------------------";

        HPDF_Page_BeginText(page);
        HPDF_Page_SetFontAndSize(page, font, 10);
        HPDF_Page_TextOut(page, 50.0f, yPosition, lineaSeparadora.c_str());
        HPDF_Page_EndText(page);
        yPosition -= 20.0f;  // Espaciado después de la línea

        // Si el texto se sale de la página, crear una nueva página
        if (yPosition < 100.0f) {
            yPosition = 750.0f;
            page = HPDF_AddPage(pdf);
            HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
            HPDF_Page_SetFontAndSize(page, font, 12);

            // Reimprimir título en nueva página
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

    // Abrir el PDF automáticamente
    std::string command = "start " + nombreArchivo;  // Para Windows
    // Si estás en Linux/Mac, usa: std::string command = "xdg-open " + nombreArchivo;
    system(command.c_str());
}

