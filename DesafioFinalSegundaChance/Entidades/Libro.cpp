#include "Libro.h"


Libro::Libro(int id, string nombre, string autor)
{
	this->CodISBN = id;
	this->Nombre = nombre;
	this->Autor = autor;
}

void Libro::AgregarEjemplar(Ejemplar* ejemplar)
{
	if (ejemplar != nullptr)
		this->Ejemplares.push_back(ejemplar);
}

bool Libro::HayEjemplares()
{
	return this->Ejemplares.size() > 0;
}

Ejemplar* Libro::PrestarEjemplar()
{
	Ejemplar* retorno = this->Ejemplares.size()>0? this->Ejemplares.front():nullptr;
	if (retorno != nullptr) {
		retorno->disponible = false;
		this->Ejemplares.pop_front();
	}
	return retorno;
}

void Libro::IngresarEjemplar(Ejemplar* ejemplar)
{
	this->Ejemplares.push_back(ejemplar);
}

string Libro::GetAllData()
{
	return to_string(this->CodISBN)+","+this->Nombre+","+this->Autor;
}

Libro::~Libro()
{
	cout.write("Destructor lib", 14);
}

