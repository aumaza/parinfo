#include "mainwindow.h"
#include "ui_mainwindow.h"

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

        // Set the connection parameters
        db.setHostName("slackzone.ddns.net"); // Set your host name
        db.setDatabaseName("parinfo"); // Set your database name
        db.setUserName("root"); // Set your username
        db.setPassword("slack142"); // Set your password

        // Try to open the connection
        if (db.open()) {
            qDebug() << "Connected to the database!";
            // Perform your database operations here
            db.close();
        } else {
            qDebug() << "Failed to connect to the database!";
        }
}

MainWindow::~MainWindow()
{
    delete ui;
}

