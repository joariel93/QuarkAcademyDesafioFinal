#include "SocioDataHelper.h"

Socio* SocioDataHelper::GetSocioById(int idSoc, list<Socio*> Socios)
{
    Socio* retorno = nullptr;
    for (Socio* soc : Socios) {
        if (soc->IdSocio == idSoc) {
            retorno = soc;
            break;
        }
    }
    return retorno;
}

list<Socio*> SocioDataHelper::GetSocios()
{
    list<Socio*> retorno;
    ifstream input_file("socios.csv");
    string line;
    while (std::getline(input_file, line)) {
        vector<string> fields;
        stringstream ss(line);
        string field;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        if (fields.size() == 5)
            retorno.push_back(new SocioVip(stoi(fields[0]), fields[1], fields[2], fields[3] == "true" ? true : false, stof(fields[4])));
        else
            retorno.push_back(new Socio(stoi(fields[0]), fields[1], fields[2], fields[3] == "true" ? true : false));

    }
    return retorno;
}

void SocioDataHelper::SaveSocios(list<Socio*> socios)
{
    ofstream output_file("socios.csv");
    for (const auto& socio : socios) {
        output_file << socio->GetAllData() << endl;
    }
}

string SocioDataHelper::GetEncabezadoSocios()
{
    string retorno = "";
    retorno = "ID\t|NOMBRE\t\t|APELLIDO\n";

    ifstream input_file("socios.csv");
    string line;
    while (std::getline(input_file, line)) {
        vector<string> fields;
        stringstream ss(line);
        string field;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }

        retorno += fields[0] + "\t" + fields[1] + "\t\t" + fields[2] + "\n";
    }

    return retorno;
}

string SocioDataHelper::GetEncabezadoEjemplares(Socio* socio)
{
    string retorno = "";
    if (socio->EjemplaresRetirados.size()>0) {
        retorno += "Ejemplares retirados por el socio: " + socio->NombreCompleto()+"\n";
        retorno += "ID\t|UBICACION\n";
        for (Ejemplar* ejemplar : socio->EjemplaresRetirados) {
            retorno += to_string(ejemplar->IdEdicion) + "\t|" + ejemplar->Ubicacion+"\n";
        }
    }
    else {
        retorno = "El socio no posee ejemplares";
    }
    return retorno;
}

