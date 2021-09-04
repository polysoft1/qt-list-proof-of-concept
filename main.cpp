#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Q_INIT_RESOURCE(icons);
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    MainWindow w(&a);
    w.show();
    return a.exec();
}
