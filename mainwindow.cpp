#include "mainwindow.h"

#include <QtQuickWidgets/QQuickWidget>
#include <QQmlContext>
#include <QVBoxLayout>
#include <QLabel>
#include "MyListModel.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    this->resize(500, 800);


    QVBoxLayout * layout = new QVBoxLayout();
    //layout->setSpacing(0);
    //layout->setMargin(0);
    this->setLayout(layout);
    // IMPORTANT to reduce resource usage:
    // https://forum.qt.io/topic/98806/own-thread-for-each-qquickwidget/4

    MyListModel * model = new MyListModel;
    QQuickWidget * quick = new QQuickWidget(this);
    quick->rootContext()->setContextProperty("MyModel",  QVariant::fromValue(model));
    //quick->setClearColor(Qt::transparent);
    this->layout()->addWidget(quick);
    quick->setResizeMode(QQuickWidget::SizeRootObjectToView);
    quick->setSource(QUrl::fromLocalFile("qml/Timeline.qml"));
    quick->show();
}

MainWindow::~MainWindow()
{


}

