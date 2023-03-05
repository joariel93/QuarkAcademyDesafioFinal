#pragma once
#include "../Entidades/SocioVip.h"
#include "../Entidades/Libro.h"
#include "../Entidades/Prestamo.h"
#include "SocioDataHelper.h"
#include "LibroDataHelper.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
static class DataHelper
{
public:
	
	
	static list<Prestamo*> GetPrestamosVigentes(list<Ejemplar*> Ejemplares, list<Socio*> Socios);
	static list<Prestamo*> GetDevoluciones(list<Ejemplar*> Ejemplares, list<Socio*> Socios);
	static void SaveData(list<Socio*>socios, list<Libro*>libros, list<Prestamo*>prestamos, list<Prestamo*>devoluciones);
	
	
	static void SavePrestamos(list<Prestamo*> prestamos);
	static void SaveDevoluciones(list<Prestamo*> devoluciones);

	
	
	static Prestamo* GetPrestamoById(int idPrestamo, list<Prestamo*> Prestamos);
	static Ejemplar* GetEjemplarById(int idEjemplar);

	
	
	static string GetEncabezadoPrestamosVigentes(list<Prestamo*>prestamos, list<Libro*>Libros);
	static string GetEncabezadoPrestamosFinalizados(list<Prestamo*>devoluciones, list<Libro*>Libros);

};

