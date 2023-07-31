#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QString>
#include <QSqlDatabase>


class Equipment{

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
    //QSqlDatabase *db;

public:
    Equipment(); // DESTRUCTOR DESPARAMETRIZADO
    ~Equipment(); // DESTRUCTOR


    // SETTERS
    QString setNombreApellido(QString nombre);
    QString setpatrimonio(QString patrimonio);
    QString setIp(QString ip);
    QString setGateaway(QString gateaway);
    QString setSubmask(QString submask);
    QString setDns(QString dns);
    QString setNroOficina(QString nro_of);
    QString setLoginUsuario(QString usuario);
    QString setSistemaOperativo(QString os);
    QString setPeriscopio(QString peris);
    QString setPuesto(QString puesto);
    QString setMacAddress(QString mac);

    // GETTERS
    QString getNombreApellido();
    QString getpatrimonio();
    QString getIp();
    QString getGateaway();
    QString getSubmask();
    QString getDns();
    QString getNroOficina();
    QString getLoginUsuario();
    QString getSistemaOperativo();
    QString getPeriscopio();
    QString getPuesto();
    QString getMacAddress();

    // METODOS
    int connection(QSqlDatabase db);
    int saveEquipment(int conn, QString nombre, QString pat, QString ip, QString gate, QString submask, QString dns, QString nro_oficina, QString usuario, QString os, QString periscopio, QString puesto, QString mac);
    int updateEquipment(int conn, QString id, QString nombre, QString pat, QString ip, QString gate, QString submask, QString dns, QString nro_oficina, QString usuario, QString os, QString periscopio, QString puesto, QString mac);
    int deleteEquipment(int conn, QString id);

};

#endif // EQUIPMENT_H
