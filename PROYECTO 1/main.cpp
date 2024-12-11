#include "ListaAutores.h"
#include "ListaLibros.h"
#include "Validaciones.h"
#include "GenerarPDFLibros.h"
#include "GenerarPDFAutores.h"
#include "VentanaAyuda.h"
#include "Cursor.h"
#include <iostream>
#include <cstdlib> // Para system()
#include <limits>
#include <hpdf.h>
#include <conio.h>
#include "BackupManager.h"
#include "FileUtils.h"
#include <ctime>
#include <string>
// Men� para manejar las opciones de "Autores"
void menuAutores(ListaAutores& listaAutores) {
    int opcion;
    do {
        system("cls");
        string opciones[] = {
            "1. Insertar Autor",
            "2. Buscar Autor",
            "3. Eliminar Autor",
            "4. Mostrar Autores",
            "5. Generar PDF Autores",
            "6. Crear Backup de Autores",
            "7. Restaurar Backup de Autores",
            "8. Volver al menu principal"
        };

        Cursor cursor(8);  // Crear cursor para 8 opciones
        cursor.actualizarMenu(opciones, 8);

        while (true) {
            if (cursor.teclaPresionada()) {
                char tecla = _getch();
                if (tecla == 72) {  // Flecha arriba
                    cursor.moverArriba();
                    cursor.actualizarMenu(opciones, 8);
                } else if (tecla == 80) {  // Flecha abajo
                    cursor.moverAbajo();
                    cursor.actualizarMenu(opciones, 8);
                } else if (tecla == 13) {  // Enter
                    opcion = cursor.getPosicion() + 1;
                    break;
                }
            }
        }


       switch (opcion) {
       case 1: {
           string cedula, nombre, apellido, fechaPublicacion;
          while (true) {
    cout << "Ingrese la cedula: ";
    cin >> cedula;

    if (!validarCedula(cedula)) {
        cout << "Error: La cedula ingresada no es valida. Intente de nuevo.\n";
        continue;
    }
    if (listaAutores.buscar(cedula)) {
        cout << "Error: El autor con cedula " << cedula << " ya existe. Ingrese una cedula diferente.\n";
    } else {
        break;
    }
    }
          while (true) {
        cout << "Ingrese nombre: ";
        cin >> nombre;
        if (validarTexto(nombre)) break;
        cout << "Error: El nombre debe contener solo letras y espacios.\n";
        }
        while (true) {
        cout << "Ingrese apellido: ";
        cin >> apellido;
        if (validarTexto(apellido)) break;
        cout << "Error: El apellido debe contener solo letras y espacios.\n";
        }

         while (true) {
        cout << "Ingrese fecha de publicacion (MM/DD/YYYY): ";
        cin >> fechaPublicacion;
        if (validarFecha(fechaPublicacion)) {
            break;
        }
        cout << "Error: Intente nuevamente.\n";
    }

    listaAutores.insertar(cedula, nombre, apellido, fechaPublicacion);
    system("pause");

    break;
}

       case 2: {
    string cedula;

    while (true) {
        cout << "Ingrese cedula del autor: ";
        cin >> cedula;
        if (validarCedula(cedula)) break;
        cout << "Error: La cedula ingresada no es valida\n";}

    NodoAutores* autor = listaAutores.buscar(cedula);
    if (autor) {

        cout << "Autor encontrado:\n";
        cout << "Nombre: " << autor->getNombre() << "\n";
        cout << "Apellido: " << autor->getApellido() << "\n";
    } else {

        cout << "Autor no encontrado con la cedula proporcionada.\n";
    }
    system("pause");
    break;
}

        case 3: {
            string cedula;
    while (true) {
        cout << "Ingrese cedula del autor a eliminar: ";
        cin >> cedula;
        if (validarCedula(cedula)) break;
        cout << "Error: La cedula ingresada no es valida.\n";
    }

    bool eliminado = listaAutores.eliminar(cedula);
    if (eliminado) {
        cout << "Autor con cedula " << cedula << " eliminado exitosamente.\n";
    } else {
        cout << "Error: No se encontro un autor con la cedula proporcionada.\n";
    }
    system("pause");
    break;
        }


        case 4:
            listaAutores.mostrar();
            system("pause");
            break;
        case 5:
           {
            GenerarPDFAutores generador(listaAutores);
            generador.generarPDF("autores_lista.pdf");
            }
            system("pause");
            break;
         case 6:
                listaAutores.crearBackup(); // Crear backup
                system("pause");
                break;
            case 7: {
                // Listar los backups disponibles
    std::vector<std::string> backupsAutores = BackupManager::listarArchivosEnCarpeta("BackupAutores");
    if (backupsAutores.empty()) {
        std::cout << "No hay backups disponibles en la carpeta 'BackupAutores'.\n";
    } else {
        std::cout << "Backups disponibles en 'BackupAutores':\n";
        for (const auto& archivo : backupsAutores) {
            std::cout << "- " << archivo << "\n";
        }
        std::cout << "Ingrese el nombre del archivo de backup a restaurar: ";
        std::string nombreBackup;
        std::cin >> nombreBackup;

        // Intentar restaurar el backup
        listaAutores.restaurarBackup(nombreBackup);

    }
    system("pause");
    break;
            }
            case 8:
                cout << "Volviendo al menu principal...\n";
                system("pause");
                break;
        }
    } while (opcion != 8);
}

