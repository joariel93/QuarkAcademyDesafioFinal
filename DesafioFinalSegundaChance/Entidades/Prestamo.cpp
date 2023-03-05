#include "Prestamo.h"

string Prestamo::GetAllData()
{
	ostringstream retorno;
	retorno << to_string(this->idPrestamo) << ","
		<< to_string(this->IdSocio->IdSocio) << ","
		<< to_string(this->IdEjemplar->IdEdicion) << ","
		<< FormatDateTime(this->FechaPrestamo) << ","
		<< FormatDateTime(this->FechaDevolucion);
	return retorno.str();
}

Prestamo::Prestamo(int idPrestamo, Socio* soc, Ejemplar* ej)
{
	this->idPrestamo = idPrestamo;
	this->IdEjemplar = ej;
	this->IdSocio = soc;
	this->FechaPrestamo = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	tm tmFechaDevolucion = { 0 };
	localtime_s(&tmFechaDevolucion, &FechaPrestamo); 
	tmFechaDevolucion.tm_mday += 5;
	FechaDevolucion = mktime(&tmFechaDevolucion);
}

Prestamo::Prestamo(int idPrestamo, Socio* soc, Ejemplar* ej,  string fechaIn, string fechaFin):Prestamo(idPrestamo, soc, ej)
{
	this->FechaPrestamo = ParseDateTime(fechaIn);
	this->FechaDevolucion = ParseDateTime(fechaFin);
}

Prestamo::~Prestamo()
{
	cout.write("Destructor pst", 14);
}

string Prestamo::FormatDateTime(time_t datetime)
{
	if (datetime == 0) {
		return "";
	}
	std::tm timeinfo;
	localtime_s(&timeinfo, &datetime);
	char buffer[80];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
	return buffer;
}

time_t Prestamo::ParseDateTime(const string& dateTimeStr)
{
	struct tm timeInfo = { 0 };
	timeInfo.tm_isdst = -1;
	int day, month, year, hour, minute, second;
	if (sscanf_s(dateTimeStr.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) == 6) {
		timeInfo.tm_mday = day;
		timeInfo.tm_mon = month - 1;
		timeInfo.tm_year = year - 1900;
		timeInfo.tm_hour = hour;
		timeInfo.tm_min = minute;
		timeInfo.tm_sec = second;
		return mktime(&timeInfo);
	}
	else {
		return 0;
	}
}
