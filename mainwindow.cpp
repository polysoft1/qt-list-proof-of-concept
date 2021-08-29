#include "mainwindow.h"

#include <QtQuickWidgets/QQuickWidget>
#include <QQmlContext>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QQuickItem>
#include "MyListModel.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    this->resize(1000, 800);


    QHBoxLayout * mainLayout = new QHBoxLayout();
    QVBoxLayout * settingsLayout = new QVBoxLayout();
    //layout->setSpacing(0);
    //layout->setMargin(0);
    this->setLayout(mainLayout);
    // IMPORTANT to reduce resource usage:
    // https://forum.qt.io/topic/98806/own-thread-for-each-qquickwidget/4

    MyListModel * model = new MyListModel;
    quick = new QQuickWidget(this);
    quick->rootContext()->setContextProperty("MyModel",  QVariant::fromValue(model));
    //quick->setClearColor(Qt::transparent);
    mainLayout->addWidget(quick, 1);
    mainLayout->addLayout(settingsLayout, 1);
    settingsLayout->addWidget(getProfilePicOptionSettings());
    settingsLayout->addWidget(getSelfPicOptionSettings());
    settingsLayout->addWidget(getProfilePicSizeSetting());
    quick->setResizeMode(QQuickWidget::SizeRootObjectToView);
    quick->setSource(QUrl::fromLocalFile("qml/Timeline.qml"));
    quick->show();
}

QGroupBox *MainWindow::getProfilePicOptionSettings()
{
    QGroupBox *groupBox = new QGroupBox(tr("Profile Pic Location"));

    QRadioButton *radio1 = new QRadioButton(tr("Top"));
    QRadioButton *radio2 = new QRadioButton(tr("Bottom"));

    radio1->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    connect(radio1, &QRadioButton::toggled, this,
            &MainWindow::onProfilePicLocationClicked);
    return groupBox;
}

QGroupBox *MainWindow::getSelfPicOptionSettings()
{
    QGroupBox *groupBox = new QGroupBox(tr("Self profile pic"));

    QRadioButton *radio1 = new QRadioButton(tr("Show"));
    QRadioButton *radio2 = new QRadioButton(tr("Hide"));

    radio1->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    connect(radio1, &QRadioButton::toggled, this,
            &MainWindow::onShowSelfPicClicked);
    return groupBox;
}

QGroupBox* MainWindow::getProfilePicSizeSetting() {
    QGroupBox *groupBox = new QGroupBox(tr("Profile pic size"));

    QSlider * slider = new QSlider(Qt::Orientation::Horizontal);
    profilePicSizeLabel = new QLabel();

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(profilePicSizeLabel, 0);
    hbox->addWidget(slider, 1);
    //hbox->addStretch(1);
    groupBox->setLayout(hbox);

    connect(slider, &QSlider::valueChanged, this,
            &MainWindow::onProfilePicSizeChange);

    slider->setValue(50);
    return groupBox;
}

void MainWindow::onProfilePicLocationClicked( bool toggled) {
    quick->setSource(QUrl::fromLocalFile("qml/Timeline.qml"));
    quick->rootObject()->setProperty("profilePicTopAlign", toggled);
}
void MainWindow::onShowSelfPicClicked( bool toggled) {
    quick->setSource(QUrl::fromLocalFile("qml/Timeline.qml"));
    quick->rootObject()->setProperty("showSelfProfilePic", toggled);
}
void MainWindow::onProfilePicSizeChange(int newSize) {
    quick->setSource(QUrl::fromLocalFile("qml/Timeline.qml"));
    quick->rootObject()->setProperty("profilePicSize", newSize);
    profilePicSizeLabel->setText(QString::number(newSize));
}

MainWindow::~MainWindow()
{


}

