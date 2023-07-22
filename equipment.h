#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QString>


class Equipment
{
private:
    QString nombre_apellido;
    QString patrimonio;
    QString ip;
    QString gateaway;
    QString submask;
    QString dns;
    QString nro_oficina;
    QString login_usuario;
    QString sistema_operativo;
    QString periscopio;
    QString puesto_ubicacion;
    QString mac_address;

public:
    Equipment();
    ~Equipment();
};

#endif // EQUIPMENT_H
