#include "../include/pdf_generator.h"
#include "hpdf.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <ctime>

using namespace std;

// Función para dividir una cadena por un delimitador
vector<string> split(const string &line, char delimiter) {
    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Función para obtener la fecha y hora actual en formato "YYYY-MM-DD HH:MM"
string getCurrentDateTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[17];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", ltm);
    return string(buffer);
}

// Función para generar el PDF
void createPDF(const string &inputFile) {
    HPDF_Doc pdf = HPDF_New(NULL, NULL);
    if (!pdf) {
        cerr << "Error al crear el PDF" << endl;
        return;
    }

    ifstream file(inputFile);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo: " << inputFile << endl;
        HPDF_Free(pdf);
        return;
    }

    string currentDateTime = getCurrentDateTime();
    map<string, vector<vector<string>>> reservas;

    // Leer el archivo de reservas y agrupar por fecha y hora exactas
    string line;
    while (getline(file, line)) {
        vector<string> fields = split(line, ',');
        if (fields.size() != 6) continue;  // Verificar que haya 6 campos

        string fechaHora = fields[5];  // "YYYY-MM-DD HH:MM"
        reservas[fechaHora].push_back(fields);
    }
    file.close();

    // Crear una nueva página en el PDF
    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
    HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
    HPDF_Page_SetFontAndSize(page, font, 12);
    float y = 800;
    float x = 50;

    // Título del reporte
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, x, y, "REPORTE DE RESERVAS");
    HPDF_Page_EndText(page);
    y -= 30;

    // Recorrer todas las reservas agrupadas por fecha y hora
    for (auto &reserva : reservas) {
        string fechaHora = reserva.first;
        y -= 20;

        // Subtítulo con la fecha y hora de las reservas
        HPDF_Page_BeginText(page);
        string titulo = "RESERVAS DE " + fechaHora;
        HPDF_Page_TextOut(page, x, y, titulo.c_str());
        HPDF_Page_EndText(page);
        y -= 20;

        // Encabezado de la tabla
        HPDF_Page_BeginText(page);
        HPDF_Page_TextOut(page, x, y, "Cliente");
        HPDF_Page_TextOut(page, x + 150, y, "Contacto/Correo");
        HPDF_Page_TextOut(page, x + 300, y, "#Mesa");
        HPDF_Page_TextOut(page, x + 400, y, "Estado");
        HPDF_Page_EndText(page);
        y -= 10;

        // Línea divisoria
        HPDF_Page_MoveTo(page, x, y);
        HPDF_Page_LineTo(page, x + 500, y);
        HPDF_Page_Stroke(page);
        y -= 20;

        // Recorrer cada reserva en la fecha y hora exactas
        for (auto &datos : reserva.second) {
            string estado = (fechaHora < currentDateTime) ? "Reserva caducada" : "Reserva Activa";

            HPDF_Page_BeginText(page);
            HPDF_Page_TextOut(page, x, y, datos[1].c_str());        // Cliente
            HPDF_Page_TextOut(page, x + 150, y, datos[3].c_str());  // Contacto/Correo
            HPDF_Page_TextOut(page, x + 300, y, datos[4].c_str());  // Mesa
            HPDF_Page_TextOut(page, x + 400, y, estado.c_str());    // Estado
            HPDF_Page_EndText(page);
            y -= 20;

            // Crear nueva página si no hay suficiente espacio
            if (y < 100) {
                page = HPDF_AddPage(pdf);
                HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
                HPDF_Page_SetFontAndSize(page, font, 12);
                y = 800;
            }
        }
    }

    // Guardar el PDF
    HPDF_SaveToFile(pdf, "reservas.pdf");
    HPDF_Free(pdf);
    cout << "PDF generado correctamente en 'reservas.pdf'" << endl;
}
