// DesafioFinalSegundaChance.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include <string>
#include <vector>
#include "./Entidades/Libro.h"
#include "./Entidades/SocioVip.h"
#include "./Entidades/Prestamo.h"
#include "Validador.h"
#include "./DataHelpers/DataHelper.h"
#include "./DataHelpers/SocioDataHelper.h"
#include "./DataHelpers/LibroDataHelper.h"


using namespace std;
list<Ejemplar*> Ejemplares;
list<Libro*> Libros;
list<Prestamo*> PrestamosVigentes;
list<Prestamo*> Devoluciones;
list<Socio*> Socios;
#pragma region Visualizacion de datos

void VerSocios() {
    system("cls");
    cout << SocioDataHelper::GetEncabezadoSocios();
    system("PAUSE");
}
void VerLibros() {
    system("cls");
    cout << LibroDataHelper::GetEncabezadoLibros();
    system("PAUSE");

}
void VerPrestamos() {
    system("cls");
    cout << DataHelper::GetEncabezadoPrestamosVigentes(PrestamosVigentes, Libros);
    system("PAUSE");
}
void VerDevoluciones() {
    system("cls");
    cout << DataHelper::GetEncabezadoPrestamosFinalizados(Devoluciones, Libros);
    system("PAUSE");
}
#pragma endregion

#pragma region Definiciones en pantalla
void MainMenu() {
    system("cls");
    cout << "Bienvenido a la biblioteca, ¿que desea hacer? \n";
    cout << "1 - Administracion socio \n";
    cout << "2 - Administracion libro \n";
    cout << "3 - Administracion ejemplar \n";
    cout << "4 - Nuevo prestamo \n";
    cout << "5 - Devolución de prestamo \n";
    cout << "6 - Ver prestamos vigentes \n";
    cout << "7 - Ver historial de devoluciones \n";
    cout << "8 - Ver socios\n";
    cout << "9 - Ver libros\n";
    cout << "0 - Salir \n";
}

void OptionsSocio() {
    system("cls");
    cout << "1 - Alta socio" << endl;
    cout << "2 - Baja socio" << endl;
    cout << "3 - Mostrar ejemplares" << endl;
    cout << "0 - Volver" << endl;
}
void OptionsLibro() {
    system("cls");
    cout << "1 - Alta libro" << endl;
    cout << "2 - Baja libro" << endl;
    cout << "3 - Mostrar ejemplares" << endl;
    cout << "0 - Volver" << endl;
}
void OptionsEjemplar() {
    system("cls");
    cout << "1 - Alta ejemplar" << endl;
    cout << "0 - Volver" << endl;
}
#pragma endregion

#pragma region ABM Socio
void AgregarSocio() {
    system("cls");
    string nombre, apellido;
    float cuota;
    int esVip, idSoc;
    bool continuar = true;
    char siNo;
    cout << "NUEVO SOCIO: \n";
    while (continuar) {
        cout << "Ingrese nombre: ";
        cin.ignore();
        cin.clear();
        getline(std::cin, nombre);
        continuar = Validador::ValidarStringConNombre(nombre);
        if (continuar) {
            while (continuar) {
                cin.ignore();
                cin.clear();
                cout << "Ingrese apellido: ";
                getline(std::cin, apellido);
                continuar = Validador::ValidarStringConNombre(apellido);
                if (continuar) {
                        cout << " ¿Sera VIP? 1:SI - 0:NO \n";
                        cin >> esVip;
                        idSoc = Socios.size() > 0 ? Socios.back()->IdSocio + 1 : 0;
                        if (esVip == 1) {
                            cout << "\nCual es el valor de su cuota?";
                            cin >> cuota;
                            Socios.push_back((Socio*)new SocioVip(idSoc, nombre, apellido, true, cuota));
                        }
                        else
                            Socios.push_back(new Socio(idSoc, nombre, apellido));
                        SocioDataHelper::SaveSocios(Socios);
                        cout << "\n Muchas gracias ya se agrego " << nombre << " " << apellido<<" a nuestra base\n";
                        continuar = false;
                        system("PAUSE");
                }
                else {
                    cout << "\nEl apellido del socio no es valido, desea intentarlo de nuevo? S/N\n";
                    cin >> siNo;
                    if (siNo == 'n' || siNo == 'N')
                        continuar = false;
                }
            }
        }
        else {
            cout << "\nEl nombre del socio no es valido, desea intentarlo de nuevo? S/N\n";
            cin >> siNo;
            if (siNo == 'n' || siNo == 'N')
                continuar = false;
        }
    }
}

