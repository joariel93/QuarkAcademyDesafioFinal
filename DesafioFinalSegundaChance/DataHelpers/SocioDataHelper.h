#pragma once
#include "DataHelper.h"


static class SocioDataHelper 
{
public:
	static Socio* GetSocioById(int idSoc, list<Socio*> Socios);
	static list<Socio*> GetSocios();
	static void SaveSocios(list<Socio*> socios);
	static string GetEncabezadoSocios();
	static string GetEncabezadoEjemplares(Socio* socio);
};

