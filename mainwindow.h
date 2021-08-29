#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QAbstractButton>
#include <QQuickWidget>
#include <QSlider>
#include <QLabel>

class MainWindow : public QWidget
{
    Q_OBJECT
private slots:
    void onProfilePicLocationClicked(bool toggled );
    void onShowSelfPicClicked(bool toggled );
    void onProfilePicSizeChange(int newSize);

private:
    QGroupBox* getProfilePicOptionSettings();
    QGroupBox* getSelfPicOptionSettings();
    QGroupBox* getProfilePicSizeSetting();
    QQuickWidget * quick;
    QLabel * profilePicSizeLabel;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
