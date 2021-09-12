#include "mainwindow.h"

#include <QtQuickWidgets/QQuickWidget>
#include <QApplication>
#include <QQmlContext>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QQuickItem>
#include <stdlib.h>
#include <stdint.h>

#include <chrono>
#include <random>

MainWindow::MainWindow(QApplication* app, std::string selfName, QWidget *parent)
    : QWidget(parent), app(app), selfName(selfName)
{
    this->resize(1000, 800);

    darkPalette.setColor(QPalette::Window,          QColor( 45,  45,  45));
    darkPalette.setColor(QPalette::WindowText,      QColor(212, 212, 212));
    darkPalette.setColor(QPalette::Base,            QColor( 25,  25,  25));
    darkPalette.setColor(QPalette::AlternateBase,   QColor( 45,  45,  45));
    darkPalette.setColor(QPalette::PlaceholderText, QColor(127, 127, 127));
    darkPalette.setColor(QPalette::Text,            QColor(255, 255, 255));
    darkPalette.setColor(QPalette::Button,          QColor( 60,  60,  60));
    darkPalette.setColor(QPalette::ButtonText,      QColor(245, 245, 245));
    darkPalette.setColor(QPalette::BrightText,      QColor(255, 255, 255));
    darkPalette.setColor(QPalette::Highlight,       QColor( 38,  79, 120));
    darkPalette.setColor(QPalette::HighlightedText, QColor(240, 240, 240));

    darkPalette.setColor(QPalette::Light,           QColor( 60,  60,  60));
    darkPalette.setColor(QPalette::Midlight,        QColor( 52,  52,  52));
    darkPalette.setColor(QPalette::Dark,            QColor( 30,  30,  30) );
    darkPalette.setColor(QPalette::Mid,             QColor( 37,  37,  37));
    darkPalette.setColor(QPalette::Shadow,          QColor( 0,    0,   0));

    darkPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(127, 127, 127));

    QHBoxLayout * mainLayout = new QHBoxLayout();
    QVBoxLayout * settingsLayout = new QVBoxLayout();
    //layout->setSpacing(0);
    //layout->setMargin(0);
    this->setLayout(mainLayout);
    // IMPORTANT to reduce resource usage:
    // https://forum.qt.io/topic/98806/own-thread-for-each-qquickwidget/4

    model = new MessageGroupModel(QString::fromStdString(selfName));
    generateMessages();
    quick = new QQuickWidget(this);
    quick->rootContext()->setContextProperty("MyModel",  QVariant::fromValue(model));
    quick->rootContext()->setContextProperty("Palette",  QVariant::fromValue(lightPalette));
    mainLayout->addWidget(quick, 1);
    mainLayout->addLayout(settingsLayout, 1);
    quick->setSource(QUrl::fromLocalFile("qml/Timeline.qml"));
    settingsLayout->addWidget(getProfilePicOptionSettings());
    settingsLayout->addWidget(getSelfPicOptionSettings());
    settingsLayout->addWidget(getGroupSpacingSetting());
    settingsLayout->addWidget(getMessageSpacingSetting());
    settingsLayout->addWidget(getProfilePicSizeSetting());
    settingsLayout->addWidget(getBorderRadiusSetting());
    settingsLayout->addWidget(getThemeSetting());
    quick->setResizeMode(QQuickWidget::SizeRootObjectToView);
    quick->show();
}

