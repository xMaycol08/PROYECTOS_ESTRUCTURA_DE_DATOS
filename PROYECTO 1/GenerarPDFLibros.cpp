#include "GenerarPDFLibros.h"
#include <iostream>
#include <hpdf.h>
#include <iomanip>
#include <sstream>
#include <cstdlib> // Para abrir el PDF automáticamente

GenerarPDFLibros::GenerarPDFLibros(ListaLibros& listaLibros) : listaLibros(listaLibros) {}

void GenerarPDFLibros::generarPDF(const std::string& nombreArchivo) {
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

    // Título del documento "Lista de Libros"
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, font, 16);
    HPDF_Page_TextOut(page, 50.0f, yPosition, "Lista de Libros");
    HPDF_Page_EndText(page);
    yPosition -= 30.0f;

    // Separador
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, font, 10);
    HPDF_Page_TextOut(page, 50.0f, yPosition, "==========================================");
    HPDF_Page_EndText(page);
    yPosition -= 20.0f;

    // Recorremos la lista de libros y generamos su información en el PDF
    NodoLibros* actual = listaLibros.getCabeza();
    if (actual == nullptr) {
        std::cout << "La lista de libros esta vacia." << std::endl;
        return;
    }

    // Escribir los libros en el PDF
    do {
        // Separar cada campo en una línea diferente
std::string tituloTexto = "Titulo: " + actual->getTitulo();
std::string autorTexto = "Autor: " + actual->getAutor();
std::string isbnTexto = "ISBN: " + actual->getIsbn();
std::string generoTexto = "Genero: " + actual->getGenero();
std::string anioTexto = "Ano de Lanzamiento: " + actual->getAnioLanzamiento();

// Formatear precio con dos decimales
std::ostringstream precioStream;
precioStream << std::fixed << std::setprecision(2) << actual->getPrecio();
std::string precioTexto = "Precio: $" + precioStream.str();

// Formatear calificación con dos decimales
std::ostringstream calificacionStream;
calificacionStream << std::fixed << std::setprecision(2) << actual->getCalificacion();
std::string calificacionTexto = "Calificacion: " + calificacionStream.str();

        // Escribir el título
        HPDF_Page_BeginText(page);
        HPDF_Page_SetFontAndSize(page, font, 12);
        HPDF_Page_TextOut(page, 50.0f, yPosition, tituloTexto.c_str());
        HPDF_Page_EndText(page);
        yPosition -= 20.0f;  // Espaciado después del título

        // Escribir el autor
        HPDF_Page_BeginText(page);
        HPDF_Page_SetFontAndSize(page, font, 12);
        HPDF_Page_TextOut(page, 50.0f, yPosition, autorTexto.c_str());
        HPDF_Page_EndText(page);
        yPosition -= 20.0f;  // Espaciado después del autor

        // Escribir el ISBN
        HPDF_Page_BeginText(page);
        HPDF_Page_SetFontAndSize(page, font, 12);
        HPDF_Page_TextOut(page, 50.0f, yPosition, isbnTexto.c_str());
        HPDF_Page_EndText(page);
        yPosition -= 20.0f;  // Espaciado después del ISBN

        // Escribir el género
        HPDF_Page_BeginText(page);
        HPDF_Page_SetFontAndSize(page, font, 12);
        HPDF_Page_TextOut(page, 50.0f, yPosition, generoTexto.c_str());
        HPDF_Page_EndText(page);
        yPosition -= 20.0f;  // Espaciado después del género

        // Escribir el año de lanzamiento
        HPDF_Page_BeginText(page);
        HPDF_Page_SetFontAndSize(page, font, 12);
        HPDF_Page_TextOut(page, 50.0f, yPosition, anioTexto.c_str());
        HPDF_Page_EndText(page);
        yPosition -= 20.0f;  // Espaciado después del año de lanzamiento

        // Escribir el precio
        HPDF_Page_BeginText(page);
        HPDF_Page_SetFontAndSize(page, font, 12);
        HPDF_Page_TextOut(page, 50.0f, yPosition, precioTexto.c_str());
        HPDF_Page_EndText(page);
        yPosition -= 20.0f;  // Espaciado después del precio

        // Escribir la calificación
        HPDF_Page_BeginText(page);
        HPDF_Page_SetFontAndSize(page, font, 12);
        HPDF_Page_TextOut(page, 50.0f, yPosition, calificacionTexto.c_str());
        HPDF_Page_EndText(page);
        yPosition -= 30.0f;  // Espaciado después de la calificación

        // Agregar una línea de separación entre libros
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
            HPDF_Page_TextOut(page, 50.0f, yPosition, "Lista de Libros");
            HPDF_Page_EndText(page);
            yPosition -= 30.0f;

            // Separador
            HPDF_Page_BeginText(page);
            HPDF_Page_SetFontAndSize(page, font, 10);
            HPDF_Page_TextOut(page, 50.0f, yPosition, "==========================================");
            HPDF_Page_EndText(page);
            yPosition -= 20.0f;
        }

        // Avanzar al siguiente libro en la lista
        actual = actual->getSiguiente();

    } while (actual != listaLibros.getCabeza()); // Recorre la lista circular

    // Guardar el archivo PDF
    HPDF_SaveToFile(pdf, nombreArchivo.c_str());
    HPDF_Free(pdf);

    std::cout << "El archivo PDF fue generado correctamente: " << nombreArchivo << std::endl;

    // Abrir el archivo PDF generado
    #if defined(_WIN32) || defined(_WIN64)
        system(("start " + nombreArchivo).c_str());  // En Windows
    #elif defined(__linux__)
        system(("xdg-open " + nombreArchivo).c_str());  // En Linux
    #elif defined(__APPLE__)
        system(("open " + nombreArchivo).c_str());  // En macOS
    #endif
}
