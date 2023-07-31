#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QTableWidgetItem>
#include <QCloseEvent>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void cleanFormEquipment();
    QTableWidgetItem* myItem(QString value);

    // EQUIPAMIENTO
    void listarEquipamiento();
    void fillFormEquipamiento(QString index);


private slots:
    void on_btn_guardar_clicked();

    void on_table_equipamiento_activated(const QModelIndex &index);

    void on_btn_editar_clicked();

    void on_btn_eliminar_clicked();

private:
    Ui::MainWindow *ui;
    //QSqlDatabase *db;

};
#endif // MAINWINDOW_H
