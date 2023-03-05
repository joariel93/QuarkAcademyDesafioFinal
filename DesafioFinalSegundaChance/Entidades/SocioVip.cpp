#include "SocioVip.h"

SocioVip::SocioVip(int id, string nombre, string apellido, bool vip, float cuota):Socio(id, nombre, apellido, true)
{
	this->CuotaMens = cuota;
}

string SocioVip::GetAllData()
{
	string retorno = Socio::GetAllData();
	return retorno +","+ to_string(this->CuotaMens);
}

SocioVip::~SocioVip()
{
	cout.write("Destructor sov", 14);
}