void EliminarSocio() {
    int idSoc;
    char siNo;
    bool seguirDeNuevo=true;
    Socio* aEliminar = nullptr;
    system("cls");
    cout << "ELIMINAR SOCIO: \n";
    while (seguirDeNuevo) {
        cout << SocioDataHelper::GetEncabezadoSocios();
        cout << "\nIngrese el id del socio a eliminar: ";
        cin >> idSoc;
        for (Socio* socio : Socios) {
            if (socio->IdSocio == idSoc) {
                aEliminar = socio;
                break;
            }
        }
        if (aEliminar != nullptr) {
            Socios.remove(aEliminar);
            SocioDataHelper::SaveSocios(Socios);
            seguirDeNuevo = false;
            cout << "\nSe elimino el socio " << aEliminar->NombreCompleto() << endl;
            system("PAUSE");
        }
        else {
            cout << "\nEl id ingresado no es valido, desea intentarlo de nuevo? S/N\n";
            cin >> siNo;
            if (siNo == 'n' || siNo == 'N')
                seguirDeNuevo = false;
        }
    }
}

void MostrarEjemplaresRetirados() {
    int idSoc;
    char siNo;
    bool seguirDeNuevo = true;
    Socio* aMostrar = nullptr;
    system("cls");
    cout << "EJEMPLARES SOCIO: \n";
    while (seguirDeNuevo) {
        cout << SocioDataHelper::GetEncabezadoSocios();
        cout << "\nIngrese el id del socio a verificar: ";
        cin >> idSoc;
        aMostrar = Validador::ValidarSocio(idSoc, Socios);
        if (aMostrar != nullptr) {
            cout << endl << SocioDataHelper::GetEncabezadoEjemplares(aMostrar) << endl;
            seguirDeNuevo = false;
            system("PAUSE");
        }
        else {
            cout << "\nEl id ingresado no es valido, desea intentarlo de nuevo? S/N\n";
            cin >> siNo;
            if (siNo == 'n' || siNo == 'N')
                seguirDeNuevo = false;
        }
    }
}

#pragma endregion

#pragma region ABM Libro
void AgregarLibro() {
    system("cls");
    string nombre, autor;
    int codIS;
    char siNo;
    bool continuar = true;
    cout << "NUEVO LIBRO: \n";
    while (continuar) {
        cout << "Ingrese nombre: ";
        cin.ignore();
        cin.clear();
        getline(std::cin, nombre);
        continuar = Validador::ValidarStringVacio(nombre);
        if (continuar) {
            while (continuar) {
                cout << "Ingrese autor: ";
                cin.clear();
                getline(std::cin, autor);
                continuar = Validador::ValidarStringConNombre(autor);
                if (continuar) {
                    codIS = Libros.size() > 0 ? Libros.back()->CodISBN + 1 : 0;
                    Libro* libro = new Libro(codIS, nombre, autor);
                    Libros.push_back(libro);
                    LibroDataHelper::SaveLibros(Libros);
                    continuar = false;
                    cout << "\n Muchas gracias ya se agrego " << nombre << " de " << autor << " a nuestra base\n";

                }
                else {
                    cout << "\nEl nombre del autor no es valido, desea intentarlo de nuevo? S/N\n";
                    cin >> siNo;
                    if (siNo == 'n' || siNo == 'N')
                        continuar = false;
                }

            }

        }
        else {
            cout << "\nNo ha ingresado el nombre del libro, desea intentarlo de nuevo? S/N\n";
            cin >> siNo;
            if (siNo == 'n' || siNo == 'N')
                continuar = false;
        }
    }
    system("PAUSE");
}
void EliminarLibro() {
    system("cls");
    int idLibro;
    char siNo;
    bool seguirDeNuevo = true;
    Libro* aEliminar = nullptr;
    cout << "ELIMINAR LIBRO: \n";
    while (seguirDeNuevo) {
        cout << LibroDataHelper::GetEncabezadoLibros();
        cout << "\nIngrese el id del libro a eliminar: ";
        cin >> idLibro;
        aEliminar = Validador::ValidarLibro(idLibro, Libros);
        if (aEliminar != nullptr) {
            Libros.remove(aEliminar);
            LibroDataHelper::SaveLibros(Libros);
            seguirDeNuevo = false;
            system("PAUSE");
        }
        else {
            cout << "\nEl id ingresado no es valido, desea intentarlo de nuevo?\n";
            cin >> siNo;
            if (siNo == 'n' || siNo == 'N')
                seguirDeNuevo = false;
        }
    }
}
void MostrarEjemplaresLibro() {
    system("cls");
    int idLibro;
    char siNo;
    bool seguirDeNuevo = true;
    Libro* aMostrar = nullptr;
    cout << "EJEMPLARES LIBRO: \n";
    while (seguirDeNuevo) {
        cout << LibroDataHelper::GetEncabezadoLibros();
        cout << "\nIngrese el id del libro a verificar: ";
        cin >> idLibro;
        aMostrar = Validador::ValidarLibro(idLibro, Libros);
        if (aMostrar != nullptr) {
            cout <<endl<< LibroDataHelper::GetEncabezadoEjemplares(aMostrar)<<endl;
            seguirDeNuevo = false;
            system("PAUSE");
        }
        else {
            cout << "\nEl id ingresado no es valido, desea intentarlo de nuevo?\n";
            cin >> siNo;
            if (siNo == 'n' || siNo == 'N')
                seguirDeNuevo = false;
        }
    }
}

