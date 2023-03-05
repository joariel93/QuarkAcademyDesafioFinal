#include "Ejemplar.h"

string Ejemplar::GetAllData()
{
    string disp = this->disponible ? "1" : "0";
    return to_string(this->CodISBNLibro)+","+to_string(this->IdEdicion)+","+this->Ubicacion+","+disp;
}

Ejemplar::Ejemplar(int codLibro, int id, string ubicacion)
{
    this->CodISBNLibro = codLibro;
    this->IdEdicion = id;
    this->Ubicacion = ubicacion;
    this->disponible = true;
}

Ejemplar::Ejemplar(int codLibro, int id, string ubicacion, bool disponible):Ejemplar(codLibro, id, ubicacion)
{
    this->disponible = disponible;
}

Ejemplar::~Ejemplar()
{
    cout.write("Destructor ejm", 14);
}