// MenU para manejar las opciones de "Libros"
void menuLibros(ListaLibros& listaLibros, ListaAutores& listaAutores) {
    int opcion;
    do {
        system("cls");
        string opciones[] = {
            "1. Insertar Libro",
            "2. Buscar Libro",
            "3. Eliminar Libro",
            "4. Mostrar Libros",
            "5. Generar PDF de Libros",
            "6. Crear Backup de Libros",
            "7. Restaurar Backup de Libros",
            "8. Filtrar Libros por Año",
            "9. Volver al menu principal"
        };


        Cursor cursor(9);  // Crear cursor para 9 opciones
        cursor.actualizarMenu(opciones, 9);

        while (true) {
            if (cursor.teclaPresionada()) {
                char tecla = _getch();
                if (tecla == 72) {  // Flecha arriba
                    cursor.moverArriba();
                    cursor.actualizarMenu(opciones, 9);
                } else if (tecla == 80) {  // Flecha abajo
                    cursor.moverAbajo();
                    cursor.actualizarMenu(opciones, 9);
                } else if (tecla == 13) {  // Enter
                    opcion = cursor.getPosicion() + 1;
                    break;
                }
            }
        }

        switch (opcion) {

        case 1: {

    string titulo, isbn, genero, anioLanzamiento;
    double precio, calificacion;
    string autor = listaLibros.seleccionarAutor(listaAutores);
    if (autor.empty()) break;

   do {
    cout << "Ingrese titulo: ";
    cin.ignore();
    getline(cin, titulo);
} while (titulo.empty());


    while(true) {
        cout << "Ingrese ISBN: ";
        getline(cin, isbn);
        if (!validarISBN(isbn)) {
            cout << "Error: El ISBN solo puede contener digitos y guiones y formato ej.(15-1).\n";
        continue;
        }
        if(listaLibros.buscar(isbn)){
            cout << "Error: El libro con ISBN " << isbn << " ya existe. Ingrese una ISBN diferente.\n";
            continue;
        }else{
            break;
        }
    }

    do {
        cout << "Ingrese su Clasificacion: ";
        getline(cin, genero);
        if (!validarTexto(genero)) {
            cout << "Error: El clasificacion solo puede contener letras y espacios.\n";
        }
    } while (!validarTexto(genero));

    do {
        cout << "Ingrese fecha de lanzamiento (MM/DD/AAAA): ";
        getline(cin, anioLanzamiento);
        if (!validarFecha(anioLanzamiento)) {
           // cout << "Error: Fecha invalida. Usa el formato MM/DD/AAAA.\n";
        }
    } while (!validarFecha(anioLanzamiento));

    do {
        cout << "Ingrese precio: ";
        if (!ingresarNumero(precio) || !validarPrecio(precio)) {
            cout << "Error: El precio debe ser un numero positivo.\n";
        }
    } while (!validarPrecio(precio));

    do {
        cout << "Ingrese calificacion (0-10): ";
        if (!ingresarNumero(calificacion) || !validarCalificacion(calificacion)) {
            cout << "Error: La calificacion debe ser entre 0 y 10.\n";
        }
    } while (!validarCalificacion(calificacion));

    listaLibros.insertar(titulo, autor, isbn, genero, anioLanzamiento, precio, calificacion);
    cout << "Libro ingresado exitosamente.\n";
    system("pause");
    break;

        }
        case 2: {
            string isbn;
            do {
        cout << "Ingrese ISBN del libro: ";
        cin >> isbn;
        if (!validarISBN(isbn)) {
            cout << "Error: El ISBN debe contener solo digitos y guiones y formato ej.(15-1).\n";
        }
    } while (!validarISBN(isbn));

            NodoLibros* libro = listaLibros.buscar(isbn);
            if (libro) {
                cout << "Libro encontrado: " << libro->getTitulo() << " por " << libro->getAutor() << "\n";
            } else {
                cout << "Libro no encontrado.\n";
            }
            system("pause");
            break;
        }
        case 3: {
            string isbn;
            do {
                    cout << "Ingrese ISBN del libro: ";
                    cin >> isbn;
                    if (!validarISBN(isbn)) {
                            cout << "Error: Ingrese un ISBN valida ej.(15-1).\n";}
              } while (!validarISBN(isbn));

           if (listaLibros.eliminar(isbn)) {
             cout << "El libro con ISBN " << isbn << " ha sido eliminado exitosamente.\n";
             } else {
             cout << "El libro con ISBN " << isbn << " no se encontro en la lista.\n";
            }
            system("pause");
            break;
        }
        case 4:
            listaLibros.mostrar();
            system("pause");
            break;
        case 5:
            {
            GenerarPDFLibros generadorPDF(listaLibros);
            // Generar el archivo PDF con los libros
            generadorPDF.generarPDF("libros_lista.pdf");
            }
            system("pause");
            break;
        case 6:
                listaLibros.crearBackup(); // Crear backup
                system("pause");
                break;
            case 7: {
                std::vector<std::string> backupsLibros = BackupManager::listarArchivosEnCarpeta("BackupLibros");
        if (backupsLibros.empty()) {
        std::cout << "No hay backups disponibles en la carpeta 'BackupLibros'.\n";
        } else {
        std::cout << "Backups disponibles en 'BackupLibros':\n";
        for (const auto& archivo : backupsLibros) {
        std::cout << "- " << archivo << "\n";
        }
        std::cout << "Ingrese el nombre del archivo de backup a restaurar: ";
        std::string nombreBackup;
        std::cin >> nombreBackup;
        // Intentar restaurar el backup
        listaLibros.restaurarBackup(nombreBackup);
    }
    system("pause");
    break;
            }
            case 8:
            listaLibros.filtrarPorAnio(); // Llamar a la nueva función
            system("pause");
            break;
        case 9:
            cout << "Volviendo al menu principal...\n";
            system("pause");
            break;
        }
    } while (opcion != 9);
}

