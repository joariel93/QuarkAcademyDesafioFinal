#include "Validador.h"


Socio* Validador::ValidarSocio(int idSoc, list<Socio*>Socios)
{    
    return SocioDataHelper::GetSocioById(idSoc, Socios);
}

Libro* Validador::ValidarLibro(int idLibro, list<Libro*> Libros)
{
    return LibroDataHelper::GetLibroById(idLibro, Libros);
}

bool Validador::ValidarStringConNombre(string text)
{
    bool retorno = ValidarStringVacio(text);
    if (retorno) {
        retorno = !any_of(text.begin(), text.end(), [](char c) { return isdigit(c); });
    }
    return retorno;
}

bool Validador::ValidarStringVacio(string text)
{
    return text==""||text==" "||text=="\n" || text=="\t" ? false : true;
}

