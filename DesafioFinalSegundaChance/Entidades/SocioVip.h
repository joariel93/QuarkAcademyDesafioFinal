#pragma once
#include "Socio.h"
class SocioVip :
    public Socio
{
public:
    float CuotaMens;

    SocioVip(int id, string nombre, string apellido, bool vip, float cuota);
    string GetAllData() override;

    ~SocioVip();
};

