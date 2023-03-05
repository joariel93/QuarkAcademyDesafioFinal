#include "EjemplarDataHelper.h"

list<Ejemplar*> EjemplarDataHelper::GetEjemplaresByLibroId(int idLibro)
{
	list<Ejemplar*> retorno;
    ifstream input_file("ejemplares.csv");
    string line;
    while (std::getline(input_file, line)) {
        vector<string> fields;
        stringstream ss(line);
        string field;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        if (stoi(fields[0]) == idLibro) {
            bool disp = fields[3] == "1" ? true : false;
            if (disp)
                retorno.push_back(new Ejemplar(stoi(fields[0]), stoi(fields[1]), fields[2]));
        }
    }

	return retorno;
}

void EjemplarDataHelper::SaveEjemplares(list<Ejemplar*> ejemplares)
{
    ofstream output_file("ejemplares.csv");
    for (const auto& ejemplar : ejemplares) {
        output_file << ejemplar->GetAllData() << endl;
    }
}

list<Ejemplar*> EjemplarDataHelper::GetEjemplares()
{
    list<Ejemplar*> retorno;
    ifstream input_file("ejemplares.csv");
    string line;
    while (std::getline(input_file, line)) {
        vector<string> fields;
        stringstream ss(line);
        string field;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        bool disp = fields[3] == "1" ? true : false;
        retorno.push_back(new Ejemplar(stoi(fields[0]), stoi(fields[1]), fields[2],disp));
    }
    return retorno;
}
