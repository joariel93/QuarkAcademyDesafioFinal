#pragma once
#include "../Entidades/Ejemplar.h"
#include "DataHelper.h"

using namespace std;

static class EjemplarDataHelper
{
public:
	static list<Ejemplar*> GetEjemplaresByLibroId(int idLibro);
	static void SaveEjemplares(list<Ejemplar*> ejemplares);
	static list<Ejemplar*> GetEjemplares();
};