#pragma endregion

void AgregarEjemplar() {
    system("cls");
    string ubicacion;
    Libro* libroVal;
    bool continuar=true;
    int idLibro, idEj;
    char siNo;
    cout << "NUEVO EJEMPLAR: \n";
    while (continuar) {
        cin.ignore();
        cout << LibroDataHelper::GetEncabezadoLibros();
        cout << "Ingrese codigo de libro: ";
        cin >> idLibro;
        libroVal = Validador::ValidarLibro(idLibro, Libros);
        if (libroVal!= nullptr) {
            cout << "Ingrese ubicacion: ";
            cin.ignore();
            cin.clear();
            getline(std::cin, ubicacion);
            idEj = Ejemplares.size() > 0 ? Ejemplares.back()->IdEdicion + 1 : 0;
            Ejemplar* ej = new Ejemplar(idLibro, idEj, ubicacion);
            Ejemplares.push_back(ej);
            libroVal->AgregarEjemplar(ej);
            EjemplarDataHelper::SaveEjemplares(Ejemplares);
            continuar = false;
            cout << "\n Muchas gracias ya se agrego el ejemplar a nuestra base\n";
            system("PAUSE");
        }
        else {
            cout << "El id de libro ingresado no es valido, desea intentarlo de nuevo?";
            cin >> siNo;
            if (siNo == 'n' || siNo == 'N') {
                continuar = false;
            }
        }

    }
}

