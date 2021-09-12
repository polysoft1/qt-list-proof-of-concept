#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QAbstractButton>
#include <QQuickWidget>
#include <QSlider>
#include <QLabel>
#include "message.h"
#include "messagegroupmodel.h"

class MainWindow : public QWidget
{
    Q_OBJECT
private slots:
    void onProfilePicLocationClicked(bool toggled );
    void onShowSelfPicClicked(bool toggled );
    void onThemeClicked(bool toggled );
    void onProfilePicSizeChange(int newSize);
    void onBorderRadiusChange(int newSize);
    void onGroupSpacingChange(int newSize);
    void onMessageSpacingChange(int newSize);

private:
    void generateMessages();

    QGroupBox* getProfilePicOptionSettings();
    QGroupBox* getSelfPicOptionSettings();
    QGroupBox* getProfilePicSizeSetting();
    QGroupBox* getBorderRadiusSetting();
    QGroupBox* getGroupSpacingSetting();
    QGroupBox* getMessageSpacingSetting();
    QGroupBox* getThemeSetting();
    QQuickWidget * quick;
    QLabel * profilePicSizeLabel;
    QLabel * borderRadiusLabel;
    QLabel * groupSpacingLabel;
    QLabel * messageSpacingLabel;

    QApplication* app;
    std::string selfName;

    QPalette darkPalette;
    QPalette lightPalette;

    MessageGroupModel * model;

public:
    MainWindow(QApplication* app, std::string selfName, QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
