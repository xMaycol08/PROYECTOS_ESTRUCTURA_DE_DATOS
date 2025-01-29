/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Archivo principal de proyecto                            *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          01/01/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include <iostream>
#include <windows.h>
#include "Menu.h"
#include "ArbolBTree.h"
#include "BackupManager.h"


int main() {
    // Configurar la consola para usar UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Verifica y crea la carpeta de backups si no existe
    BackupManager::crearCarpetaSiNoExiste("backup");

    ArbolBTree arbol(3);
    // Cargar los libros desde el archivo al iniciar
    try {
        arbol.cargarLibrosDesdeArchivo();
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error al cargar los libros desde el archivo: " << e.what() << std::endl;
        return 1;
    }

    mostrarMenu(arbol);
    return 0;
}