void AgregarPrestamo() {
    int idSoc, idLibro;
    bool volverAlMenu = false, ingresarOtroLibro = true;
    char siNo;
    Socio* socio;
    Libro* libro=nullptr;
    Ejemplar* ej;
    while(!volverAlMenu) {
        system("cls");
        cout << SocioDataHelper::GetEncabezadoSocios();
        cout << "Ingrese codigo de socio: ";
        cin.ignore();
        cin.clear();
        cin >> idSoc;
        socio=Validador::ValidarSocio(idSoc, Socios);
        if (socio != nullptr) {
            if (socio->PuedeRetirar()) {
                while (ingresarOtroLibro) {
                    cout << endl <<LibroDataHelper::GetEncabezadoLibros();
                    cout << "\nIngrese codigo de libro: ";
                    cin.ignore();
                    cin.clear();
                    cin >> idLibro;
                    libro = Validador::ValidarLibro(idLibro, Libros);
                    if (libro != nullptr) {
                        if (libro->HayEjemplares()) {
                            ej = libro->PrestarEjemplar();
                            socio->RetirarEjemplar(ej);
                            int idPres = PrestamosVigentes.size() > 0 ? PrestamosVigentes.back()->idPrestamo + 1 : 0;
                            Prestamo* aux = new Prestamo(idPres, socio, ej);
                            PrestamosVigentes.push_back(aux);
                            DataHelper::SavePrestamos(PrestamosVigentes);
                            cout << "\nSe ha generado el prestamo al socio/a " << socio->NombreCompleto()<<endl;
                            system("PAUSE");
                            ingresarOtroLibro = false;
                            volverAlMenu = true;
                        }
                        else {
                            cout << "\n El libro ingresado no posee ejemplares disponibles, ¿desea ingresar otro libro? ";
                            cin >> siNo;
                            if (siNo == 'n' || siNo == 'N') {
                                volverAlMenu = true;
                                ingresarOtroLibro = false;
                            }
                        }
                    }
                    else {
                        cout << "El libro ingresado no existe, ¿desea ingresar otro? S/N ";
                        cin >> siNo;
                        if (siNo == 'n' || siNo == 'N') {
                            volverAlMenu = true;
                            ingresarOtroLibro = false;
                        }
                    }
                }
            } else {
                cout << "\n El socio ingresado no tiene cupo disponible para retirar";
                cout << "\n ¿Desea intentar con otro socio? S/N";
                cin >> siNo;
                if (siNo == 'n' || siNo == 'N')
                    volverAlMenu = true;
                }

        }
        else {
            cout << "\n El socio ingresado no existe";
            cout << "\n ¿Desea intentar con otro socio? S/N";
            cin >> siNo;
            if (siNo == 'n' || siNo == 'N')
                volverAlMenu = true;
        }
    }
}
void FinalizarPrestamo() {
    int idPrestamo;
    bool volverAlMenu = false;
    char siNo;
    while (!volverAlMenu) {
        system("cls");
        cout << DataHelper::GetEncabezadoPrestamosVigentes(PrestamosVigentes, Libros);
        cout << "\nIngrese el codigo de prestamo a devolver: ";
        cin.ignore();
        cin.clear();
        cin >> idPrestamo;
        Prestamo* prestamo = nullptr;
        for (Prestamo* prestmo : PrestamosVigentes) {
            if (prestmo->idPrestamo == idPrestamo) {
                prestamo = prestmo;
                break;
            }
        }
        if (prestamo != nullptr) {
            Libro* libro = LibroDataHelper::GetLibroById(prestamo->IdEjemplar->CodISBNLibro, Libros);
            Socio* socio = SocioDataHelper::GetSocioById(prestamo->IdSocio->IdSocio, Socios);

            socio->DevolverEjemplar(prestamo->IdEjemplar);
            libro->IngresarEjemplar(prestamo->IdEjemplar);
            PrestamosVigentes.remove(prestamo);
            Devoluciones.push_back(prestamo);
            DataHelper::SaveDevoluciones(Devoluciones);
            DataHelper::SavePrestamos(PrestamosVigentes);
            volverAlMenu = true;
            cout << endl << "Se ha registrado la devolucion"<<endl;
            system("PAUSE");
        }
        else {
            cout << "\n El prestamo ingresado no existe, desea volver a intentarlo?\n";
            cin >> siNo;
            if (siNo == 'n' || siNo == 'N') {
                volverAlMenu = true;
            }
        }

    }
}
void MenuSocio(list<Socio*> Socios){
    int menuOpt;
    do {
        OptionsSocio();
        cin >> menuOpt;
        switch (menuOpt) {
        case 1 : AgregarSocio();
            break;
        case 2: EliminarSocio();
            break;
        case 3: MostrarEjemplaresRetirados();
            break;
        }
    } while (menuOpt != 0);
}
void MenuLibro(list<Libro*> Libros) {
    int menuOpt;
    do {
        OptionsLibro();
        cin >> menuOpt;
        switch (menuOpt) {
        case 1: AgregarLibro();
            break;
        case 2: EliminarLibro();
            break;
        case 3: MostrarEjemplaresLibro();
            break;
        }
    } while (menuOpt != 0);
}
void MenuEjemplar(list<Ejemplar*> Ejemplares) {
    int menuOpt;
    do {
        OptionsEjemplar();
        cin >> menuOpt;
        if (menuOpt == 1)
            AgregarEjemplar();
    } while (menuOpt != 0);
}



int main()
{
    Ejemplares = EjemplarDataHelper::GetEjemplares();
    Libros = LibroDataHelper::GetLibros();
    Socios = SocioDataHelper::GetSocios();
    for (Libro* libro : Libros) {
        LibroDataHelper::SetEjemplares(libro, Ejemplares);
    }
    PrestamosVigentes = DataHelper::GetPrestamosVigentes(Ejemplares, Socios);
    Devoluciones = DataHelper::GetDevoluciones(Ejemplares, Socios);
    int mainMenuOpt;
    do {
        MainMenu();
        cin >> mainMenuOpt;
        switch (mainMenuOpt)
        {
        case 1: MenuSocio(Socios);
                break;
        case 2: MenuLibro(Libros);
            break;
        case 3: MenuEjemplar(Ejemplares);
            break;
        case 4: AgregarPrestamo();
                break;
        case 5: FinalizarPrestamo();
                break;
        case 6: VerPrestamos();
                break;
        case 7: VerDevoluciones();
                break;
        case 8: VerSocios();
            break;
        case 9: VerLibros();
            break;
        }

    } while (mainMenuOpt != 0);
    EjemplarDataHelper::SaveEjemplares(Ejemplares);
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
