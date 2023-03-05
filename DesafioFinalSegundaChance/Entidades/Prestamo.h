#pragma once
#include "Ejemplar.h"
#include "Socio.h"
#include <memory>
#include <chrono>
#include <iomanip>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
class Prestamo
{
public:
	int idPrestamo;
	Ejemplar* IdEjemplar;
	Socio* IdSocio;
	time_t FechaPrestamo;
	time_t FechaDevolucion;

	string GetAllData();
	Prestamo(int idPrestamo, Socio* soc, Ejemplar* ej);
	Prestamo(int idPrestamo, Socio* soc, Ejemplar* ej,  string fechaIn, string fechaFin);
	~Prestamo();
	string FormatDateTime(time_t datetime);


private:
	time_t ParseDateTime(const string& datetimeStr);
};