void MainWindow::generateMessages() {
    std::string users[4] = { selfName, "User1", "User2", "User3" };
    int numBlobs = 100;
    int msgIndex = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint64_t> dis(1, 1000 * 60 * 60 * 8); // up to 8 hours

    // Start 30 minutes ago
    uint64_t ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - (30 * 60 * 1000);

    int lastUser = -1;
    for (int i = 0; i < numBlobs; i++) {
        int userIndex = rand() % 4;
        std::string userName = users[userIndex];

        int numMsgsInBlob = rand() % 3 + 1;

        for (int j = 0; j < numMsgsInBlob; j++) {

            int msgSize = rand() % 30 + 1;
            std::string msg = "Message + " + std::to_string(msgIndex++) + " size " +  std::to_string(msgSize);
            for (int j = 0; j < msgSize; j++) {
                msg.append(std::string(" word"));
            }

            model->addMessage(Message {ms, QString::fromStdString(msg), QString::fromStdString(userName)});

            ms += rand() % (20 * 1000); // Add up to 20 seconds.
        }

        if (rand() % 3 == 0 || lastUser == userIndex) {
            // 1/3 chance of a long delay
            ms += dis(gen);
        }
        lastUser = userIndex;
    }
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

QGroupBox *MainWindow::getThemeSetting()
{
    QGroupBox *groupBox = new QGroupBox(tr("Theme"));

    QRadioButton *radio1 = new QRadioButton(tr("Light"));
    QRadioButton *radio2 = new QRadioButton(tr("Dark"));

    radio1->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    connect(radio1, &QRadioButton::toggled, this,
            &MainWindow::onThemeClicked);
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

QGroupBox* MainWindow::getBorderRadiusSetting() {
    QGroupBox *groupBox = new QGroupBox(tr("Bubble Border Radius"));

    QSlider * slider = new QSlider(Qt::Orientation::Horizontal);
    slider->setMaximum(12);
    borderRadiusLabel = new QLabel();

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(borderRadiusLabel, 0);
    hbox->addWidget(slider, 1);
    groupBox->setLayout(hbox);

    connect(slider, &QSlider::valueChanged, this,
            &MainWindow::onBorderRadiusChange);

    slider->setValue(5);
    return groupBox;
}

QGroupBox* MainWindow::getGroupSpacingSetting() {
    QGroupBox *groupBox = new QGroupBox(tr("Group Spacing"));

    QSlider * slider = new QSlider(Qt::Orientation::Horizontal);
    slider->setMaximum(100);
    groupSpacingLabel = new QLabel();

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(groupSpacingLabel, 0);
    hbox->addWidget(slider, 1);
    groupBox->setLayout(hbox);

    connect(slider, &QSlider::valueChanged, this,
            &MainWindow::onGroupSpacingChange);

    slider->setValue(13);
    return groupBox;
}

QGroupBox* MainWindow::getMessageSpacingSetting() {
    QGroupBox *groupBox = new QGroupBox(tr("Message Spacing"));

    QSlider * slider = new QSlider(Qt::Orientation::Horizontal);
    slider->setMaximum(20);
    slider->setMinimum(-5);
    messageSpacingLabel = new QLabel();

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(messageSpacingLabel, 0);
    hbox->addWidget(slider, 1);
    groupBox->setLayout(hbox);

    connect(slider, &QSlider::valueChanged, this,
            &MainWindow::onMessageSpacingChange);

    slider->setValue(10);
    return groupBox;
}

void MainWindow::onProfilePicLocationClicked( bool toggled) {
    quick->rootObject()->setProperty("profilePicTopAlign", toggled);
}
void MainWindow::onShowSelfPicClicked( bool toggled) {
    quick->rootObject()->setProperty("showSelfProfilePic", toggled);
}
void MainWindow::onThemeClicked( bool isLight) {
    if (isLight) {
        quick->rootObject()->setProperty("color", "#eceff1");
        quick->rootObject()->setProperty("msgBackgroundColor", "#FFF");
        quick->rootObject()->setProperty("selfMsgBackgroundColor", "#cfd8dc");
        quick->rootContext()->setContextProperty("Palette",  QVariant::fromValue(lightPalette));
        app->setPalette(lightPalette);
    } else {
        quick->rootObject()->setProperty("color", "#000");
        quick->rootObject()->setProperty("msgBackgroundColor", "#303030");
        quick->rootObject()->setProperty("selfMsgBackgroundColor", "#19a3ff");
        quick->rootContext()->setContextProperty("Palette",  QVariant::fromValue(darkPalette));
        app->setPalette(darkPalette);
    }
}
void MainWindow::onProfilePicSizeChange(int newSize) {
    quick->rootObject()->setProperty("profilePicSize", newSize);
    profilePicSizeLabel->setText(QString::number(newSize));
}

void MainWindow::onBorderRadiusChange(int newSize) {
    quick->rootObject()->setProperty("bubbleRadius", newSize);
    borderRadiusLabel->setText(QString::number(newSize));
}

void MainWindow::onGroupSpacingChange(int newSize) {
    quick->rootObject()->setProperty("groupSpacing", newSize);
    groupSpacingLabel->setText(QString::number(newSize));
}
void MainWindow::onMessageSpacingChange(int newSize) {
    quick->rootObject()->setProperty("messageSpacing", newSize);
    messageSpacingLabel->setText(QString::number(newSize));
}

MainWindow::~MainWindow()
{


}

