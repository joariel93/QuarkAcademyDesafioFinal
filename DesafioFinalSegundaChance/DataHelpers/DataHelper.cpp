#include "DataHelper.h"



list<Prestamo*> DataHelper::GetPrestamosVigentes(list<Ejemplar*> Ejemplares, list<Socio*> Socios)
{
    list<Prestamo*>retorno;
    ifstream input_file("prestamos.csv");
    string line;
    while (std::getline(input_file, line)) {
        vector<string> fields;
        stringstream ss(line);
        string field;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        Ejemplar* ej=nullptr;
        for (Ejemplar* eje : Ejemplares) {
            if (eje->IdEdicion == stoi(fields[2])) {
                ej = eje;
                break;
            }
        }
        Socio* soc = SocioDataHelper::GetSocioById(stoi(fields[1]), Socios);
        soc->RetirarEjemplar(ej);
        retorno.push_back(new Prestamo(stoi(fields[0]),soc,ej,fields[3], fields[4]));
    }
    return retorno;
}

list<Prestamo*> DataHelper::GetDevoluciones(list<Ejemplar*> Ejemplares, list<Socio*> Socios)
{
    list<Prestamo*>retorno;
    ifstream input_file("devoluciones.csv");
    string line;
    while (std::getline(input_file, line)) {
        vector<string> fields;
        stringstream ss(line);
        string field;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        Ejemplar* ej = nullptr;
        for (Ejemplar* eje : Ejemplares) {
            if (eje->IdEdicion == stoi(fields[2])) {
                ej = eje;
                break;
            }
        }
        Socio* soc = SocioDataHelper::GetSocioById(stoi(fields[1]), Socios);
        retorno.push_back(new Prestamo(stoi(fields[0]), soc, ej, fields[3], fields[4]));
    }
    return retorno;
}

void DataHelper::SaveData(list<Socio*> socios, list<Libro*> libros, list<Prestamo*> prestamos, list<Prestamo*> devoluciones)
{
    SavePrestamos(prestamos);
    SaveDevoluciones(devoluciones);
}

void DataHelper::SavePrestamos(list<Prestamo*> prestamos)
{
    ofstream output_file("prestamos.csv");
    for (const auto& prestamo : prestamos) {
        output_file << prestamo->GetAllData() << endl;
    }
}

void DataHelper::SaveDevoluciones(list<Prestamo*> devoluciones)
{
    ofstream output_file("devoluciones.csv");
    for (const auto& devolucion : devoluciones) {
        output_file << devolucion->GetAllData() << endl;
    }
}



Ejemplar* DataHelper::GetEjemplarById(int idEdicion)
{
    Ejemplar* retorno = nullptr;
    ifstream input_file("ejemplares.csv");
    string line;
    while (std::getline(input_file, line)) {
        vector<string> fields;
        stringstream ss(line);
        string field;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        if (stoi(fields[1]) == idEdicion)
            retorno = new Ejemplar(stoi(fields[0]), stoi(fields[1]), fields[2]);
    }
    return retorno;
}

Prestamo* DataHelper::GetPrestamoById(int idPrestamo, list<Prestamo*> Prestamos)
{
    Prestamo* retorno = nullptr;
    for (Prestamo* prest : Prestamos) {
        if (prest->idPrestamo == idPrestamo) {
            retorno = prest;
            break;
        }
    }
    return retorno;
}


string DataHelper::GetEncabezadoPrestamosVigentes(list<Prestamo*>prestamos, list<Libro*>Libros)
{
    string retorno = "";
    retorno = "ID\t|LIBRO\t\t\t\t|SOCIO\t\t|Fecha inicio\n";
    for (Prestamo* prestamo : prestamos) {
        if (prestamo!=nullptr) {
            retorno += to_string(prestamo->idPrestamo) + "\t" + LibroDataHelper::GetNombreLibro(prestamo->IdEjemplar,Libros)+"\t"+prestamo->IdSocio->NombreCompleto()+"\t"+prestamo->FormatDateTime(prestamo->FechaPrestamo)+"\n";

        }
    }
    return retorno;
}

string DataHelper::GetEncabezadoPrestamosFinalizados(list<Prestamo*>devoluciones, list<Libro*> Libros)
{
    string retorno = "";
    retorno = "ID\t|LIBRO\t\t\t\t|SOCIO\t\t|Fecha inicio\t\t|Fecha devolucion\n";
    for (Prestamo* dev : devoluciones) {
        auto aux = GetEjemplarById(dev->IdEjemplar->IdEdicion);
        retorno += to_string(dev->idPrestamo) + "\t" + LibroDataHelper::GetNombreLibro(dev->IdEjemplar,Libros) + "\t" + dev->IdSocio->NombreCompleto() + "\t" + dev->FormatDateTime(dev->FechaPrestamo) + "\t" + dev->FormatDateTime(dev->FechaDevolucion)+"\n";
    }

    return retorno;
}
