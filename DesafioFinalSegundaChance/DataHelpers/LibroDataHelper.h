#pragma once
#include "../Entidades/Libro.h"
#include "EjemplarDataHelper.h"
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


static class LibroDataHelper
{
public:
	static list<Libro*> GetLibros();
	static void SaveLibros(list<Libro*> libros);
	static Libro* GetLibroById(int idLibro, list<Libro*>Libros);
	static string GetEncabezadoLibros();
	static void SetEjemplares(Libro* libro, list<Ejemplar*> ejemplares);
	static string GetNombreLibro(Ejemplar* ejemplar, list<Libro*>Libros);
	static string GetEncabezadoEjemplares(Libro* libro);
};
