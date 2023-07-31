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
#include <QTimer>

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

        // CARGA DE TABLAS EN EL INICIO
        listarEquipamiento();
        ui->btn_editar->setEnabled(false);
        ui->btn_eliminar->setEnabled(false);


}

MainWindow::~MainWindow()
{
    delete ui;
}


// ================================================================================================================= //
// METHODS
// ================================================================================================================= //

void MainWindow::cleanFormEquipment(){

    if(ui->equip_id->text() != ""){
        ui->equip_id->clear();
    }
    ui->nombre_apellido->clear();
    ui->patrimonio->clear();
    ui->ip->clear();
    ui->gateaway->clear();
    ui->submask->clear();
    ui->dns->clear();
    ui->nro_oficina->clear();
    ui->usuario->clear();
    ui->periscopio->clear();
    ui->puesto_ubicacion->clear();
    ui->mac_address->clear();
    ui->sistema_operativo->setCurrentIndex(0);
    ui->nombre_apellido->setFocus();
}


QTableWidgetItem *MainWindow::myItem(QString value){

    auto item = new QTableWidgetItem(value);
    item->setTextAlignment(Qt::AlignCenter);
    return item;
}

void MainWindow::listarEquipamiento(){

        QString consulta;
        consulta.append("select * from equipamiento");
        QSqlQuery consultar;
        consultar.prepare(consulta);


        if(consultar.exec()){
          qDebug() << "All registers are shown Succesfully";
        }else{
            qDebug() << "ERROR! Impossible show table registers...";
            qDebug() << "ERROR!"<< consultar.lastError();
        }

        int count = 0;
        int fila = 0;

        ui->table_equipamiento->setColumnHidden(0,true);
        ui->table_equipamiento->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Stretch);
        ui->table_equipamiento->setRowCount(0);

        while(consultar.next()){
             ui->table_equipamiento->insertRow(fila);

                for(int i = 0; i < 13; i++){
                    ui->table_equipamiento->setItem(fila,i,myItem(consultar.value(i).toByteArray().constData()));
                }
                count++;
                fila++;
          }
        QString contador = QString::number(count);
        if(count != 0){
            ui->mensaje->setText("Hay " + contador + " Registro/s");
        }else if(count == 0){
            ui->mensaje->setText("Atención!!...Aún no hay registros en la Tabla Equipamiento!");
        }

}

void MainWindow::fillFormEquipamiento(QString index){

        // SE INICIALA EL QUERY
        QSqlQuery query;
        query.prepare("SELECT * from equipamiento where id = '"+index+"'");



        if(index == ""){
            QMessageBox msgBoxDpFormSearch;
            msgBoxDpFormSearch.setWindowTitle("Equipamiento - Llenar Formulario");
            msgBoxDpFormSearch.setIcon(QMessageBox::Warning);
            msgBoxDpFormSearch.setText("Debe Seleccionar un Registro");
            msgBoxDpFormSearch.exec();
        }else{

                if(query.exec()){


                        while(query.next()){

                                    ui->equip_id->setText(query.value(0).toString());
                                    ui->nombre_apellido->setText(query.value(1).toString());
                                    ui->patrimonio->setText(query.value(2).toString());
                                    ui->ip->setText(query.value(3).toString());
                                    ui->gateaway->setText(query.value(4).toString());
                                    ui->submask->setText(query.value(5).toString());
                                    ui->dns->setText(query.value(6).toString());
                                    ui->nro_oficina->setText(query.value(7).toString());
                                    ui->usuario->setText(query.value(8).toString());
                                    ui->sistema_operativo->setCurrentIndex(ui->sistema_operativo->findText(query.value(9).toString()));
                                    ui->periscopio->setText(query.value(10).toString());
                                    ui->puesto_ubicacion->setText(query.value(11).toString());
                                    ui->mac_address->setText(query.value(12).toString());

                            } // FIN DEL WHILE

                        QTimer::singleShot(0000,[&](){ui->mensaje->setText("Registro Cargado Correctamente!");});
                        QTimer::singleShot(4000,ui->mensaje, &QLabel::clear);
                        ui->btn_guardar->setEnabled(false);
                        ui->btn_editar->setEnabled(true);
                        ui->btn_eliminar->setEnabled(true);
                        qDebug()<<"Registo Cargado Correctamente!!";


                }else{
                    QTimer::singleShot(0000,[&](){ui->mensaje->setText("ERROR!!...No se pudo realizar la consulta");});
                    QTimer::singleShot(4000,ui->mensaje, &QLabel::clear);
                    qDebug() << "ERROR!!...No se pudo realizar la consulta" << query.lastError();
                }
        }
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
                cleanFormEquipment();
                listarEquipamiento();
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
            if(aux == 3){
                msg.setText("Atención!! Ya Existe registro on la IP ingresada. Por favor modifique la IP!");
                msg.exec();
                qDebug() << "Atención!! Ya Existe registro on la IP ingresada. Por favor modifique la IP!";
            }

    }
}


void MainWindow::on_table_equipamiento_activated(const QModelIndex &index){

    // se captura el dato desde la tabla
    qDebug() << "Column Clicked: " << index.data().toString();
    QString id = ui->table_equipamiento->model()->data(ui->table_equipamiento->selectionModel()->selectedRows()[0]).toString();
    qDebug() << "Regestry ID: " << id;
    fillFormEquipamiento(id);
}