int main() {
    ListaLibros listaLibros;
    ListaAutores listaAutores;
    VentanaAyuda ventanaAyuda;

    listaAutores.cargarDesdeArchivoJSON();
    listaLibros.cargarDesdeArchivoJSON();

    int opcionMenu;

    do {
        system("cls");
        string opciones[] = {
            "1. Manejar Autores",
            "2. Manejar Libros",
            "3. Ayuda",
            "4. Salir"
        };

        Cursor cursor(4);  // Crear cursor para 4 opciones
        cursor.actualizarMenu(opciones, 4);

        while (true) {
            if (cursor.teclaPresionada()) {
                char tecla = _getch();
                if (tecla == 72) {  // Flecha arriba
                    cursor.moverArriba();
                    cursor.actualizarMenu(opciones, 4);
                } else if (tecla == 80) {  // Flecha abajo
                    cursor.moverAbajo();
                    cursor.actualizarMenu(opciones, 4);
                } else if (tecla == 13) {  // Enter
                    opcionMenu = cursor.getPosicion() + 1;
                    break;
                }
            }
        }

        switch (opcionMenu) {
        case 1:
            menuAutores(listaAutores);
            break;
        case 2:
            menuLibros(listaLibros, listaAutores);
            break;
        case 3:
            ventanaAyuda.mostrar();
            break;
        case 4:
            cout << "Saliendo...\n";
            system("pause");
            break;
        }

    } while (opcionMenu != 4);

    return 0;
}
