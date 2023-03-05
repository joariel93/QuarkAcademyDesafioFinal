#pragma once
#include <string>
#include <list>
#include <iostream>
#include "Ejemplar.h"

using namespace std;
class Socio
{
public:
	int IdSocio;
	string Nombre;
	string Apellido;
	bool EsVip;
	list<Ejemplar*> EjemplaresRetirados;
	int MaxEjemplares;

	Socio(int id, string nombre, string apellido, bool vip = false);
	bool PuedeRetirar();
	void RetirarEjemplar(Ejemplar* ejemplar);
	void DevolverEjemplar(Ejemplar* idEj);
	string NombreCompleto();
	virtual string GetAllData();

	~Socio();

};

