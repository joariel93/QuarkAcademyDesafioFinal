#pragma once
#include "./Entidades/SocioVip.h"
#include "./Entidades/Libro.h"
#include "./DataHelpers/SocioDataHelper.h"
#include "./DataHelpers/LibroDataHelper.h"
#include <algorithm>
#include <cctype>
static class Validador
{
public:
	static Socio* ValidarSocio(int idSoc, list<Socio*> Socios);
	static Libro* ValidarLibro(int idLibro, list<Libro*> Libros);
	static bool ValidarStringConNombre(string text);
	static bool ValidarStringVacio(string text);
};

