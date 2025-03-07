#ifndef PDF_GENERATOR_H
#define PDF_GENERATOR_H

#include <string>
#include <vector>

// Función para dividir una línea por el delimitador ';'
std::vector<std::string> split(const std::string &line, char delimiter);

// Función para obtener la fecha y hora actual en formato YYYY-MM-DD HH:MM
std::string getCurrentDateTime();

// Función para crear el PDF
void createPDF(const std::string& inputFile);

#endif // PDF_GENERATOR_H
