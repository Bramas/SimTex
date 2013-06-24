#include "mainwindow.h"
#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Ultratools");
    QCoreApplication::setOrganizationDomain("ultratools.org");
    QCoreApplication::setApplicationName("TexSim");
    QSettings::setDefaultFormat(QSettings::IniFormat);

    MainWindow w;
    w.show();
    
    return a.exec();
}
