#pragma once
#include <list>
#include <string>
#include <iostream>
#include "Ejemplar.h"

using namespace std;
class Libro
{
public:
	int CodISBN;
	string Nombre;
	string Autor;
	list<Ejemplar*> Ejemplares;

	Libro(int id, string nombre, string autor);
	void AgregarEjemplar(Ejemplar* ejemplar);
	bool HayEjemplares();
	Ejemplar* PrestarEjemplar();
	void IngresarEjemplar(Ejemplar* ejemplar);
	string GetAllData();
	~Libro();
};

