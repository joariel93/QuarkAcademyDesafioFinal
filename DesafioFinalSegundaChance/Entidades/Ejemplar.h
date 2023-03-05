#pragma once
#include <string>
#include <iostream>

using namespace std;

class Ejemplar
{
public:
	int CodISBNLibro;
	int IdEdicion;
	string Ubicacion;
	bool disponible;

	string GetAllData();

	Ejemplar(int codLibro, int id, string ubicacion);
	Ejemplar(int codLibro, int id, string ubicacion, bool disponible);
	~Ejemplar();
};

