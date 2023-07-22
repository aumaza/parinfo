#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QSharedMemory>
#include <QDebug>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSharedMemory shared("62d60669-bb94-4a94-88bb-b964890a7e04");
    if( !shared.create( 512, QSharedMemory::ReadWrite) ){
        QMessageBox msg;
        msg.setWindowTitle("Administración de Parque Informático");
        msg.setIcon(QMessageBox::Warning);
        msg.setText("Sólo se permite una instancia de la aplicación...");
        msg.exec();
        qDebug() << "Can't start more than one instance of the application.";
        exit(0);
    }else {

        a.setStyle("fusion");
        QTranslator translator;
        const QStringList uiLanguages = QLocale::system().uiLanguages();

        for (const QString &locale : uiLanguages) {
            const QString baseName = "parinfo_" + QLocale(locale).name();

            if (translator.load(":/i18n/" + baseName)) {
                a.installTranslator(&translator);
                break;
        }
    }

    MainWindow w;
    w.show();
    return a.exec();

    }
}
