#include "equipment.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QString>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>

// ========================================================================================================================================= //
// CONTRUCTOR DESPARAMETRIZADO
// ========================================================================================================================================= //

Equipment::Equipment(){

    this->nombre_apellido = "";
    this->patrimonio = "";
    this->ip = "";
    this->gateaway = "";
    this->submask = "";
    this->dns = "";
    this->nro_oficina = "";
    this->login_usuario = "";
    this->sistema_operativo = "";
    this->periscopio = "";
    this->puesto_ubicacion = "";
    this->mac_address = "";

}



// ========================================================================================================================================= //
// DESTRUCTOR
// ========================================================================================================================================= //

Equipment::~Equipment(){

}

// ========================================================================================================================================= //
// SETTERS
// ========================================================================================================================================= //

QString Equipment::setNombreApellido(QString nombre){
    return this->nombre_apellido = nombre;
}

QString Equipment::setpatrimonio(QString patrimonio){
    return this->patrimonio = patrimonio;
}

QString Equipment::setIp(QString ip){
    return this->ip = ip;
}

QString Equipment::setGateaway(QString gateaway){
    return this->gateaway = gateaway;
}

QString Equipment::setSubmask(QString submask){
    return this->submask = submask;
}

QString Equipment::setDns(QString dns){
    return this->dns = dns;
}

QString Equipment::setNroOficina(QString nro_of){
    return this->nro_oficina = nro_of;
}

QString Equipment::setLoginUsuario(QString usuario){
    return this->login_usuario = usuario;
}

QString Equipment::setSistemaOperativo(QString os){
    return this->sistema_operativo = os;
}

QString Equipment::setPeriscopio(QString peris){
    return this->periscopio = peris;
}

QString Equipment::setPuesto(QString puesto){
    return this->puesto_ubicacion = puesto;
}

QString Equipment::setMacAddress(QString mac){
    return this->mac_address = mac;
}

// ========================================================================================================================================= //
// GETTERS
// ========================================================================================================================================= //

QString Equipment::getNombreApellido(){
    return this->nombre_apellido;
}

QString Equipment::getpatrimonio(){
    return this->patrimonio;
}

QString Equipment::getIp(){
    return this->ip;
}

QString Equipment::getGateaway(){
    return this->gateaway;
}

QString Equipment::getSubmask(){
    return this->submask;
}

QString Equipment::getDns(){
    return this->dns;
}

QString Equipment::getNroOficina(){
    return this->nro_oficina;
}

QString Equipment::getLoginUsuario(){
    return this->login_usuario;
}

QString Equipment::getSistemaOperativo(){
    return this->sistema_operativo;
}

QString Equipment::getPeriscopio(){
    return this->periscopio;
}

QString Equipment::getPuesto(){
    return this->puesto_ubicacion;
}

QString Equipment::getMacAddress(){
    return this->mac_address;
}



// ========================================================================================================================================= //
// METODOS
// ========================================================================================================================================= //

int Equipment::connection(QSqlDatabase db){

    // VARIABLE DE VALIDACION
    int aux = -1;

    //db = QSqlDatabase::addDatabase("QMYSQL");

    // Set the connection parameters
    db.setHostName("slackzone.ddns.net"); // Set your host name
    db.setDatabaseName("parinfo"); // Set your database name
    db.setUserName("root"); // Set your username
    db.setPassword("slack142"); // Set your password

    // Try to open the connection
    if (db.open()) {
        aux = 1;
    } else {
        aux = 0;
    }

    return aux;
}


int Equipment::saveEquipment(int conn,QString nombre, QString pat, QString ip, QString gate, QString submask, QString dns, QString nro_oficina, QString usuario, QString os, QString periscopio, QString puesto, QString mac){



    // VARIBLE DE VALIDACION
    int aux = -1;

    // SE CREA EL SQL
    QString sql;
    sql.append("INSERT INTO equipamiento ("
               "nombre_apellido,"
               "patrimonio,"
               "ip,"
               "gateaway,"
               "submask,"
               "dns,"
               "nro_oficina,"
               "login_usuario,"
               "sistema_operativo,"
               "periscopio,"
               "puesto_ubicacion,"
               "mac_address"
               ")"
               "VALUES ("
               "'"+this->setNombreApellido(nombre)+"',"
               "'"+this->setpatrimonio(pat)+"',"
               "'"+this->setIp(ip)+"',"
               "'"+this->setGateaway(gate)+"',"
               "'"+this->setSubmask(submask)+"',"
               "'"+this->setDns(dns)+"',"
               "'"+this->setNroOficina(nro_oficina)+"',"
               "'"+this->setLoginUsuario(usuario)+"',"
               "'"+this->setSistemaOperativo(os)+"',"
               "'"+this->setPeriscopio(periscopio)+"',"
               "'"+this->setPuesto(puesto)+"',"
               "'"+this->setMacAddress(mac)+"'"
               ");");

    // SE CREA EL SQL
    QSqlQuery query;
    query.prepare(sql);

    if(conn == 1){

        if(query.exec()){
            aux = 1;
            qDebug() << "MYSQL_QUERY: " << query.lastQuery();
        }else{
            aux = 0;
            qDebug() << "MYSQL_ERROR: " << query.lastError();
        }
     }else{
        aux = 2;
     }

    return aux;

}












































