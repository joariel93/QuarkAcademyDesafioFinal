#include "Socio.h"

Socio::Socio(int id, string nombre, string apellido, bool vip)
{
	this->IdSocio = id;
	this->Nombre = nombre;
	this->Apellido = apellido;
	this->EsVip = vip;
	this->MaxEjemplares = vip ? 3 : 1;

}

bool Socio::PuedeRetirar()
{
	return this->MaxEjemplares > (int) this->EjemplaresRetirados.size();
}

void Socio::RetirarEjemplar(Ejemplar* ejemplar)
{
	this->EjemplaresRetirados.push_back(ejemplar);
}

void Socio::DevolverEjemplar(Ejemplar* idEj)
{
	if (this->EjemplaresRetirados.size() == 1) {
		this->EjemplaresRetirados.clear();
	}
	else if (this->EjemplaresRetirados.size() > 0) {
		this->EjemplaresRetirados.remove(idEj);

	}
		
}

string Socio::NombreCompleto()
{
	return this->Nombre+" "+this->Apellido;
}

string Socio::GetAllData()
{
	string retorno = to_string(this->IdSocio) + "," + this->Nombre + "," + this->Apellido + ",";
	string vip = this->EsVip?"true":"false";
	return retorno + vip;
}

Socio::~Socio()
{
	cout.write("Destructor soc", 14);
}


