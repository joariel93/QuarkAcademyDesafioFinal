#include "LibroDataHelper.h"

list<Libro*> LibroDataHelper::GetLibros()
{
    list<Libro*> retorno;
    ifstream input_file("libros.csv");
    string line;
    while (std::getline(input_file, line)) {
        vector<string> fields;
        stringstream ss(line);
        string field;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        retorno.push_back(new Libro(stoi(fields[0]), fields[1], fields[2]));
    }
    return retorno;
}

void LibroDataHelper::SaveLibros(list<Libro*> libros)
{
    ofstream output_file("libros.csv");
    for (const auto& libro : libros) {
        output_file << libro->GetAllData() << endl;
    }
}

Libro* LibroDataHelper::GetLibroById(int idLibro, list<Libro*> Libros)
{
    Libro* retorno = nullptr;
    for (Libro* lib : Libros) {
        if (lib->CodISBN == idLibro) {
            retorno = lib;
            break;
        }
    }
    return retorno;
}

string LibroDataHelper::GetEncabezadoLibros()
{
    string retorno = "";
    retorno = "ID\t|NOMBRE\t\t\t\t\t|AUTOR\n";
    ifstream input_file("libros.csv");
    string line;
    while (std::getline(input_file, line)) {
        vector<string> fields;
        stringstream ss(line);
        string field;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        retorno += fields[0] + "\t" + fields[1] + "\t\t\t" + fields[2] + "\n";
    }
    return retorno;
}

void LibroDataHelper::SetEjemplares(Libro* libro, list<Ejemplar*> ejemplares)
{
    for (Ejemplar* ejemplar : ejemplares) {
        if (ejemplar->disponible && ejemplar->CodISBNLibro == libro->CodISBN)
            libro->AgregarEjemplar(ejemplar);
    }    
}

string LibroDataHelper::GetNombreLibro(Ejemplar* ejemplar, list<Libro*> Libros)
{
    string retorno = "";
    for (Libro* libro : Libros) {
        if (libro->CodISBN == ejemplar->CodISBNLibro) {
            retorno = libro->Nombre;
            break;
        }
    }
    return retorno;
}

string LibroDataHelper::GetEncabezadoEjemplares(Libro* libro)
{
    string retorno = "";
    if (libro->HayEjemplares()) {
        retorno += "Ejemplares disponibles del libro: " + libro->Nombre + "\n";
        retorno += "ID\t|UBICACION\n";
        for (Ejemplar* ejemplar : libro->Ejemplares) {
            retorno += to_string(ejemplar->IdEdicion) + "\t|" + ejemplar->Ubicacion+"\n";
        }
    }
    else {
        retorno = "El libro no posee ejemplares disponibles";
    }
    return retorno;
}
