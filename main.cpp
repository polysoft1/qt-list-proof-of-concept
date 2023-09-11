#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Q_INIT_RESOURCE(icons);
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    MainWindow w(&a, "Myself");
    w.setGeometry(1000, 1000, 500, 500);
    w.show();
    return a.exec();
}