void MainWindow::on_btn_editar_clicked(){

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    // SE INSTANCIA UN OBJETO EQUIPO
    Equipment* oneEquipment = new Equipment();

    // VARIABLE DE VALIDACION
    int aux = -1;
    int conn = -1;

    // SE CAPTURAN LOS DATOS
    QString id = ui->equip_id->text();
    QString nombre = oneEquipment->setNombreApellido(ui->nombre_apellido->text());
    QString patrimonio = oneEquipment->setpatrimonio(ui->patrimonio->text());
    QString ip = oneEquipment->setIp(ui->ip->text());
    QString gateaway = oneEquipment->setGateaway(ui->gateaway->text());
    QString submask = oneEquipment->setSubmask(ui->submask->text());
    QString dns = oneEquipment->setDns(ui->dns->text());
    QString nro_oficina = oneEquipment->setNroOficina(ui->nro_oficina->text());
    QString login_usuario = oneEquipment->setLoginUsuario(ui->usuario->text());
    QString sistema_operativo = oneEquipment->setSistemaOperativo(ui->sistema_operativo->currentText());
    QString periscopio = oneEquipment->setPeriscopio(ui->periscopio->text());
    QString puesto_ubicacion = oneEquipment->setPuesto(ui->puesto_ubicacion->text());
    QString mac_address = oneEquipment->setMacAddress(ui->mac_address->text());

    QMessageBox msg;
    msg.setWindowTitle("Actualización de Registro de Equipo");
    msg.setIcon(QMessageBox::Information);

    // SE VALIDA QUE NO VENGAN NULL LOS DATOS
    if((id == "") ||
            (nombre == "") ||
                (patrimonio == "") ||
                    (ip == "") ||
                        (gateaway == "") ||
                            (submask == "") ||
                                (dns == "") ||
                                    (nro_oficina == "") ||
                                        (login_usuario == "") ||
                                            (sistema_operativo == "") ||
                                                (periscopio == "") ||
                                                    (puesto_ubicacion == "") ||
                                                        (mac_address == "")){

            msg.setText("Atención!! Hay campos sin completar!!");
            msg.exec();
            qDebug() << "Atención!! Hay campos sin completar cuando intentó actualizar el registro de un equipo!!";
    }else{

        conn = oneEquipment->connection(db);
        aux = oneEquipment->updateEquipment(conn,id,nombre,patrimonio,ip,gateaway,submask,dns,nro_oficina,login_usuario,sistema_operativo,periscopio,puesto_ubicacion,mac_address);

        if(aux == 1){
            msg.setText("Atención!! El Registro de Equipo ha sido actualizado con Exito!!");
            msg.exec();
            qDebug() << "Atención!! El Registro de Equipo ha sido actualizado con Exito!!";
            cleanFormEquipment();
            listarEquipamiento();
            ui->btn_editar->setEnabled(false);
            ui->btn_eliminar->setEnabled(false);
            ui->btn_guardar->setEnabled(true);
        }
        if(aux == 0){
            msg.setText("Atención!! Hubo un problema al intentar actualizar el registro de equipo!");
            msg.exec();
            qDebug() << "Atención!! Hubo un problema al intentar actualizar el registro de equipo!";
        }
        if(aux == 2){
            msg.setText("Atención!! No hay conexion a la base de datos!");
            msg.exec();
            qDebug() << "Atención!! No hay conexion a la base de datos!";
        }

    }


}


void MainWindow::on_btn_eliminar_clicked(){

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    // SE CREA EL OJETO EQUIPO
    Equipment* oneEquip = new Equipment();

    // VARIABLES DE VERIFICACION
    int conn = -1;
    int aux = -1;

    // SE CAPTURA EL ID
    QString id = ui->equip_id->text();

    QMessageBox msg;
    msg.setWindowTitle("Eliminar Registro de Equipo");
    msg.setIcon(QMessageBox::Warning);


    if(id == ""){
        msg.setText("Atención!! Debe seleccionar un registro!");
        msg.exec();
        qDebug() << "Atención!! Debe seleccionar un registro!!";
    }else{

        msg.setText("Ateción - Eliminará un registro definitivamente. Está Seguro?");
        msg.addButton(QMessageBox::Ok);
        msg.addButton(QMessageBox::Cancel);
        int resp = msg.exec();

        if(resp == QMessageBox::Ok){

            conn = oneEquip->connection(db);
            aux = oneEquip->deleteEquipment(conn,id);

            if(aux == 1){
                msg.setText("Atención!! El Registro de Equipo ha sido eliminado Correctamente!");
                msg.exec();
                cleanFormEquipment();
                listarEquipamiento();
                ui->btn_editar->setEnabled(false);
                ui->btn_eliminar->setEnabled(false);
                ui->btn_guardar->setEnabled(true);
            }
            if(aux == 0){
                msg.setText("Atención!! Ha ocurrido un error al intentar eliminar el registro de Equipo!");
                msg.exec();
            }
            if(aux == 2){
                msg.setText("Atención!! No hay conexión con la base de datos!");
                msg.exec();
            }
        }
        if(resp == QMessageBox::Cancel){

            msg.setText("Atención!! Ha decidido no elimiar el registro!");
            msg.exec();
            cleanFormEquipment();
            ui->btn_guardar->setEnabled(true);
            ui->btn_editar->setEnabled(false);
            ui->btn_eliminar->setEnabled(false);

        }
    }
}

