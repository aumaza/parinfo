#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipment.h"

#include <iostream>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Administración de Parque Informático");

        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        Equipment* oneEquipment = new Equipment();
        // VARIABLE DE VALIDACION
        int conn = oneEquipment->connection(db);

        if(conn == 1){
            ui->mensaje_database_ok->setText("<font color='green'>DATA BASE CONNECTION OK!!</font>");
            qDebug() << "Connected to the database!";
        }
        if(conn == 0){
            ui->mensaje_database_ok->setText("<font color='red'>Failed to connect to the database!</font>");
            qDebug() << "Failed to connect to the database!";
        }


}

MainWindow::~MainWindow()
{
    delete ui;
}

// ================================================================================================================= //
// BUTTONS
// ================================================================================================================= //


// Button Guardar registro de Equipo

void MainWindow::on_btn_guardar_clicked(){

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    // SE INSTANCIA UN OBJETO EQUIPO
    Equipment* oneEquipment = new Equipment();

    // VARIABLE DE VALIDACION
    int aux = -1;
    int conn = -1;

    // SE CAPTURAN LAS VARIABLES
    QString nombre = ui->nombre_apellido->text();
    QString patrimonio = ui->patrimonio->text();
    QString ip = ui->ip->text();
    QString gate = ui->gateaway->text();
    QString submask = ui->submask->text();
    QString dns = ui->dns->text();
    QString nro_oficina = ui->nro_oficina->text();
    QString usuario = ui->usuario->text();
    QString os = ui->sistema_operativo->currentText();
    QString periscopio = ui->periscopio->text();
    QString puesto = ui->puesto_ubicacion->text();
    QString mac = ui->mac_address->text();

    QMessageBox msg;
    msg.setWindowTitle("Ingreso de Equipo");
    msg.setIcon(QMessageBox::Information);

    if((nombre == "") ||
            (patrimonio == "") ||
                (ip == "") ||
                    (gate == "") ||
                        (submask == "") ||
                            (dns == "") ||
                                (nro_oficina == "") ||
                                    (usuario == "") ||
                                        (os == "") ||
                                            (periscopio == "") ||
                                                (puesto == "") ||
                                                    (mac == "")){

        msg.setText("Atención!! Hay Campos sin Completar!");
        msg.exec();
        qDebug() << "Atención!! Hay Campos sin completar en el Formulario alta de Equipo!";
    }else{
            conn = oneEquipment->connection(db);
            aux = oneEquipment->saveEquipment(conn,nombre,patrimonio,ip,gate,submask,dns,nro_oficina,usuario,os,periscopio,puesto,mac);

            if(aux == 1){
                msg.setText("Atención!! El Registro de Equipo ha sido guardado con Exito!!");
                msg.exec();
                qDebug() << "Atención!! El Registro de Equipo ha sido guardado con Exito!!";
            }
            if(aux == 0){
                msg.setText("Atención!! Hubo un problema al intentar guardar el registro de equipo!");
                msg.exec();
                qDebug() << "Atención!! Hubo un problema al intentar guardar el registro de equipo!";
            }
            if(aux == 2){
                msg.setText("Atención!! No hay conexion a la base de datos!");
                msg.exec();
                qDebug() << "Atención!! No hay conexion a la base de datos!";
            }

    }
}

