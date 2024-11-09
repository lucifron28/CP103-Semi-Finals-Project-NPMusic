#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include <QtCore>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonVolume_clicked();

private:
    Ui::MainWindow *ui;
    bool is_muted = false;
    QString buttonStyle = "QPushButton::hover {"
                              "background-color: rgba(0, 0, 0, 0.5);}"
                          "QPushButton {"
                            "border-radius: 35px;"
                            "background-color: white;"
                            "border: 2px solid black;}"
                          "QPushButton::pressed {"
                            "background-color: white}";
};
#endif // MAINWINDOW_H
